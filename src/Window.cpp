#include"Window.h"

using crustgames::Window;

Window* Window::ptr_ = nullptr;

Window::Window() :window_(sf::VideoMode(crustgames::GAME_FRAME_WIDTH, crustgames::GAME_FRAME_HEIGHT), "SFML GAMES", sf::Style::Close|sf::Style::Fullscreen ) {//| sf::Style::Titlebar|| sf::Style::Resize
    window_.setPosition(sf::Vector2i(0, 0));
    window_.setSize(sf::Vector2u(crustgames::GAME_FRAME_WIDTH, crustgames::GAME_FRAME_HEIGHT));
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(crustgames::GAME_FPS_LIMIT);
}

Window::~Window() {
    if (ptr_ != nullptr) {
        if (ptr_->Instance().Get().isOpen()) {
            ptr_->Instance().Get().close();
        }
    }
}

sf::RenderWindow& Window::Get() {
    return window_;
}

Window& Window::Instance() {
    if (ptr_ == nullptr) {
        ptr_ = new Window;
    }
    return*ptr_;
}