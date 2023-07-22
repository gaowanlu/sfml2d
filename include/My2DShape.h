#pragma once

#include <list>
#include "ControllHandler.h"
#include "FPS.h"
#include "Object2D.h"
#include <SFML/Audio.hpp>

namespace crustgames {
	class Bullet{
	public:
		Bullet();
		void Next();
		bool Render();
	public:
		float x{0};
		float y{0};
		int start_x{0};
		int start_y{0};
		int mouse_x{0};
		int mouse_y{0};
		sf::Clock clock;
	};

	class Person {
	public:
		enum MoveTarget {
			LEFT = 0,
			DOWN,
			TOP,
			RIGHT
		};
	public:
		Person();
		void Render();
		void Left();
		void Right();
		void Top();
		void Down();
		void Next();
		void TouchTest();
	public:
		float x{ 0 };
		float y{ 0 };
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<std::vector<sf::IntRect>> frames;
		int currentFrame{ 0 };
		int currentFrameIndex{ 0 };
		MoveTarget moveTarget{ DOWN };
		sf::Clock clock;
	};
	
	class My2DShape :public Object2D {
	public:
		My2DShape();
		~My2DShape();
		virtual void WindowInitBefore();
		virtual void WindowInitAfter();
		virtual void EventNotifyBefore();
		virtual void EventNotifyAfter();
		virtual void Render();
		virtual void KeyPressed(sf::Event& event);
		virtual void MouseButtonPressed(sf::Event& event);
	private:
		FPS fps;
		sf::Text text;
		sf::Font font;
		float x {0};
		float y {0};
		std::list<Bullet> bullets;
		sf::Music music;
		sf::Music bgm;
		Person person;
	};
}