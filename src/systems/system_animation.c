#include "system_animation.h"

void system_animation_tick(ECS* ecs, float delta_time)
{
	ComponentArray animation_array = ecs->component_data.components[ANIMATION];
	for (size_t i = 0; i < animation_array.num_components; ++i)
	{
		Animation* animation = (Animation*)(animation_array.array) + i;
		const float frame_time = 1000.0f / animation->fps;

		if ((animation->t_since_frame += delta_time) < frame_time)
			continue;

		animation->t_since_frame = 0.0f;
		animation->current_frame =
			animation->current_frame == animation->num_frames - 1 ? 0
			: animation->current_frame + 1;
	}
}
