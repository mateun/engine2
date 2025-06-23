#include <iostream>
#include "Win32Window.h"
#include "VulkanApp.h"
#include "ImageLoader.h"
#include "GLTFImporter.h"
#include "Camera.h"
#include "Mesh.h"
#include "SceneNode.h"
#include "Scene.h"
#include <thread>
#include <chrono>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    Win32Window window(hInstance, nCmdShow);
    VulkanApp vkApp(hInstance, window.get_hwnd(), 800, 600);

    // Setup camera
    Camera camera;
    camera.set_perspective(glm::radians(60.0f), 800.0f/600.0f, 0.1f, 100.0f);
    camera.set_position(glm::vec3(0, 2, 10));
    camera.set_look_at(glm::vec3(0, 0, 0));
    camera.set_up(glm::vec3(0, 1, 0));
    vkApp.set_camera(camera);

    // Load mesh
    std::vector<Vertex> meshVertices;
    std::vector<uint32_t> meshIndices;
    if (!GLTFImporter::load_mesh("assets/test.glb", meshVertices, meshIndices)) {
        std::cerr << "Failed to load mesh from test.glb" << std::endl;
        return 1;
    }
    // Create mesh and scene node
    auto mesh = std::make_shared<Mesh>(vkApp.device(), vkApp.physical_device(), meshVertices, meshIndices);
    auto node = std::make_unique<SceneNode>();
    node->mesh = mesh;
    // Optionally set node transform here
    // Create scene
    Scene scene;
    scene.root = std::move(node);
    vkApp.set_scene(&scene);
    vkApp.record_draw_commands();

    // Give RenderDoc a chance to attach before Vulkan instance creation
    if constexpr (true) { // Set to true if you want to always allow attaching
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Main loop
    while (window.process_messages()) {
        vkApp.draw_frame();
    }
    vkApp.wait_device_idle();
    return 0;
} 