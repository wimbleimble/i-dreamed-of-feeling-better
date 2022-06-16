#include "system_render.h"
#include "rect.h"

void system_render_update(ECS* ecs, RenderContext* render_context, Entity camera)
{
	renderer_clear();
	ComponentArray sprite_array = ecs->component_data.components[SPRITE];
	Transform* camera_transform = ecs_get_component(ecs, camera, TRANSFORM);

	for (size_t i = 0; i < sprite_array.num_components; ++i)
	{
		Entity entity = sprite_array.index_to_entity[i];
		ComponentSignature sig = entity_signature(&ecs->entity_data, entity);
		Transform* transform = ecs_get_component(ecs, entity, TRANSFORM);
		Sprite* sprite = (Sprite*)(sprite_array.array) + i;
		Rect frame = sig & COMP_SIG(ANIMATOR) ?
			((Animator*)ecs_get_component(ecs, entity, ANIMATOR))->frame
			: (Rect){0, 0, sprite->texture.width, sprite->texture.height };
		
		renderer_draw_2D_sprite(
			render_context,
			sprite,
			&frame,
			transform->position,
			transform->size,
			camera_transform->position,
			camera_transform->size
		);
	}

	renderer_swap_buffer(render_context);
}