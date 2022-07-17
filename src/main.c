#include <stdio.h>
#include "ecs.h"
#include "event_bus.h"
#include "entity.h"
#include "renderer.h"
#include "resources.h"
#include "texture.h"
#include <assert.h>
#include "cglm/cglm.h"
#include "system_render.h"
#include "system_animation.h"
#include "system_movement.h"

// Create Vriska
// Doesn't matter that this goes out of scope. vriska exists whether you
// want her to or not. her lifetime is not bound to her relevance.
Entity create_vriska(ECS* ecs, Resources* resources)
{
	ShaderProgram vriska_shader = resources_load_shader(
		resources, "shaders/sprite.vert", "shaders/sprite.frag");
	Texture vriska_texture =
		resources_load_texture(resources, "sprites/vriska/vriska.png", true);

	Entity vriska = ecs_create_entity(ecs);

	ecs_assign_component(ecs, vriska, COMP_TRANSFORM, &(Transform){
		.position = { 0.0f, 0.0f },
		.size = { 69, 87 }});
	ecs_assign_component(ecs, vriska, COMP_SPRITE, &(Sprite){
		.texture = vriska_texture,
		.shader = vriska_shader});
	ecs_assign_component(ecs, vriska, COMP_ANIMATION, &(Animation){
		.fps = 8,
		.start_frame = 4,
		.num_frames = 2,
		.sheet_frames = 21});
	ecs_assign_component(ecs, vriska, COMP_PLAYER, &(Player){
		.speed = 35,
		.run_mult = 1.7f,
		.state = IDLE});

	return vriska;
}

Entity create_camera(ECS* ecs, Resources* resources)
{

	Entity camera = ecs_create_entity(ecs);
	ecs_assign_component(ecs, camera, COMP_TRANSFORM,
		&(Transform){.position = { 0.0f, 0.0f }, .size = { 800.0f, 600.0f }});
	return camera;
}

static inline int game_loop(
	ECS* ecs,
	EventBus event_bus,
	RenderContext* render_context,
	Entity camera,
	Entity vriska)
{
	uint64_t curr_time = SDL_GetPerformanceCounter();
	uint64_t prev_time = 0;

	bool run = true;
	while (run)
	{
		prev_time = curr_time;
		curr_time = SDL_GetPerformanceCounter();
		double delta_time =
			((double)(curr_time - prev_time) * 1000.0)
			/ (double)SDL_GetPerformanceFrequency();

		// printf("FPS: %f\n", 1000.0 / delta_time);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					run = false;
					break;
				case SDLK_b:
					ecs_remove_component(ecs, vriska, COMP_PLAYER);
					printf("Removing player component from vriska.\n");
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
				run = false;
		}
		event_bus_dispatch(event_bus, ecs);
		system_animation_tick(ecs, (float)delta_time);
		system_movement_tick(ecs, event_bus, (float)delta_time);
		system_render_update(ecs, render_context, camera);
	}

	return 0;

}

int main()
{
	RenderContext render_context = {};
	assert(renderer_init(&render_context,
		"I Dreamed of Feeling Better", 800, 600, SDL_WINDOW_OPENGL));
	renderer_set_clear_colour(1.0, 1.0, 1.0, 1.0);

	Resources resources = {};
	resources_init(&resources, 1, 1);

	ECS ecs = {};
	ecs_init(&ecs);

	EventBus event_bus = {};
	event_bus_init(event_bus);

	Entity camera = create_camera(&ecs, &resources);
	Entity vriska = create_vriska(&ecs, &resources);
	return game_loop(&ecs, event_bus, &render_context, camera, vriska);
}
