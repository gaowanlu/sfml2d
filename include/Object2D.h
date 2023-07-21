#pragma once

#include "ControllHandler.h"

namespace crustgames {
	class Object2D:public ControllHandler
	{
	public:
		virtual void Render() = 0;
	};
}