cmake_minimum_required(VERSION 3.0)

project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_CXX_COMPILER icl)


set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#====================
include(CheckCXXCompilerFlag)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        message("${flag}")
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-std=c++17")
enable_cxx_compiler_flag_if_supported("-O3")
enable_cxx_compiler_flag_if_supported("-openmp")
#==============================================

include_directories(${LIB_DIR})

include_directories("${LIB_DIR}/CL")
find_library(OPENCL OpenCL.lib "${LIB_DIR}/CL")

include_directories("${LIB_DIR}/SDL2/include")
include_directories("${LIB_DIR}/SDL2/lib/x64/")
find_library(SDL SDL2.lib SDL2main.lib SDL2test.lib "${LIB_DIR}/SDL2/lib/x64/")


file( GLOB SOURCES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/cl/*.cl"
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCL})
target_link_libraries(${PROJECT_NAME} ${SDL})


file(GLOB CL_FILES "${SRC_DIR}/cl/*.cl")
file(COPY ${CL_FILES} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build") #копирование файлов

configure_file("${LIB_DIR}/SDL2/lib/x64/SDL2.dll" "${CMAKE_CURRENT_SOURCE_DIR}/build" COPYONLY) # тоже копирование файла

target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}/cl")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/stb")
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})
