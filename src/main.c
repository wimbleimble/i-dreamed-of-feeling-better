#include <stdio.h>
#include "ecs.h"
#include "entity.h"
#include "renderer.h"
#include "resource_manager.h"

int main()
{
	RenderContext render_context = {};
	renderer_init(&render_context,
		"I Dreamed of Feeling Better", 200, 200, SDL_WINDOW_OPENGL);

	Resources resources = {};
	// Currently does nothing
	resource_init(&resources);
	resource_set_shader_capacity(&resources, 1);
	ShaderProgram shader = resource_load_shader(
		&resources, "shaders/sprite.vert", "shaders/sprite.frag");

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


	return 0;
}

