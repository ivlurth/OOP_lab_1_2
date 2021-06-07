#include "TextShape.h"

namespace ShapeSpace {

	TextShape::TextShape(std::wstring _text, Gdiplus::Rect _rect, COLOR _penColor, COLOR _brushColor) 
		: Shape(_rect, _penColor, _brushColor),  text(_text){
		std::cerr << "An instance of TextShape has been created! # " << getID() << std::endl;
	}

	TextShape::TextShape(std::wstring _text, int x0, int y0, int width, int height, COLOR _penColor, COLOR _brushColor) 
		: Shape({ x0, y0, width, height }, _penColor, _brushColor), text(_text) {
		std::cerr << "An instance of TextShape has been created! # " << getID() << std::endl;
	}

	TextShape::~TextShape() {
		std::cerr << "An instance of TextShape has been destroyed! # " << getID() << std::endl;
	}

	const std::wstring& TextShape::getText() const {
		return text;
	}

	void TextShape::draw(Gdiplus::Graphics& g) {
		Gdiplus::Color color = getGdiPlus_Color(getPenColor());
		Gdiplus::Color brushColor = getGdiPlus_Color(getBrushColor());
		Gdiplus::SolidBrush brush(brushColor);
		Gdiplus::Pen newPen(color, 3);
		//newPen.SetBrush(&brush);

		const WCHAR* str = getText().c_str();
		Gdiplus::Font myFont(L"Times New Roman", 14);
		Gdiplus::StringFormat strForm;
		strForm.SetAlignment(Gdiplus::StringAlignmentCenter);

		g.DrawRectangle(&newPen, getRect());
		g.FillRectangle(&brush, getRect());
		brush.SetColor(color);
		g.DrawString(str, 
				     wcslen(str),
					 &myFont,
					 { static_cast<float>(getRect().X),
					   static_cast<float>(getRect().Y),
					   static_cast<float>(getRect().Width),
					   static_cast<float>(getRect().Height) },
					 &strForm,
					 &brush);

	}
}