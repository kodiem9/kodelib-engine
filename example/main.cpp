#include <PCH.hpp>

int main() {
    kl::Engine engine;
    engine.AddType<int>(5);
    engine.AddType<char>(10);
    engine.AddType<float>(15);
    
    std::cout << engine.GetType<int>() << std::endl;
    std::cout << engine.GetType<char>() << std::endl;
    std::cout << engine.GetType<float>() << std::endl;

    return 0;
}