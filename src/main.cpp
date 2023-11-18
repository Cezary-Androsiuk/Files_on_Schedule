#include "Window.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// BUILD LINUX
// mkdir bin && cd bin;
// cmake .. && make && ./main;

// BUILD WINDOWS
// mkdir bin && cd bin;
// cmake -G "MinGW Makefiles" .. && cmake --build . && .\main

#ifdef linux
// it is linux :)
#elif _WIN32
// it is windows :)
#elif __APPLE__
// it is macos :)
#elif __ANDROID__
// it is android :)
#endif

int main(const int argc, const char **argv)
{
    Window *a = new Window(argc, argv);

    while (a->running())
    {
        a->update();
        a->render();
    }

    delete a;

    printf("Application Correctly Closed!\n");
    return 0;
}