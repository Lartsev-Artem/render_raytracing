#include <iostream>
#include "Scene.h"
#include "render_cl.h"
#include "process_sdl.h"
#include <string>
#include <omp.h>

enum e_object_type_t
{
    e_obj_type_none,
    e_obj_type_complex,
    e_obj_type_sphere,
    e_obj_type_plane,
    e_obj_type_light
};
static void parser(int argc, char* argv[], Scene& sc)
{
    sc.load_background(argv[3]);

    std::vector<Material> materilas;
    Material m;
    int idx = 4, type = -1;
    do
    {
        sscanf_s(argv[idx], "%d,", &type);
        if (type != e_obj_type_none)
        {
            break;
        }

        sscanf_s(argv[idx++], "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f", &type,
            &m.albedo.diffuse, &m.albedo.specular,
            &m.albedo.absorption, &m.albedo.refraction,
            &m.color[0], &m.color[1], &m.color[2],
            &m.shininess, &m.refraction);

        materilas.push_back(m);

        if (idx >= argc)
        {
            return;
        }
    } while (true);


    Vec3f c, p1, p2;
    float r;
    int id;
    char file_obj[250];
    for (size_t i = idx; i < argc; i++)
    {
        sscanf_s(argv[i], "%d,", &type);
        switch (type)
        {
        case e_obj_type_complex:
            sscanf_s(argv[i], "%d,%f,%f,%f,%f,%f,%f,%d,%s", &type,
                &p1[0], &p1[1], &p1[2],
                &p2[0], &p2[1], &p2[2], &id,
                file_obj, (rsize_t)sizeof file_obj);
            printf("file=%s\n", file_obj);
            sc.add_complex_obj(ComplexObj(file_obj, materilas[id], p1, p2));
            break;
        case e_obj_type_sphere:
            sscanf_s(argv[i], "%d,%f,%f,%f,%f,%d", &type, &c[0], &c[1], &c[2], &r, &id);
            sc.add_sphere(Sphere(c, r, materilas[id]));
            break;
        case e_obj_type_plane:
            sscanf_s(argv[i], "%d,%f,%f,%f,%f,%f,%f,%d", &type, &p1[0], &p1[1], &p1[2],
                &p2[0], &p2[1], &p2[2], &id);
            sc.add_plane(Plane(p1, p2, materilas[id]));
            break;
        case e_obj_type_light:
            sscanf_s(argv[i], "%d,%f,%f,%f,%f", &type, &p1[0], &p1[1], &p1[2], &r);
            sc.add_light(Light(p1, r));
            break;
        default:
            printf("unknow obj\n");
            exit(1);
        }
    }
}


static int default_scene(Scene& scene)
{
    std::string file_background = "D:/Game/RayTracing/MakeRayTracing/data/background.jpg";
    scene.load_background(file_background.c_str());

    scene.add_light(Light(Vec3f(-20, 20, 20), 1.5));
    scene.add_light(Light(Vec3f(30, 50, -25), 1.8));
    scene.add_light(Light(Vec3f(30, 20, 30), 1.7));

    //scene.add_sphere(Sphere(Vec3f(-3, 0, -16), 2, material::ivory));
    //scene.add_sphere(Sphere(Vec3f(-1.0, -1.5, -12), 2, material::glass));
   // scene.add_sphere(Sphere(Vec3f(1.5, -0.5, -18), 3, material::red_rubber));
    //scene.add_sphere(Sphere(Vec3f(7, 5, -18), 4, material::mirror));
    //scene.add_plane(Plane(Vec3f(-10, 4, -30), Vec3f(10, 4, -10), Material()));

    //scene.add_complex_obj(ComplexObj("duck.obj", material::red_rubber, Vec3f(0, M_PI/5, 0), point_t(0,0.4,-23)));

    scene.add_sphere(Sphere(Vec3f(-3, 0, 0), 2, material::ivory));
    scene.add_sphere(Sphere(Vec3f(1.5, -0.5, 0), 3, material::red_rubber));  

    return 0;
    /*  scene.output("./out.jpg");
      system("out.jpg");*/
}

int main(int argc, char* argv[])
{
    const std::string file_kernel = "kernel.cl";
    
    Camera camera(Vec3f(0, 0, -18), 400);
    Vec2i screen(800, 600);

    if (argc >= 3)
    {
        sscanf_s(argv[1], "%f,%f,%f,%f", &camera._pos[0], &camera._pos[1], &camera._pos[2], &camera._death);
        sscanf_s(argv[2], "%d,%d", &screen[0], &screen[1]);
    }

    Scene scene(screen, camera);

    if (argc > 5)
    {
        parser(argc, argv, scene);
    }
    else
    {
        default_scene(scene);
    }

    Process_SDL SDL_proc;
    SDL_proc.init(scene.get_screen());

    render_cl::init(file_kernel.c_str());
    render_cl::init_scene(scene, render_cl::phong_model);

    render_cl::start_render(scene);
    //scene.render(render::diffusion);
    SDL_proc.update();

    Vec3i handle_move(0, 0, 0);
    while (1)  // main game loop
    {
        if (SDL_proc.handle_event(handle_move))
        {
            break; // quit
        }

        if (handle_move != Vec3i(0, 0, 0))
        {
            scene.set_camera(handle_move);
            render_cl::update_cam_position(scene);
            render_cl::start_render(scene);
            //scene.render(render::diffusion);
            SDL_proc.update();
            handle_move = Vec3i(0, 0, 0);
        }
    }

    return 0;
}

//Контроль утечек памяти
//#define CHECK_MEMORY
#ifdef CHECK_MEMORY
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#ifdef CHECK_MEMORY
_CrtMemState _ms;
_CrtMemCheckpoint(&_ms);
#endif
// PROGRAMM
#ifdef CHECK_MEMORY
_CrtMemDumpAllObjectsSince(&_ms);
#endif