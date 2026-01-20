#pragma once
#include <engine/Entity.h>

class Player : public Entity {
public:
    Player(float x, float y, float w, float h, const char* texturePath, Entity* platform, Entity** orbPtr);

    void update(float deltaTime);

private:
    bool isOnGround = false;

    // Dodge state
    bool dodgeActive = false;
    float dodgeTimer = 0.0f;
    const float dodgeDuration = 3.0f; // seconds

    // Inputs
    void jump();
    void startDodge();

	// Temporary references to platform and orb
    Entity* platform;
    Entity** orbRef;

    void handleCollision(const Entity& other);

};