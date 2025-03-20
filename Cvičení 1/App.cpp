#include <iostream>
#include <string>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "Logger.h"
#include "App.h"
#include "Camera.h"
#include "Window.h"
#include "OBJLoader.h"
#include "Mesh.h"
#include "Shader.h"

#include "Model.h"

#include "SimpleLight.h"

#include "FrameCounter.h"
#include "DebugOutputManager.h"

App::App()
{
    // default constructor
    // nothing to do here (so far...)
    Logger::info("New Application has been constructed.");
    window = new Window(800, 600, "OpenGL Window", false, false);
}

bool App::init()
{
    // init glew
    // http://glew.sourceforge.net/basic.html
    glewInit();
    wglewInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    return true;
}

void App::report(void)
{
    GLint extensionCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount);

    std::ostringstream vendor, renderer, version, extensions;

    vendor << "Vendor: " << glGetString(GL_VENDOR) << ", " << "rendered with " << glGetString(GL_RENDERER);
    version << "Version: " << glGetString(GL_VERSION) << ", " << extensionCount << " extensions.";

    Logger::debug(vendor.str());
    Logger::debug(version.str());

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    Logger::debug("Enabled Backface Culling (CCW)");
}

int App::run()
{
    FrameCounter fps;
    DebugOutputManager debug;

    Logger::debug("OpenGL Debug Output: " + (debug.isAvailable ? std::string("yes") : std::string("no")));

    auto camera = Camera{ glm::vec3(0.0f, 15.0f, 0.0f) };

    auto gate = Model("./assets/obj/gate.obj");
    auto gateShader = Shader(std::filesystem::path("./assets/shaders/material.vert"), std::filesystem::path("./assets/shaders/material.frag"));
    //gate.scale = glm::vec3(0.5f);
    

    auto coin = Model("./assets/obj/coin.obj");
    auto meshShader = Shader(std::filesystem::path("./assets/shaders/material.vert"), std::filesystem::path("./assets/shaders/material.frag"));

    auto terrain = Model("./assets/obj/level_1.obj");
    auto terrainShader = Shader(std::filesystem::path("./assets/shaders/material.vert"), std::filesystem::path("./assets/shaders/material.frag"));

    auto simpleLight = SimpleLight(glm::vec3(1.0f, 10.0f, -10.0f), 5.0f);

    Window::cam = &camera;

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glfwSetCursorPosCallback(window->getWindow(), Window::mouse_callback);
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window->getWindow()))
    {
        //menu.render();
        // If a second has passed.
        if (fps.hasSecondPassed()) {
            fps.setNumberOfFrames(0);
        }

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clearing the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        // New GUI frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // process events
        camera.onKeyboardEvent(window->getWindow(), deltaTime);

        // Draw scene
        
        // Moving light

        // Gate
        gateShader.activate();
        gateShader.setUniform("light.position", simpleLight.position);
        gateShader.setUniform("light.ambient", simpleLight.ambient);
        gateShader.setUniform("light.diffuse", simpleLight.diffusion);
        gateShader.setUniform("light.specular", simpleLight.specular);
        gateShader.setUniform("light.constant", 1.0f);
        gateShader.setUniform("light.linear", 0.09f);
        gateShader.setUniform("light.quadratic", 0.032f);

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, (float)glfwGetTime() / 4, glm::vec3(0.0f, 1.0f, 0.0f));

        gateShader.setUniform("transform", model);
        gateShader.setUniform("view", camera.getViewMatrix());
        gateShader.setUniform("projection", camera.getProjectionMatrix());

        // Terrain
        terrainShader.activate();
        terrainShader.setUniform("light.position", simpleLight.position);
        terrainShader.setUniform("light.ambient", simpleLight.ambient);
        terrainShader.setUniform("light.diffuse", simpleLight.diffusion);
        terrainShader.setUniform("light.specular", simpleLight.specular);
        terrainShader.setUniform("light.constant", 1.0f);
        terrainShader.setUniform("light.linear", 0.5f);
        terrainShader.setUniform("light.quadratic", 0.0019f);

        terrainShader.setUniform("transform", glm::mat4(1.0f));
        terrainShader.setUniform("view", camera.getViewMatrix());
        terrainShader.setUniform("projection", camera.getProjectionMatrix());

        simpleLight.render(camera);

        terrain.render(terrainShader);
        coin.render(gateShader);
        gate.render(gateShader);

        // Draw HUD
        ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetTextLineHeightWithSpacing() * 3));
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("FPS Counter", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
        // Could be realtime if std::round(1 / deltatime);
        ImGui::Text("FPS: %d", fps.getLastNumberOfFrames());
        ImGui::Text("Vsync: %s", window->isVSynced() ? "True" : "False");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //// Swap front and back buffers
        glfwSwapBuffers(window->getWindow());

        //// Poll for and process events
        glfwPollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    std::cout << std::endl;

    return 0;
}

App::~App()
{
    // clean-up
    std::cout << "Bye...\n";
}