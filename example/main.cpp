#include <kodelib.hpp>

int main() {
    Entity entity;
    entity.AddComponent<HelloComponent>();
    entity.GetComponent<HelloComponent>().Hello();
    return 0;
}