#pragma once

#include "frame.h"

namespace zn {

	struct Window
	{
		int x, y, width, height;
		const char* title;
		Frame* currentFrame;
	};

}