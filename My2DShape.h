#pragma once

#include <list>
#include "ControllHandler.h"
#include "FPS.h"
#include "Object2D.h"
#include <SFML/Audio.hpp>
#include <box2d/b2_body.h>
#include "UI.h"
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace crustgames {
	class Bullet {
	public:
		Bullet();
		void Next();
		bool Render();
	public:
		float x{ 0 };
		float y{ 0 };
		int start_x{ 0 };
		int start_y{ 0 };
		int mouse_x{ 0 };
		int mouse_y{ 0 };
		int radius{ 5 };
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
		bool TouchTest();
		void Jump();
	public:
		float x{ 0 };
		float y{ 0 };
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<std::vector<sf::IntRect>> frames;
		int currentFrame{ 0 };
		int currentFrameIndex{ 0 };
		MoveTarget moveTarget{ DOWN };
		sf::Clock renderClock;
		float jumpV{ 0 };//速度
		float m{ 0 };//质量
		float g{ 0 };//重力加速度
		sf::Clock gClock;//重力作用时钟      
		//左右加速度速度控制
		float levelV{ 0 };
		float levelA{ 0 };
		sf::Clock levelAClock;
		float scale{ 2. };
		//物理引擎
		b2BodyDef playerDef;
		b2Body* playerBody{ nullptr };
		b2PolygonShape playerShape;
		b2FixtureDef playerFixtureDef;
	};

	class Ball {
	public:
		char r;
		char g;
		char b;
		int x;
		int y;
		float radius;
	public:
		bool CollisionAABB(int otherX, int otherY, int width, int height);
		void Render();
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
		int autoBallX{ 0 };
		int autoBallY{ 0 };
		std::list<Bullet> bullets;
		std::list<Ball> balls;
		sf::Music music;
		sf::Music bgm;
		Person person;
		UI* mUIPtr{ nullptr };
	};
}