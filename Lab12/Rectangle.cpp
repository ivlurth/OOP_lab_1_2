#include "Rectangle.h"

namespace ShapeSpace {

	Rectangle::Rectangle(Gdiplus::Rect _rect, COLOR _penColor, COLOR _brushColor) : Shape(_rect, _penColor, _brushColor) {
		std::cerr << "An instance of Rectangle has been created! # " << getID() << std::endl;
	}

	Rectangle::Rectangle(int x0, int y0, int width, int height, COLOR _penColor, COLOR _brushColor) : Shape({ x0, y0, width, height }, _penColor, _brushColor) {
		std::cerr << "An instance of Rectangle has been created! # " << getID() << std::endl;
	}

	Rectangle::~Rectangle() {
		std::cerr << "An instance of Rectangle has been destroyed! # " << getID() << std::endl;
	}

	void Rectangle::draw(Gdiplus::Graphics& g) {
		Gdiplus::Color color = getGdiPlus_Color(getPenColor());
		Gdiplus::Color brushColor = getGdiPlus_Color(getBrushColor());
		Gdiplus::SolidBrush brush(brushColor);
		Gdiplus::Pen newPen(color, 3);

		g.DrawRectangle(&newPen, getRect());
		g.FillRectangle(&brush, getRect());
	}
}