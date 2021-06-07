#pragma once
#include <string>

#include "Shape.h"

namespace ShapeSpace {

	class TextShape : public Shape {
	private:
		std::wstring text;
	public:
		TextShape(std::wstring, Gdiplus::Rect, COLOR, COLOR);
		TextShape(std::wstring, int, int, int, int, COLOR, COLOR);
		virtual ~TextShape();

		const std::wstring& getText() const;

		virtual void draw(Gdiplus::Graphics& g) override;
	};
}