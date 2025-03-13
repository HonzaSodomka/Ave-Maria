#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#include "App.h"

App app;

int main()
{
    bool isInitialized = app.init();

    if (!isInitialized) {
        return 1;
    }

    // Print OpenGL diagnostic information
    app.report();

    return app.run();
}