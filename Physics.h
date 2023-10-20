#pragma once
#include<box2d/box2d.h>
#include"Conf.h"

namespace crustgames {
	class Physics {
	public:
		static Physics& Instance();
	private:
		static Physics* ptr_;
	public:
		b2Vec2 gravity_;
		b2World world_;
	public:
		~Physics();
	private:
		Physics();
	};
}