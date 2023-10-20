#include"Physics.h"

using crustgames::Physics;

Physics* Physics::ptr_ = nullptr;

Physics::Physics() :
	gravity_(0.f, 0.f),
	world_(gravity_) {

}

Physics::~Physics() {

}

Physics& Physics::Instance() {
	if (ptr_ == nullptr) {
		ptr_ = new Physics;
	}
	return*ptr_;
}
