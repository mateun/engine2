cmake_minimum_required(VERSION 3.10)
project(engine)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)

file(GLOB ENGINE_SRC
    src/*.cpp
    src/*.h
)

add_library(engine STATIC ${ENGINE_SRC})
target_link_libraries(engine PUBLIC Vulkan::Vulkan)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external
)

file(GLOB APP_SRC src/*.cpp)
add_executable(engine_app ${APP_SRC})
target_link_libraries(engine_app PRIVATE engine Vulkan::Vulkan)
set_target_properties(engine_app PROPERTIES WIN32_EXECUTABLE TRUE)

# Asset copy logic
file(GLOB ASSETS
    assets/*.spv
    assets/*.vert
    assets/*.frag
    assets/*.png
    assets/*.jpg
    assets/*.bmp
    assets/*.glb
    assets/*.fbx
    assets/*.obj
)

add_custom_command(TARGET engine_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:engine_app>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSETS} $<TARGET_FILE_DIR:engine_app>/assets
    COMMAND ${CMAKE_COMMAND} -E echo "Copied shaders and resources to output directory."
) 