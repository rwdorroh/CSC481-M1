#pragma once
#include <engine/Entity.h>

class Player; // Forward declaration

class Auto : public Entity {
public:
    Auto(float x, float y, float w, float h, const char* texturePath, const Player* target);

    void update(float deltaTime);

    static void reset(Entity* orb, const Player* target, float x, float y, float speed = 300.0f);

private:
    OrderedPair direction{};
    float speed = 300.0f; // Adjust as needed
};
