#include "system_render.h"
#include "ecs.h"

void system_render_update(ECS* ecs, RenderContext* render_context)
{
	renderer_clear();
	ComponentArray sprite_array = ecs->component_data.components[SPRITE];

	for (size_t i = 0; i < sprite_array.num_components; ++i)
	{
		Entity entity = sprite_array.index_to_entity[i];
		Transform* transform = ecs_get_component(ecs, entity, TRANSFORM);
		Sprite* sprite = (Sprite*)(sprite_array.array) + i;
		renderer_draw_2D_texture(
			render_context,
			sprite->texture,
			sprite->shader,
			transform->position,
			transform->size
		);
	}

	renderer_swap_buffer(render_context);
}