/*
 * Copyright (c) MrZoraman 2021
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "Blyss.hpp"

#include <cstdint>

#include <boost/log/trivial.hpp>
#include <glm/vec3.hpp>

#include "StaticSceneObject.hpp"

namespace blyss
{
    Blyss::Blyss(std::int32_t window_width, std::int32_t window_height)
        : gui_{}
        , renderer_{}
        , camera_{std::make_shared<Camera>(window_width, window_height)}
        , input_{std::make_shared<InputSystem>()}
    {
        std::shared_ptr<StaticGeometry> geom = renderer_.GetStaticLoader()->LoadGeometry("../models/plane.obj");
        auto object = std::make_shared<StaticSceneObject>(geom);
        object->SetPosition(glm::vec3(0, 0, -1));
        renderer_.AddObject(object);

        camera_->SetPosition(glm::vec3{ 1, 0, 5 });

        input_->on_key_press.connect(
            [](InputButton button)
            {
                if (button == InputButton::kMouseCaptureToggle)
                {
                    BOOST_LOG_TRIVIAL(info) << "Toggle mouse capture!";
                }
            });
    }

    void Blyss::Frame(double delta_seconds)
    {
        // All the ImGui draw calls are done here.
        gui_.Draw(delta_seconds);

        // Draw everything else on the screen.
        renderer_.Draw(*camera_);
    }

    bool Blyss::IsCloseRequested() const
    {
        return gui_.IsCloseRequested();
    }

    std::shared_ptr<Camera> Blyss::GetCamera()
    {
        return camera_;
    }

    std::shared_ptr<InputSystem> Blyss::GetInput()
    {
        return input_;
    }

}