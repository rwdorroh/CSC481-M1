#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>
#include <engine/Engine.h>
#include <engine/Input.h>
#include <engine/Physics.h>
#include "Static.h"
#include "Player.h"
#include "Auto.h"


int main(int argc, char* argv[]) {

	// Configure the engine window
    Engine::Config config;
	config.title = "CSC 481 Game";
	config.width = 1920;
	config.height = 1080;

    // Initialize the engine
    if (!Engine::init(config)) {
        SDL_Log("Failed to initialize engine: %s", SDL_GetError());
        return 1;  // Failed to init SDL
    }

    // Increase gravity for this session
    Physics::setGravity(200.0f);

	// Add a static entity to the game world representing a brick platform
	Static* brickPlatform = new Static(300.0f, 800.0f, 96.0f, 32.0f, "assets/Brick.png");

    // Pointer to the orb entity (initialized when spawned)
    Entity* orb = nullptr;

	// Add the player entity above the platform
    Player* player = new Player(300.0f, 500.0f, 64.0f, 64.0f, "assets/Morwen.png", brickPlatform, &orb);

    Engine::addEntity(brickPlatform); // Add to engine's entity list
	Engine::addEntity(player); // Add to engine's entity list

    // Orb spawn position (top-right)
    const float ORB_W = 128.0f, ORB_H = 128.0f;
    const float ORB_SPAWN_X = 1920.0f - ORB_W;
    const float ORB_SPAWN_Y = 0.0f;

    // simple key latch
    bool enterHeld = false;

    // Main game loop
    Engine::run(
        [&](float deltaTime) {
            player->update(deltaTime);

            // Move orb if it exists
            if (orb) {
                orb->update(deltaTime);
            }

			// Spawn orb or reset its position on Enter key press
            bool enterNow = Input::isKeyPressed(SDL_SCANCODE_RETURN);
            if (enterNow && !enterHeld) {
                if (!orb) {
                    // first-time spawn
                    orb = new Auto(ORB_SPAWN_X, ORB_SPAWN_Y, ORB_W, ORB_H, "assets/Orb.png", player);
                    Engine::addEntity(orb);
                }
                else {
                    // reset existing orb back to spawn and re-aim
                    Auto::reset(orb, player, ORB_SPAWN_X, ORB_SPAWN_Y);
                }
            }
            enterHeld = enterNow;
        },
        []() {
            // No custom render logic yet
        }
    );

	// Shutdown the engine and clean up resources
    Engine::shutdown();
    return 0;
}
