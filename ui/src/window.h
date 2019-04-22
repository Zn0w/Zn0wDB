#pragma once

#include "frame.h"

namespace zn {

	class Window
	{
	private:
		int x, y, width, height;
		const char* title;
		Frame* currentFrame;
		bool visible;

	public:
		Window(const char* t)
			: title(t)
		{}

		Window(int s_x, int s_y, int s_width, int s_height, const char* t)
			: x(s_x), y(s_y), width(s_width), height(s_height), title(t)
		{}

		inline int getX() { return x; }
		inline int getY() { return y; }
		inline int getWidth() { return width; }
		inline int getHeight() { return height; }

		inline void setX(int s_x) { x = s_x; }
		inline void setY(int s_y) { y = s_y; }
		inline void setWidth(int s_width) { width = s_width; }
		inline void setHeight(int s_height) { height = s_height; }

		inline void setFrame(Frame* frame) { currentFrame = frame; }
		inline Frame* getFrame() { return currentFrame; }

		inline void setVisible(bool v) { visible = v; }
		inline bool isVisible() { return visible; }

		void pack()
		{
			// Set window size by the elements aligned
		}
	};

}