#pragma once
#include "Ellipse.h"

namespace ShapeSpace {
	class Circle : public Ellipse {
	public:
		Circle(int, int, int, COLOR, COLOR);
		virtual ~Circle();
	};
}