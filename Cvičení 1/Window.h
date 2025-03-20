#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"

class Window {
public:
    Window(int width, int height, const char* title, bool fullscreen = false, bool vsync = false);
    ~Window();
    
    void setFullscreen(bool fullscreen);
    void setVsync(bool vsync);

    void onScrollEvent(double xoffset, double yoffset);
    void onKeyEvent(int key, int action);
    
    // OpenGL callbacks
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool isVSynced() const;
    bool isFullscreen() const;
    GLFWwindow* getWindow() const;

    static Camera* cam;
    static bool isMouseMoved;
    static float lastX;
    static float lastY;

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void handle_key_press(int key, int action);
    GLFWwindow* window;

    bool fullscreen;
    bool vsync;
};

#endif
