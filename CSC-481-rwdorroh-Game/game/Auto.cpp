#include "Auto.h"
#include "Player.h"
#include <cmath>

// Auto constructor sets the direction toward the Player with no gravoty and collidable
Auto::Auto(float x, float y, float w, float h, const char* texturePath, const Player* target)
    : Entity(x, y, w, h, texturePath, false, true) {

    // Compute direction vector from spawn point to player
    OrderedPair targetPos = target->getPosition();
    OrderedPair selfPos = { x, y };
    float dx = targetPos.x - selfPos.x;
    float dy = targetPos.y - selfPos.y;
    float magnitude = std::sqrt(dx * dx + dy * dy);

    if (magnitude > 0) {
        direction.x = dx / magnitude;
        direction.y = dy / magnitude;
    }
    else {
        direction.x = 0;
        direction.y = 0;
    }

    Velocity v;
    v.direction = direction;
    v.magnitude = speed;
    setVelocity(v);
}


void Auto::update(float deltaTime) {
    Entity::update(deltaTime);
}

// Reset the Auto to a position and recompute direction toward the Player
void Auto::reset(Entity* orb, const Player* target, float x, float y, float speed) {
    
    if (!orb || !target) return;

    orb->setPosition({ x, y });

	// Get direction vector from new position to player
    OrderedPair targetPos = target->getPosition();
    float dx = targetPos.x - x;
    float dy = targetPos.y - y;
    float mag = std::sqrt(dx * dx + dy * dy);

    Velocity v{};
    if (mag > 0.0f) {
        v.direction = { dx / mag, dy / mag };
        v.magnitude = speed;
    }
    orb->setVelocity(v);
}
