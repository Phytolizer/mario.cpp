#include <jade/Window.hpp>

int main(int argc, char* argv[])
{
    Window& window = Window::get();
    window.run();
    return 0;
}
