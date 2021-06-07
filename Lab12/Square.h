#pragma once

#include "Rectangle.h"

namespace ShapeSpace {
	class Square : public Rectangle {
	public:
		Square(int, int, int, COLOR, COLOR);
		virtual ~Square();
	};
}
