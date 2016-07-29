#include "main.hpp"
#include "Application.hpp"

int main(int argc, char* argv[])
{
    auto app = make_shared<Application>(argc, argv);
    return app->run();
}
