#include <engine/Engine.h>
#include <engine/Input.h>
#include <engine/Physics.h>
#include <engine/Collision.h>
#include <engine/Entity.h>
#include <SDL3/SDL.h>
#include <iostream>

// Static members initialization, and core components for the engine working
SDL_Window* Engine::s_window = nullptr;
SDL_Renderer* Engine::s_renderer = nullptr;
bool Engine::s_running = false;
std::vector<Entity*> Engine::s_entities;

/**
 * Initializes the SDL and events, and creates the game window and renderer.
 * @param cfg The configuration struct containing window title, width, and height.
 * @return true if initialization is successful, false otherwise.
 */
bool Engine::init(const Config& cfg) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
    // Create the game window.
	s_window = SDL_CreateWindow(cfg.title, cfg.width, cfg.height, SDL_WINDOW_RESIZABLE);
	if (!s_window) {
		SDL_Log("Couldn't create window: %s", SDL_GetError());
		return false;
	}
    // Create the renderer for drawing.
	s_renderer = SDL_CreateRenderer(s_window, nullptr);
	if (!s_renderer) {
		SDL_Log("Couldn't create renderer: %s", SDL_GetError());
		return false;
	}
	return true;
}

/**
 * Cleans up all resources used by the engine.
 * This includes deleting all entities, destroying the renderer and the window.
 */
void Engine::shutdown() {
    // Clean up all allocated entity objects
	for (Entity* entity : s_entities) {
		delete entity;
	}
	s_entities.clear();
	SDL_DestroyRenderer(s_renderer);
	SDL_DestroyWindow(s_window);
	SDL_Quit();
}

/**
 * Adds a new entity to the engine's list of managed entities.
 * @param entity A pointer to the entity to add.
 */
void Engine::addEntity(Entity* entity) {
	s_entities.push_back(entity);
}

/**
 * The main game loop. It handles events, updates game state, and renders the scene.
 * @param update The function to call for game state updates.
 * @param render The function to call for custom render logic.
 */
void Engine::run(std::function<void(float)> update, std::function<void(void)> render) {
	s_running = true;
	SDL_Event e;
	Uint64 lastTime = SDL_GetTicks();// Get initial time for delta time calculation
	while (s_running) {
        // Process all pending SDL events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				s_running = false;
			}
		}
        // Update the keyboard state once per frame for consistent inputs
		Input::updateKeyboardState();
        // Calculate delta time
		Uint64 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		update(deltaTime);
		render();
        // Set the background color blue and clear the screen
		SDL_SetRenderDrawColor(s_renderer, 0, 200, 255, 255);
		SDL_RenderClear(s_renderer);
        // Draw all entities managed by the engine
		for (Entity* entity : s_entities) {
			entity->draw();
		}
		SDL_RenderPresent(s_renderer);
	}
}

/**
 * Provides access to the global SDL renderer instance.
 * @return A pointer to the SDL_Renderer.
 */
SDL_Renderer* Engine::getRenderer() {
	return s_renderer;
}
