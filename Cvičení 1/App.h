#pragma once
#include "Window.h"

class App {
public:
    App();

    bool init(void);
    void report(void);
    int run(void);

    ~App();
private:
    Window* window;
};
