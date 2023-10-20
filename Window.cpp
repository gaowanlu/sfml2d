#include"Window.h"

using crustgames::Window;

Window* Window::ptr_ = nullptr;

Window::Window() :window_(sf::VideoMode(crustgames::GAME_FRAME_WIDTH, crustgames::GAME_FRAME_HEIGHT), "SFML GAMES", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize),
view_(sf::FloatRect(0, 0, crustgames::GAME_FRAME_WIDTH, crustgames::GAME_FRAME_HEIGHT))
{
	window_.setView(view_);
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

void Window::setView(sf::Vector2f vec2f) {
	view_.setSize(vec2f.x, vec2f.y);
	view_.setCenter(vec2f / 2.0f);
	window_.setView(view_);
}