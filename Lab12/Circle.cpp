#include "Circle.h"

namespace ShapeSpace {
	Circle::Circle(int x0, int y0, int radius, COLOR _penColor, COLOR _brushColor) : Ellipse({ x0, y0, 2 * radius, 2 * radius }, _penColor, _brushColor) {
		std::cerr << "An instance of Circle has been created! # " << getID() << std::endl;
	}

	Circle::~Circle() {
		std::cerr << "An instance of Circle has been destroyed! # " << getID() << std::endl;
	}
}