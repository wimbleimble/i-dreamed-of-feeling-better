#include <stdio.h>
#include "ecs.h"
#include "entity.h"
#include "renderer.h"
#include "resources.h"
#include "texture.h"
#include <assert.h>
#include "cglm/cglm.h"
#include "system_render.h"

void create_things(ECS* ecs, Resources* resources)
{
	ShaderProgram face_thing_shader = resources_load_shader(
		resources, "shaders/sprite.vert", "shaders/sprite.frag");
	Texture face_thing_texture =
		resources_load_texture(resources, "sprites/bla.png", true);
	uint8_t diameter = 800 / 32;

	for (uint8_t row = 0; row < 24; ++row)
		for (uint8_t col = 0; col < 32; ++col)
		{
			Entity ent = ecs_create_entity(ecs);
			Transform* transform = ecs_assign_component(ecs, ent, TRANSFORM,
				&(Transform){.position = { col * diameter, row * diameter }, .size = { diameter, diameter }});
			Sprite* sprite = ecs_assign_component(ecs, ent, SPRITE,
				&(Sprite){.texture = face_thing_texture, .shader = face_thing_shader });
		}
}

int main()
{
	// Set up renderer
	RenderContext render_context = {};
	assert(renderer_init(&render_context,
		"I Dreamed of Feeling Better", 800, 600, SDL_WINDOW_OPENGL));
	renderer_set_clear_colour(1.0, 1.0, 1.0, 1.0);

	// Set up resources
	Resources resources = {};
	resources_init(&resources);
	resources_set_shader_capacity(&resources, 1);
	resources_set_texture_capacity(&resources, 1);

	// Initialise ECS
	ECS ecs = { 0 };
	ecs_init(&ecs);

	create_things(&ecs, &resources);

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
		printf("FPS: %f\n", 1000.0 / delta_time);
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
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
				run = false;
		}
		system_render_update(&ecs, &render_context);
	}
	// TODO deinit

	return 0;
}
