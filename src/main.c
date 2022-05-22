#include <stdio.h>
#include "ecs.h"
#include "entity.h"
#include "renderer.h"
#include "resources.h"
#include "texture.h"
#include <assert.h>
#include "cglm/cglm.h"
#include "system_render.h"

// void test_ecs()
// {
// 	ECS ecs = { 0 };
// 	ecs_init(&ecs);

// 	Entity ents[3];
// 	ents[0] = ecs_create_entity(&ecs);
// 	ents[1] = ecs_create_entity(&ecs);
// 	ents[2] = ecs_create_entity(&ecs);
// 	Transform* transform1 = (Transform*)ecs_assign_component(
// 		&ecs, ents[0], TRANSFORM,
// 		&(Transform){.x = 5, .y = 6, .width = 7, .height = 8 });
// 	ecs_assign_component(&ecs, ents[0], SPRITE, &(Sprite){});


// 	for (int i = 0; i < 3; ++i)
// 		printf("Entity %u, signature %u\n",
// 			ents[i], entity_signature(&ecs.entity_data, ents[i]));

// 	printf("x: %d\n", transform1->x);
// 	printf("y: %d\n", transform1->y);

// 	Transform* transform2 = (Transform*)ecs_get_component(
// 		&ecs, ents[0], TRANSFORM
// 	);

// 	printf("tranform1: %p, transform2: %p\n", transform1, transform2);
// 	printf("x: %d\n", transform2->x);
// 	printf("y: %d\n", transform2->y);


// 	ecs_destroy_entity(&ecs, ents[0]);
// 	ecs_destroy_entity(&ecs, ents[1]);
// 	ecs_destroy_entity(&ecs, ents[2]);

// }

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
	ShaderProgram face_thing_shader = resources_load_shader(
		&resources, "shaders/sprite.vert", "shaders/sprite.frag");
	Texture face_thing_texture =
		resources_load_texture(&resources, "sprites/bla.png", true);

	// Initialise ECS
	ECS ecs = { 0 };
	ecs_init(&ecs);

	// Set up entities
	struct {
		Entity id;
		Transform* transform;
		Sprite* sprite;
	} face_thing;

	face_thing.id = ecs_create_entity(&ecs);
	face_thing.transform = ecs_assign_component(
		&ecs, face_thing.id, TRANSFORM,
		&(Transform){.position = { 200, 200 }, .size = { 200, 200 }});
	face_thing.sprite = ecs_assign_component(
		&ecs, face_thing.id, SPRITE,
		&(Sprite){.texture = face_thing_texture, .shader = face_thing_shader });

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
				case SDLK_LEFT:
					face_thing.transform->position[0] -= (1 * delta_time);
					break;
				case SDLK_RIGHT:
					face_thing.transform->position[0] += (1 * delta_time);
					break;
				case SDLK_DOWN:
					face_thing.transform->position[1] -= (1 * delta_time);
					break;
				case SDLK_UP:
					face_thing.transform->position[1] += (1 * delta_time);
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

	return 0;
}
