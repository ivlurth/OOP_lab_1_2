#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <iostream>


enum class COLOR{ RED, BLUE, YELLOW, GREEN, BLACK, WHITE, GREY };


namespace ShapeSpace {
	class Shape {
	private:
		static int objCount;
		Gdiplus::Rect rect;
		COLOR penColor;
		COLOR brushColor;
		int id;

	public:
		virtual void draw(Gdiplus::Graphics&) = 0;
		static Gdiplus::Color getGdiPlus_Color(COLOR color);
		Shape(Gdiplus::Rect, COLOR, COLOR);
		virtual ~Shape();

		Gdiplus::Rect getRect();
		void setRect(Gdiplus::Rect);

		COLOR getPenColor();
		void  setPenColor(COLOR);

		COLOR getBrushColor();
		void  setBrushColor(COLOR);

		int getID();
	};
}