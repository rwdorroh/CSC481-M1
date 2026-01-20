#pragma once

#include <SDL3/SDL.h>
#include <engine/Types.h>

// The Entity class represents any object in the game world that can be rendered.
class Entity {

public:
	// Entity constructor and destructor
	Entity(float x, float y, float w, float h, const char* texturePath, bool affectedByGravity, bool collidable);
	~Entity();
	// Update the entity based on time passed
	void update(float deltaTime);
	// Draw the texture of the entity
	void draw();
	// Velocity functions
	void setVelocity(const Velocity& v);
	Velocity getVelocity() const;
	// Position functions
	void setPosition(const OrderedPair& p);
	OrderedPair getPosition() const;
	// Gravity functions
	void setAffectedByGravity(bool enabled);
	bool isAffectedByGravity() const;
	// Collisions functions
	void setCollidable(bool enabled);
	bool isCollidable() const;
	// Get the rect of the entity
	SDL_FRect getRect() const;
private:
    // Core properties of the entity
	OrderedPair position;
	OrderedPair dimensions;
	Velocity velocity;
    // Flags to control physics and collision behavior
	bool applyGravity;
	bool collidable;
    // The SDL texture for rendering the entity
	SDL_Texture* texture;
};