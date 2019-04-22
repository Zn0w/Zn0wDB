#pragma once

#include "frame.h"


namespace zn {

	class Layout
	{
	private:
		int marginX, marginY;

	public:
		Layout()
		{
			marginX = 1;
			marginY = 1;
		}

		Layout(int m_x, int m_y)
		{
			marginX = m_x;
			marginY = m_y;
		}

		virtual void allign(std::vector<Element> elements) = 0;
	};

}