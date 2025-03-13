#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    Window(int width, int height, const char* title, bool fullscreen = false, bool vsync = false);
    ~Window();
    
    void set_fullscreen(bool fullscreen);
    void set_vsync(bool vsync);

    void handle_scroll_event(double xoffset, double yoffset);
    void handle_key_event(int key, int action);
    
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool isVSynced() const;
    bool isFullscreen() const;
    GLFWwindow* getWindow() const;

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void handle_key_press(int key, int action);
    GLFWwindow* window;

    bool fullscreen;
    bool vsync;
};

#endif
