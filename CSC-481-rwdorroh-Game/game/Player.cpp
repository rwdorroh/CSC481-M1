#include "Player.h"
#include "Static.h"
#include "Auto.h"
#include <engine/Collision.h>
#include <engine/Physics.h>
#include <engine/Input.h>
#include <vector>


// Player entity with gravity and collision on by default
Player::Player(float x, float y, float w, float h, const char* texturePath, Entity* platformEntity, Entity** orbEntityRef)
    : Entity(x, y, w, h, texturePath, true, true),
    platform(platformEntity), orbRef(orbEntityRef) {
}

void Player::update(float deltaTime) {
    isOnGround = false;

    // Dodge timer
    if (dodgeActive) {
        dodgeTimer -= deltaTime;
        if (dodgeTimer <= 0.0f) {
            dodgeActive = false;
        }
    }

    // Apply physics
    Entity::update(deltaTime);

    if (platform) {
        float platformTop = platform->getPosition().y;
        float playerBottom = getPosition().y + getRect().h;

        if (playerBottom >= platformTop) {
            OrderedPair pos = getPosition();
            pos.y = platformTop - getRect().h;
            setPosition(pos);

            Velocity v = getVelocity();
            v.direction = { 0, 0 };
            v.magnitude = 0.0f;
            setVelocity(v);

            isOnGround = true;
        }
    }

    // Manual collision check: orb
    if (*orbRef && Collision::checkCollision(*this, **orbRef)) {
        if (!dodgeActive) {
            handleCollision(**orbRef);
        }
    }

    // Input
    if (isOnGround && Input::isKeyPressed(SDL_SCANCODE_W)) {
        jump();
    }

    if (Input::isKeyPressed(SDL_SCANCODE_S) && !dodgeActive) {
        startDodge();
    }
}

// Handles collision with the orb by resetting player position and velocity
void Player::handleCollision(const Entity& other) {
    if (orbRef && *orbRef && &other == *orbRef) {
        setPosition({ 300.0f, 500.0f });
        setVelocity({ {0, 0}, 0 });
    }
}

// Initiates the dodge state
void Player::startDodge() {
    dodgeActive = true;
    dodgeTimer = dodgeDuration;
}

// Makes the player jump if on the ground
void Player::jump() {
    Velocity v = getVelocity();
    v.direction.x = 0;
    v.direction.y = -1;  // Upward direction
    v.magnitude = 500.0f;  // Tune this value to jump height
    setVelocity(v);
}
