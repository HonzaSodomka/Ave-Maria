#pragma once
#include "Window.h"

Window::Window(int width, int height, const char* title, bool fullscreen, bool vsync)
    : fullscreen(fullscreen), vsync(vsync) {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        std::exit(-1);
    }

    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
    }
    else {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::getWindow() const {
    return window;
}

void Window::set_fullscreen(bool fullscreen) {
    this->fullscreen = fullscreen;
    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
    }
    else {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(window, nullptr, 150, 150, mode->width / 2, mode->height / 2, GLFW_DONT_CARE);
    }
}

void Window::set_vsync(bool vsync)
{
    this->vsync = vsync;

    if (vsync) {
        glfwSwapInterval(1);
        return;
    }

    glfwSwapInterval(0);
}

bool Window::isVSynced() const
{
    return vsync;
}

bool Window::isFullscreen() const {
    return fullscreen;
}


// Static key callback function
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // glfwGetWindowUserPointer() vytáhne z okna custom pointer, který je k nìmu pøiøazen
    // v našem pøípadì jsem k tomu pøidadil instanci tøídy Window v jejím konstruktoru
    // static_cast<Window*> je type_casting syntax (pøevod datového typu) - tím my c++ øekneme, že ten pointer je na tøídu Window
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->handle_key_event(key, action);
    }
}

/*
    Funkce pro handlování inputu v oknì.
*/
void Window::handle_key_event(int key, int action) {

    switch (action) {
        case GLFW_PRESS:
            this->handle_key_press(key, action);
        default:
            break;
    }
}

void Window::handle_key_press(int key, int action) {
    switch (key) {
        case GLFW_KEY_ESCAPE: {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }
        case GLFW_KEY_F: {
            fullscreen = !fullscreen;
            set_fullscreen(fullscreen);
            std::cout << "Fullscreen " << (fullscreen ? "enabled" : "disabled") << std::endl;
            break;
        }
        case GLFW_KEY_V: {
            vsync = !vsync;
            set_vsync(vsync);
            std::cout << "VSync " << (vsync ? "enabled" : "disabled") << std::endl;
            break;
        }
    }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // Pro vysvìtlení viz Window::handle_key_event
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->handle_scroll_event(xoffset, yoffset);
    }
}

void Window::handle_scroll_event(double xoffset, double yoffset) {
    GLclampf redf = static_cast<GLclampf>(yoffset / 10);
    GLclampf greenf = static_cast<GLclampf>(yoffset / 10);
    GLclampf bluef = static_cast<GLclampf>(yoffset / 10);

    glClearColor(redf, greenf, bluef, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
