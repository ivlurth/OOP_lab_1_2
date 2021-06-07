#include "Square.h"

namespace ShapeSpace {
	Square::Square(int x0, int y0, int side, COLOR _penColor, COLOR _brushColor) : Rectangle({ x0, y0, side, side }, _penColor, _brushColor) {
		std::cerr << "An instance of Square has been created! # " << getID() << std::endl;
	}

	Square::~Square() {
		std::cerr << "An instance of Square has been destroyed! # " << getID() << std::endl;
	}
}