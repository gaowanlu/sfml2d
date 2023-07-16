#pragma once
#include<SFML/Graphics.hpp>

namespace crustgames {
    class FPS {
    public:
        void Show();
        int Get();
    private:
        int fps_{ 0 };
        int frame_{ 0 };
        sf::Clock clock_;
    };
}