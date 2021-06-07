#include "Ellipse.h"

namespace ShapeSpace {

	Ellipse::Ellipse(Gdiplus::Rect _rect, COLOR _penColor, COLOR _brushColor) : Shape(_rect, _penColor, _brushColor) {
		std::cerr << "An instance of Ellipse has been created! # " << getID() << std::endl;
	}

	Ellipse::Ellipse(int x0, int y0, int width, int height, COLOR _penColor, COLOR _brushColor) : Shape({ x0, y0, width, height }, _penColor, _brushColor) {
		std::cerr << "An instance of Ellipse has been created! # " << getID() << std::endl;
	}

	Ellipse::~Ellipse() {
		std::cerr << "An instance of Ellipse has been destroyed! # " << getID() << std::endl;
	}

	void Ellipse::draw(Gdiplus::Graphics& g) {
		Gdiplus::Color color = getGdiPlus_Color(getPenColor());
		Gdiplus::Color brushColor = getGdiPlus_Color(getBrushColor());
		Gdiplus::SolidBrush brush(brushColor);
		Gdiplus::Pen newPen(color, 3);

		g.DrawEllipse(&newPen, getRect());
		g.FillEllipse(&brush, getRect());
	}
}