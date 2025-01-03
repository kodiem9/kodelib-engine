#pragma once
#include <raylib.h>
#include <unordered_map>
#include <typeindex>
#include <iostream>

namespace kl {

    class Engine {
        public:
            template<typename T> void AddType(int value);
            template<typename T> int GetType();
        
            std::unordered_map<std::type_index, int> entities;
        
        private:
    };

}

template<typename T>
void kl::Engine::AddType(int value) {
    entities[std::type_index(typeid(T))] = value;
}

template<typename T>
int kl::Engine::GetType() {
    return entities[std::type_index(typeid(T))];
}