#include "system_movement.h"

#include "input.h"
#include "player.h"

#include <SDL2/SDL.h>

void system_movement_tick(ECS* ecs, EventBus* event_bus, float delta_time)
{
    ComponentArray player_array = ecs->component_data.components[COMP_PLAYER];
    for (size_t i = 0; i < player_array.num_components; ++i)
    {
        const Entity entity = player_array.index_to_entity[i];
        Player* player = (Player*)(player_array.array) + i;
        Transform* transform = ecs_get_component(ecs, entity, COMP_TRANSFORM);

        // TODO add a layer above input to abstract intent.
        const uint8_t up =
            input_key_state(SDL_SCANCODE_W) || input_key_state(SDL_SCANCODE_UP);
        const uint8_t down = input_key_state(SDL_SCANCODE_S)
            || input_key_state(SDL_SCANCODE_DOWN);
        const uint8_t left = input_key_state(SDL_SCANCODE_A)
            || input_key_state(SDL_SCANCODE_LEFT);
        const uint8_t right = input_key_state(SDL_SCANCODE_D)
            || input_key_state(SDL_SCANCODE_RIGHT);
        const uint8_t shift = input_key_state(SDL_SCANCODE_LSHIFT);

        const float speed =
            0.01f * player->speed * (1.0f + shift * (player->run_mult - 1.0f));

        // Euler, bitch.
        // Doing it this way means that diagonal speed is very slightly faster
        // (by a factor of root 2). I could do this a better way by creating a
        // normalized direction vectory and then mutlipying it by the speed
        // scalar.
        vec2 velocity = {
            speed * delta_time * (right - left),
            speed * delta_time * (up - down),
        };

        PlayerState state = up | (down << 1) | (left << 2) | (right << 3);

        if (player->state != state)
        {
            player->state = state;
            uint64_t event;
            switch (state)
            {
            case IDLE:
                event = 0;
                event_bus_post(event_bus, SYS_SIG(SYS_ANIMATION), &event);
                break;
            case UP:
                event = 1;
                event_bus_post(event_bus, SYS_SIG(SYS_ANIMATION), &event);
                break;
            case DOWN:
                event = 2;
                event_bus_post(event_bus, SYS_SIG(SYS_ANIMATION), &event);
                break;
            case LEFT:
                event = 3;
                event_bus_post(event_bus, SYS_SIG(SYS_ANIMATION), &event);
                break;
            case RIGHT:
                event = 4;
                event_bus_post(event_bus, SYS_SIG(SYS_ANIMATION), &event);
                break;
            default:
                break;
            }
        }

        vec2 old_pos;
        glm_vec2_copy(transform->position, old_pos);
        glm_vec2_add(velocity, old_pos, transform->position);
    }
}
