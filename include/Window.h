#pragma once
#include<SFML/Graphics.hpp>
#include"Conf.h"

namespace crustgames {
    class Window {
    public:
        static Window& Instance();
    private:
        static Window* ptr_;
    public:
        ~Window();
        sf::RenderWindow& Get();
    private:
        sf::RenderWindow window_;
        Window();
    };
}