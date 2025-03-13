#include <iostream>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "App.h"
#include "Window.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Mesh.h"
#include "Shader.h"

#include "FrameCounter.h"
#include "DebugOutputManager.h"

App::App()
{
    // default constructor
    // nothing to do here (so far...)
    std::cout << "New App constructed\n";
    window = new Window(800, 600, "OpenGL Window");;
}

bool App::init()
{
    // init glew
    // http://glew.sourceforge.net/basic.html
    glewInit();
    wglewInit();

    return true;
}

void App::report(void)
{
    GLint extensionCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount);

    std::cout << "OpenGL Information:" << std::endl;
    std::cout << "Vendor: " << "\t" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << "\t" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << "\t" << glGetString(GL_VERSION) << std::endl;
    std::cout << "Extensions: " << "\t" << extensionCount << std::endl;


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
}

int App::run()
{
    FrameCounter fps;
    DebugOutputManager debug;

    std::cout << "Debug Output: \t" << (debug.isAvailable ? "yes" : "no") << std::endl;

    OBJLoader test{ "./assets/obj/bunny_tri_vnt.obj" };

    auto camera = Camera{ glm::vec3(0.0f, 0.0f, 0.0f) };
    auto mesh = test.getMesh();

    auto vertexShaderPath = std::filesystem::path("./assets/shaders/basic.vert");
    auto fragmentShaderPath = std::filesystem::path("./assets/shaders/basic.frag");
    auto shader = Shader(vertexShaderPath, fragmentShaderPath);

    shader.setUniform("projection", camera.getProjectionMatrix());
    //glfwSetCursorPosCallback(window->getWindow(), camera.onMouseEvent);
    
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    std::cout << shader.ID << std::endl;

    while (!glfwWindowShouldClose(window->getWindow()))
    {
        // If a second has passed.
        if (fps.hasSecondPassed())
        {
            // Display the frame count here any way you want.
            std::cout << "FPS: \t" << fps.getNumberOfFrames() << std::endl;
            fps.setNumberOfFrames(0);
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.onKeyboardEvent(window->getWindow(), deltaTime); // process keys etc

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setUniform("transform", trans);

        // Tady si musim nastudovat, co to vlastnì kurva dìlá.
        // Jako position chápu, front už taky, ale ten up vector je nìjakej zakletej
        //camera.Pitch = 30.0f;

        shader.setUniform("view", camera.getViewMatrix());

        //glm::mat4 projection = glm::mat4(1.0f);
        //projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        shader.setUniform("projection", camera.getProjectionMatrix());

        mesh.draw(shader);

        // Swap front and back buffers
        glfwSwapBuffers(window->getWindow());

        // Poll for and process events
        glfwPollEvents();
    }

    std::cout << std::endl;

    return 0;
}

App::~App()
{
    // clean-up
    std::cout << "Bye...\n";
}