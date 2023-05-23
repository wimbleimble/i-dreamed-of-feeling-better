#include "system_animation.h"
#include <stdio.h>

void system_animation_event(ECS* ecs, void* event)
{
    ComponentArray player_array = ecs->component_data.components[COMP_PLAYER];
    printf("CAll me!\n");
    for (size_t i = 0; i < player_array.num_components; ++i)
    {
        Player* player = (Player*)(player_array.array) + i;
        Entity entity = player_array.index_to_entity[i];
        Animator* animator = ecs_get_component(ecs, entity, COMP_ANIMATOR);
        Animations* animations =
            ecs_get_component(ecs, entity, COMP_ANIMATIONS);
        animator->current_animation = animations->list[*(uint64_t*)event];
    }
}

void system_animation_tick(ECS* ecs, float delta_time)
{
    ComponentArray animator_array =
        ecs->component_data.components[COMP_ANIMATOR];
    for (size_t i = 0; i < animator_array.num_components; ++i)
    {
        Animator* animator = (Animator*)(animator_array.array) + i;
        const float frame_time = 1000.0f / animator->fps;

        if ((animator->t_since_frame += delta_time) < frame_time)
            continue;

        animator->t_since_frame = 0.0f;
        animator->current_frame = animator->current_frame
                == animator->current_animation.num_frames - 1 ?
            0 :
            animator->current_frame + 1;
    }
}
