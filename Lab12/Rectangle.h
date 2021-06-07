#pragma once
#include "Shape.h"

namespace ShapeSpace {

	class Rectangle : public Shape {
	public:
		Rectangle(Gdiplus::Rect, COLOR, COLOR);
		Rectangle(int, int, int, int, COLOR, COLOR);
		virtual ~Rectangle();

		virtual void draw(Gdiplus::Graphics& g) override;
	};
}