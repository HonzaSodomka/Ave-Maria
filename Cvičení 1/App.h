#pragma once
#include "Window.h"

class App {
public:
    App();

    bool init(void);
    void report(void);
    int run(void);

    void addMouseHandler(void);
    void onMouseMove(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch);

    ~App();
private:
    Window* window;
};
