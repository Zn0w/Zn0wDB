#pragma once

#include <vector>

#include "element.h"


namespace zn {

	enum Layout
	{
		NO,
		SEQUENCE_X,
		SEQUENCE_Y,
	};

	class Frame
	{
	private:
		Layout layout;
		std::vector<Element> elements;

	public:
		Frame()
		{
			layout = NO;
		}
		
		Frame(Layout l)
		{
			layout = l;
		}

		inline void setLayout(Layout l) { layout = l; }
		inline Layout getLayout() { return layout; }

		void addElement(Element e)
		{
			elements.push_back(e);
		}

		Element* getElement(int index)
		{
			if (index > 0 && index < elements.size())
				return &elements.at(index);
			else
				return NULL;
		}

		Element* getElement(Element e)
		{
			for (Element element : elements)
			{
				// TODO
			}

			return NULL;
		}

		void allignElements()
		{
			// TODO
		}
	};

}