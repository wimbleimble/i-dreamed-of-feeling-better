#include <stdio.h>
#include "ecs.h"
#include "entity.h"
#include "renderer.h"
#include "resources.h"
#include "texture.h"
#include <assert.h>
#include "cglm/cglm.h"
#include "system_render.h"

Entity create_things(ECS* ecs, Resources* resources)
{
	ShaderProgram face_thing_shader = resources_load_shader(
		resources, "shaders/sprite.vert", "shaders/sprite.frag");
	Texture face_thing_texture =
		resources_load_texture(resources, "sprites/vriska/vriska.png", true);

	Entity ent = ecs_create_entity(ecs);
	Transform* transform = ecs_assign_component(ecs, ent, TRANSFORM,
		&(Transform){.position = { 0.0f, 0.0f }, .size = { 69, 87 }});
	Sprite* sprite = ecs_assign_component(ecs, ent, SPRITE,
		&(Sprite){
			.texture = face_thing_texture,
			.shader = face_thing_shader,
			.src_rect = { 0, 0, 23, 29 },
			.tex_width = 483,
			.tex_height = 29});

	printf("sprite_tex_width: %u", sprite->tex_width);

	Entity camera = ecs_create_entity(ecs);
	ecs_assign_component(ecs, camera, TRANSFORM,
		&(Transform){.position = { 0.0f, 0.0f }, .size = { 800.0f, 600.0f }});
	return camera;
}

static inline int game_loop(ECS* ecs, RenderContext* render_context, Entity camera)
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
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
				run = false;
		}
		system_render_update(ecs, render_context, camera);
	}
	// TODO deinit

	return 0;

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
	resources_init(&resources, 1, 1);

	// Initialise ECS
	ECS ecs = {};
	ecs_init(&ecs);

	Entity camera = create_things(&ecs, &resources);
	printf("Transform size: %u\n", sizeof(Transform));
	printf("Sprite size: %u\n", sizeof(Sprite));
	printf("Camera size: %u\n", sizeof(Camera));

	return game_loop(&ecs, &render_context, camera);
}
