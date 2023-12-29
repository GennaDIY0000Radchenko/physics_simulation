#include <iostream>
#include <cmath>

#include "engine/window_context_handler.hpp"
#include "engine/common/color_utils.hpp"

#include "physics/physics.hpp"
#include "thread_pool/thread_pool.hpp"
#include "renderer/renderer.hpp"


int main()
{
    const uint32_t window_width  = 1920;
    const uint32_t window_height = 980;
    WindowContextHandler app("Physics Simulation", sf::Vector2u(window_width, window_height), sf::Style::Default);
    RenderContext& render_context = app.getRenderContext();
    // Initialize solver and renderer

    tp::ThreadPool thread_pool(10);
    const IVec2 world_size{100, 300};
    PhysicSolver solver{world_size, thread_pool};
    Renderer renderer(solver, thread_pool);

    const float margin = 20.0f;
    const auto  zoom   = static_cast<float>(window_height - margin) / static_cast<float>(world_size.y);
    render_context.setZoom(zoom);
    render_context.setFocus({world_size.x * 0.5f, world_size.y * 0.5f});

    bool emit = true;
    app.getEventManager().addKeyPressedCallback(sf::Keyboard::Space, [&](sfev::CstEv) {
        emit = !emit;
    });

    app.getEventManager().addKeyPressedCallback(sf::Keyboard::Backspace, [&](sfev::CstEv) {
        solver.deleteAllObjects();
     });

    constexpr uint32_t fps_cap = 60;
    int32_t target_fps = fps_cap;
    app.getEventManager().addKeyPressedCallback(sf::Keyboard::S, [&](sfev::CstEv) {
        target_fps = target_fps ? 0 : fps_cap;
        app.setFramerateLimit(target_fps);
    });

    bool stop = false;
    app.getEventManager().addKeyPressedCallback(sf::Keyboard::P, [&](sfev::CstEv) {
        stop = !stop;
    });

    // Main loop
    const float dt = 1.0f / static_cast<float>(fps_cap);
    while (app.run()) {
        if ( solver.objects.size() < 1 && emit && !stop ) {
            // Gravity and air friction   !!! world_size{300, 300} !!!
            /*for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ world_size.x - 2.0f, 100.0f + 1.1f * i });
                solver.objects[id].last_position.x += 0.2f;
                solver.objects[id].last_position.y += 0.01f;
                solver.objects[id].VELOCITY_DAMPING = 0.0f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.002f + 2.5f);
            }
            for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ world_size.x - 2.0f, 105.5f + 1.1f * i });
                solver.objects[id].last_position.x += 0.2f;
                solver.objects[id].last_position.y += 0.01f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.002f + 2.5f);
            }*/


            // Two particles solision  !!! world_size{100, 100} !!!
            /*for (uint32_t i{ 1 }; i--;) {
                const auto id = solver.createObject({ 2.0f, world_size.y / 2 + 1.1f * i });
                solver.objects[id].last_position.x -= 0.2f;
                solver.objects[id].last_position.y += 0.01f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f + 1.5f);
            }
            for (uint32_t i{ 1 }; i--;) {
                const auto id = solver.createObject({ world_size.x - 2.0f, world_size.y / 2 + 1.1f * i + 0.7f });
                solver.objects[id].last_position.x += 0.2f;
                solver.objects[id].last_position.y += 0.01f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f);
            }*/


            // Two streams colision  !!! world_size{300, 300} !!!
            /*for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ 2.0f, 100.0f + 1.1f * i });
                solver.objects[id].last_position.x -= 0.2f;
                solver.objects[id].last_position.y += 0.05f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f + 1.5f);
            }
            for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ world_size.x - 2.0f, 100.0f + 1.1f * i });
                solver.objects[id].last_position.x += 0.2f;
                solver.objects[id].last_position.y += 0.05f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f);
            }*/


            // Two streams & wall  
            /*for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ 2.0f, world_size.y / 3 + 1.1f * i });
                solver.objects[id].last_position.x -= 0.2f;
                solver.objects[id].last_position.y += 0.05f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f + 1.5f);
            }
            for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ 2.0f, world_size.y * 2 / 3 + 1.1f * i });
                solver.objects[id].last_position.x -= 0.2f;
                solver.objects[id].last_position.y += 0.1f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f);
            }*/


            // Waterfal & stream   !!! world_size{300, 300} !!!
            /*for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ 2.0f + 1.1f * i, 2.0f });
                solver.objects[id].last_position.x -= 0.01f;
                solver.objects[id].last_position.y -= 0.14f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.0001f);
            }
            for (uint32_t i{ 5 }; i--;) {
                const auto id = solver.createObject({ world_size.x - 2.0f, 100.0f + 1.1f * i });
                solver.objects[id].last_position.x += 0.2f;
                solver.objects[id].last_position.y += 0.01f;
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.0001f);
            }*/


            // Cumulative parabola   !!! world_size{100, 300} !!!
            /*for (uint32_t q{ 150 }; q--;) {
                for (uint32_t i{ 96 + ((q+1) % 2) }; i--;) {
                    float x_pos = 2.0f + 0.5f * (q % 2) + 1.0f * i;
                    float y_pos = world_size.y - (10.0f + 1.2f * q);
                    if ( 1.0f * (y_pos - (world_size.y - 20)) >= - pow((x_pos - (world_size.x / 2)), 2) )
                    {
                        const auto id = solver.createObject({ x_pos , y_pos });
                        solver.objects[id].last_position.x -= 0.0f;
                        solver.objects[id].last_position.y -= 0.15f;
                        solver.objects[id].color = ColorUtils::getRainbow(id * 0.0001f);
                    }
                }
            }*/


            // Cumulative triangle   !!! world_size{150, 300} !!!
            /*for (uint32_t q{ 150 }; q--;) {
                for (uint32_t i{ 146 + ((q + 1) % 2) }; i--;) {
                    float x_pos = 2.0f + 0.5f * (q % 2) + 1.0f * i;
                    float y_pos = world_size.y - (10.0f + 1.2f * q);
                    if (y_pos - (world_size.y - 20) >= -abs(3.5f * (x_pos - (world_size.x / 2))))
                    {
                        const auto id = solver.createObject({ x_pos , y_pos });
                        solver.objects[id].last_position.x -= 0.0f;
                        solver.objects[id].last_position.y -= 0.1f;
                        solver.objects[id].color = ColorUtils::getRainbow(id * 0.0001f);
                    }
                }
            }*/
        }

        if ( !stop )
        {
            solver.update(dt);

            render_context.clear();
            renderer.render(render_context);
            render_context.display();
        }
    }

    return 0;
}
