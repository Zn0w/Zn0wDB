#pragma once

#include <vector>

#include "layout.h"
#include "element.h"


namespace zn {

	class Frame
	{
	private:
		Layout* layout;
		std::vector<Element> elements;

	public:
		Frame()
		{
			//layout = new AbsoluteLayout();
		}
		
		Frame(Layout* l)		// This constructor must be used only with new keyword
		{
			layout = l;
		}

		inline void setLayout(Layout* l) { delete layout;  layout = l; }	// This must be used only with new keyword
		inline Layout* getLayout() { return layout; }

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