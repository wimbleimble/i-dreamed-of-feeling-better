#include <stdio.h>
#include "ecs.h"
#include "entity.h"
#include "renderer.h"
#include "resources.h"
#include "texture.h"
#include <assert.h>
#include "cglm/cglm.h"

void test_ecs()
{
	ECS ecs = { 0 };
	ecs_init(&ecs);

	Entity ents[3];
	ents[0] = ecs_create_entity(&ecs);
	ents[1] = ecs_create_entity(&ecs);
	ents[2] = ecs_create_entity(&ecs);
	Transform* transform1 = (Transform*)ecs_assign_component(
		&ecs, ents[0], TRANSFORM,
		&(Transform){.x = 5, .y = 6, .rot = 7, .scale = 8 });
	ecs_assign_component(&ecs, ents[0], SPRITE, &(Sprite){});


	for (int i = 0; i < 3; ++i)
		printf("Entity %u, signature %u\n",
			ents[i], entity_signature(&ecs.entity_data, ents[i]));

	printf("x: %d\n", transform1->x);
	printf("y: %d\n", transform1->y);
	printf("rot: %d\n", transform1->rot);
	printf("scale: %d\n", transform1->scale);

	Transform* transform2 = (Transform*)ecs_get_component(
		&ecs, ents[0], TRANSFORM
	);

	printf("tranform1: %p, transform2: %p\n", transform1, transform2);
	printf("x: %d\n", transform2->x);
	printf("y: %d\n", transform2->y);
	printf("rot: %d\n", transform2->rot);
	printf("scale: %d\n", transform2->scale);


	ecs_destroy_entity(&ecs, ents[0]);
	ecs_destroy_entity(&ecs, ents[1]);
	ecs_destroy_entity(&ecs, ents[2]);

}

int main()
{
	RenderContext render_context = {};
	assert(renderer_init(&render_context,
		"I Dreamed of Feeling Better", 800, 600, SDL_WINDOW_OPENGL));

	Resources resources = {};
	// Currently does nothing
	resources_init(&resources);
	resources_set_shader_capacity(&resources, 1);
	resources_set_texture_capacity(&resources, 1);
	renderer_set_clear_colour(1.0, 1.0, 1.0, 1.0);
	ShaderProgram shader = resources_load_shader(
		&resources, "shaders/sprite.vert", "shaders/sprite.frag");

	Texture bla_texture =
		resources_load_texture(&resources, "sprites/bla.png", true);

	bool run = true;
	while (run)
	{
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
		renderer_clear();
		vec2 pos = { 0.0f, 0.0f };
		vec2 size = { 200.0f, 200.0f };
		renderer_draw_2D_texture(
			&render_context,
			bla_texture,
			shader,
			pos,
			size);
		renderer_swap_buffer(&render_context);

	}

	return 0;
}
