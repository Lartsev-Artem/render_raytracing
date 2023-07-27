#include "Scene.h"
#include "render_cl.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Objects.cl"


void render_cl::init(const char* src_file)
{
    cl_platform_id platform_id;
    cl_uint ret_num_platforms;
    cl_int ret = 0;

    /* получить доступные платформы */
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    CL_ASSERT(ret);

    cl_device_id device_id;
    cl_uint ret_num_devices;
    /* получить доступные устройства */
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    CL_ASSERT(ret);

    /* создать контекст */
    cfg.context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    CL_ASSERT(ret);

    /* создаем команду */
    cfg.command_queue = clCreateCommandQueue(cfg.context, device_id, 0, &ret);
    CL_ASSERT(ret);
    //======================================//

    cfg.program = NULL;
    cfg.kernel = NULL;

    FILE* fp;
    const char* fileName = src_file;
    size_t source_size;
    char* source_str;
    int i;

    try {
        fp = fopen(fileName, "r");
        if (!fp) {
            fprintf(stderr, "Failed to load %s.\n", src_file);
            system("pause");
            exit(1);
        }
        source_str = (char*)malloc(MAX_SOURCE_SIZE);
        source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
        fclose(fp);
    }
    catch (int a) {
        printf("%d", a);
    }

    /* создать бинарник из кода программы */
    cfg.program = clCreateProgramWithSource(cfg.context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
    CL_ASSERT(ret);

    /* скомпилировать программу */
    ret = (clBuildProgram(cfg.program, 1, &device_id, NULL, NULL, NULL));

    if (ret == CL_BUILD_PROGRAM_FAILURE)
    {
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(cfg.program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char* log = (char*)malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(cfg.program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
        free(log);
    }
    CL_ASSERT(ret);

    free(source_str);
}

void render_cl::screencpy2device(const Screen& screen)
{
    uint8_t* screen_ptr = (uint8_t*)malloc(screen.size() * sizeof(screen(0, 0)) + sizeof(int) * 2);
    memcpy(screen_ptr, &screen._width, sizeof(int));
    memcpy(screen_ptr + sizeof(int), &screen._height, sizeof(int));
    memcpy(screen_ptr + 2 * sizeof(int), screen.data(), screen.size() * sizeof(screen(0, 0)));
    memcpy2device(screen.size() * sizeof(screen(0, 0)) + sizeof(int) * 2, screen_ptr);
    free(screen_ptr);
}

void render_cl::update_cam_position(const Scene& sc)
{
    _memobj.pop_back();
    void* cam = nullptr;
    int size = sc._camera.to_cl(cam);
    memcpy2device(size, cam);
    free(cam);
}

void render_cl::memcpy2device(size_t byte_size, void* data)
{
    cl_int ret = 0;

    /* создать буфер */
    cl_mem memobj = clCreateBuffer(cfg.context, CL_MEM_READ_WRITE, byte_size, NULL, &ret);    
    CL_ASSERT(ret);

    /* записать данные в буфер */
    ret = clEnqueueWriteBuffer(cfg.command_queue, memobj, CL_TRUE, 0, byte_size, data, 0, NULL, NULL);    
    CL_ASSERT(ret);

    _memobj.push_back(memobj);
}
void render_cl::memcpy2device_vec(int n, size_t byte_size, void* data)
{
    cl_int ret = 0;

    /* создать буфер */
    cl_mem memobj = clCreateBuffer(cfg.context, CL_MEM_READ_WRITE, n * byte_size + sizeof(int), NULL, &ret);
    CL_ASSERT(ret);

    /* записать данные в буфер */
    ret = (clEnqueueWriteBuffer(cfg.command_queue, memobj, CL_TRUE, 0, sizeof(int), &n, 0, NULL, NULL));
    CL_ASSERT(ret);

    ret = (clEnqueueWriteBuffer(cfg.command_queue, memobj, CL_TRUE, sizeof(int), n * byte_size, data, 0, NULL, NULL));
    CL_ASSERT(ret);

    _memobj.push_back(memobj);
}

void render_cl::memcpy2host(int arg, size_t byte_size, int offset_device, void* data)
{
    /* считать данные из буфера */
    cl_int ret = (clEnqueueReadBuffer(cfg.command_queue, _memobj[arg], CL_TRUE, offset_device, byte_size, data, 0, NULL, NULL));
    CL_ASSERT(ret);
}

void render_cl::init_scene(Scene& sc, const char* model)
{
    cl_int ret = 0;

    /* создать кернел */
    cfg.kernel = clCreateKernel(cfg.program, model, &ret);
    CL_ASSERT(ret);

    screencpy2device(sc._screen);
    screencpy2device(sc._background);

    int cnt = sc._objects.size();
    memcpy2device(sizeof(int), &cnt);

    int size = 0;
    for (auto& obj : sc._objects)
    {
        size += obj->get_data_byte_size();
    }

    void* obj = malloc(size);

    uint8_t* ptr = (uint8_t*)obj;
    for (size_t i = 0; i < cnt; i++)
    {
        ptr += sc._objects[i]->to_cl(ptr);
    }
    memcpy2device(size, obj);
    free(obj);

    memcpy2device_vec(sc._lights.size(), sizeof(sc._lights[0]), sc._lights.data());


    void* cam = nullptr;
    size = sc._camera.to_cl(cam);
    memcpy2device(size, cam);
    free(cam);
}

void render_cl::gradient(Scene& sc)
{
    cl_int ret = 0;

    /* создать кернел */
    cfg.kernel = clCreateKernel(cfg.program, "gradient", &ret);
    CL_ASSERT(ret);

    screencpy2device(sc._screen);

    /* устанавливаем параметр */
    int idx = 0;
    for (auto& obj : _memobj)
    {
        CL_ASSERT(clSetKernelArg(cfg.kernel, idx++, sizeof(obj), (void*)&obj));
    }

    std::vector<size_t> block_cfg = { sc._screen._width, sc._screen._height };

    /* выполнить кернел */
    CL_ASSERT(clEnqueueNDRangeKernel(cfg.command_queue, cfg.kernel, 2, NULL, block_cfg.data(), NULL, 0, NULL, NULL));

    memcpy2host(0, sc._screen.size() * sizeof(sc._screen(0, 0)), sizeof(int) * 2, (void*)sc._screen.data());
}

void render_cl::start_render(Scene& sc)
{
    cl_int ret;
    /* устанавливаем параметр */
    int idx = 0;
    for (auto& obj : _memobj)
    {
        ret = clSetKernelArg(cfg.kernel, idx++, sizeof(obj), (void*)&obj);
        CL_ASSERT(ret);
    }

    std::vector<size_t> block_cfg = { sc._screen._width, sc._screen._height };

    /* выполнить ядро */
    ret = clEnqueueNDRangeKernel(cfg.command_queue, cfg.kernel, block_cfg.size(), NULL, block_cfg.data(), NULL, 0, NULL, NULL);
    CL_ASSERT(ret);

    memcpy2host(0, sc._screen.size() * sizeof(sc._screen(0, 0)), sizeof(int) * 2, (void*)sc._screen.data());
}