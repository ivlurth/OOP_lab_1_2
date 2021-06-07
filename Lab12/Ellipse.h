#pragma once
#include "Shape.h"

namespace ShapeSpace {

	class Ellipse : public Shape {
	public:
		Ellipse(Gdiplus::Rect, COLOR, COLOR);
		Ellipse(int, int, int, int, COLOR, COLOR);
		virtual ~Ellipse();

		virtual void draw(Gdiplus::Graphics& g) override;
	};
}