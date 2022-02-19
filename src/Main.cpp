#include "Application.hpp"

#include <stdexcept>
#include <iostream>


int main()
{
    jclip::Application app;
    app.init();
    
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
