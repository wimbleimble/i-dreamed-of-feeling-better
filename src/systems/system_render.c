#include "system_render.h"

#include "rect.h"

void system_render_update(
    ECS* ecs, RenderContext* render_context, Entity camera)
{
    renderer_clear();
    ComponentArray sprite_array = ecs->component_data.components[COMP_SPRITE];
    Transform* camera_transform =
        ecs_get_component(ecs, camera, COMP_TRANSFORM);

    for (size_t i = 0; i < sprite_array.num_components; ++i)
    {
        const Entity entity = sprite_array.index_to_entity[i];
        const ComponentSignature sig =
            entity_signature(&ecs->entity_data, entity);
        const Transform* transform =
            ecs_get_component(ecs, entity, COMP_TRANSFORM);
        const Sprite* sprite = (Sprite*)(sprite_array.array) + i;
        Rect frame = { 0, 0, sprite->texture.width, sprite->texture.height };
        if (sig & COMP_SIG(COMP_ANIMATOR))
        {
            const Animator* animation =
                ecs_get_component(ecs, entity, COMP_ANIMATOR);
            const uint16_t frame_width =
                sprite->texture.width / animation->sheet_frames;
            const uint16_t frame_offset =
                (animation->current_frame
                 + animation->current_animation.start_frame)
                * frame_width;

            frame = (Rect){ frame_offset,
                            0,
                            frame_offset + frame_width,
                            sprite->texture.height };
        }

        renderer_draw_2D_sprite(
            render_context,
            sprite,
            &frame,
            transform->position,
            transform->size,
            camera_transform->position,
            camera_transform->size);
    }

    renderer_swap_buffer(render_context);
}
