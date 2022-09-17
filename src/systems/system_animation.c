#include "system_animation.h"

void system_animation_event(ECS* ecs, void* event)
{
	ComponentArray player_array = ecs->component_data.components[COMP_PLAYER];
	for (size_t i = 0; i < player_array.num_components; ++i)
	{
		Player* player = (Player*)(player_array.array) + i;
		Entity entity = player_array.index_to_entity[i];
		Animation* animation = ecs_get_component(ecs, entity, COMP_ANIMATION);
		switch (player->state)
		{
		case IDLE:
			animation->current_frame = 0;
			animation->start_frame = 0;
			animation->num_frames = 1;
			break;
		case UP:
			animation->current_frame = 0;
			animation->start_frame = 8;
			animation->num_frames = 2;
			break;
		case DOWN:
			animation->current_frame = 0;
			animation->start_frame = 4;
			animation->num_frames = 2;
			break;
		case LEFT:
			animation->current_frame = 0;
			animation->start_frame = 10;
			animation->num_frames = 2;
			break;
		case RIGHT:
			animation->current_frame = 0;
			animation->start_frame = 6;
			animation->num_frames = 2;
			break;
		default:
			break;
		}
	}
}

void system_animation_tick(ECS* ecs, float delta_time)
{
	ComponentArray animation_array = ecs->component_data.components[COMP_ANIMATION];
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
