#pragma once
#include <LIB_PCH.hpp>

class Component {
    public:
        virtual ~Component() = default;
};

class TransformComponent : public Component {
    public:
        TransformComponent(int x, int y) : x(x), y(y) { }
        int x, y;
};

class HelloComponent : public Component {
    public:
        void Hello() {
            std::cout << "Hello!" << std::endl;
        }
};

typedef std::unordered_map<std::type_index, std::shared_ptr<Component>>  components_map;

class Entity {
    public:
        virtual ~Entity() = default;
        template<typename T, typename... Args> void AddComponent(Args... args);
        template<typename T> T& GetComponent();
    
    private:
        components_map components;
};

template<typename T, typename... Args>
void Entity::AddComponent(Args... args) {
    components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
T& Entity::GetComponent() {
    return *std::static_pointer_cast<T>(components[typeid(T)]);
}