#include "Shape.h"

namespace ShapeSpace {

	int Shape::objCount = 0;

	Gdiplus::Color Shape::getGdiPlus_Color(COLOR color) {
		switch (color) {
		case COLOR::BLACK:
			return Gdiplus::Color(0, 0, 0);
		case COLOR::BLUE:
			return Gdiplus::Color(0, 0, 255);
		case COLOR::GREEN:
			return Gdiplus::Color(0, 255, 0);
		case COLOR::GREY:
			return Gdiplus::Color(220, 220, 220);
		case COLOR::RED:
			return Gdiplus::Color(255, 0, 0);
		case COLOR::WHITE:
			return Gdiplus::Color(255, 255, 255);
		case COLOR::YELLOW:
			return Gdiplus::Color(255, 255, 0);
		}
		return Gdiplus::Color(0, 0, 0);
	}

	Shape::Shape(Gdiplus::Rect _rect, COLOR _penColor, COLOR _brushColor) :
		rect(_rect),
		penColor(_penColor),
		brushColor(_brushColor),
		id(++objCount) {
		std::cerr << "An instance of Shape has been created! # " << id << std::endl;
	}

	Shape::~Shape() {
		std::cerr << "An instance of Shape has been destroyed! # " << id << std::endl;
	}

	Gdiplus::Rect Shape::getRect() { return rect; }
	void Shape::setRect(Gdiplus::Rect newRectContainer) { rect = newRectContainer; }

	COLOR Shape::getPenColor() { return penColor; }
	void  Shape::setPenColor(COLOR newColor) { penColor = newColor; }

	COLOR Shape::getBrushColor() { return brushColor; }
	void  Shape::setBrushColor(COLOR newColor) { brushColor = newColor; }

	int Shape::getID() { return id; }
}