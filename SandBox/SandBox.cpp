#include <iostream>

namespace WestEngine
{
    class __declspec(dllimport) Engine
    {
    public:
	    void Run();
    };
}

int main()
{
    WestEngine::Engine* engine = new WestEngine::Engine();
    engine->Run();
    std::cout << "Hello World!\n";
    std::cin.get();
}
