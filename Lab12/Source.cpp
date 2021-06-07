#include <iostream>
#include <memory>
#include <windows.h>
#include <windowsx.h>

#include "resource.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Square.h"
#include "Ellipse.h"
#include "Circle.h"
#include "TextShape.h"
#include "ShapeList.h"


using namespace std;
using namespace Gdiplus;



ShapeSpace::ShapeList slist;

/*
int main() {
	slist.add(make_unique<ShapeSpace::Circle>(60, 80, 90, COLOR::BLACK, COLOR::GREEN));
	slist.add(make_unique<ShapeSpace::Square>(150, 50, 30, COLOR::RED, COLOR::BLUE));
	slist.add(make_unique<ShapeSpace::Rectangle>(10, 30, 40, 60, COLOR::YELLOW, COLOR::GREEN));
	slist.add(make_unique<ShapeSpace::TextShape>(L"Sample Text", 70, 20, 400, 40, COLOR::RED, COLOR::BLUE));
	slist.add(make_unique<ShapeSpace::Ellipse>(4, 4, 500, 30, COLOR::GREY, COLOR::BLUE));

	for (auto& it : slist) {
		cout << it->getID() << endl;
	}

	cout << "Before Deletion!" << endl;

	slist.clear();

	cout << "After Deletion!" << endl;

	return 0;
}*/




//==========================================================================================================================================
//==========================================================================================================================================
//==========================================================================================================================================


#define ELLIPSEBTNID   1
#define CIRCLEBTNID    2
#define RECTANGLEBTNID 3
#define SQUAREBTNID    4
#define TEXTBTNID      5
#define CLEARALLBTNID  6
#define COLORBTNID1    7
#define COLORBTNID2    8

#define DRAW_AREA_WIDTH  800
#define DRAW_AREA_HEIGHT 600

#define MENU_AREA_UPPER_LEFT_X 0
#define MENU_AREA_UPPER_LEFT_Y 600
#define MENU_AREA_WIDTH 800
#define MENU_AREA_HEIGHT 100
HICON hIcon;

enum class SelectedShape {
	ELLIPSE,
	CIRCLE,
	RECTANGLE,
	SQUARE,
	TEXT,
	NONE
};

SelectedShape shape = SelectedShape::NONE;
COLOR chosenPenColor = COLOR::RED;
COLOR chosenBrushColor = COLOR::RED;

int x0coord, y0coord, x1coord, y1coord;
bool firstPointIsChosen  = false;

COLOR GetColorByIndex(int index) {
	switch (index) {
		case 0:
			return COLOR::RED;
		case 1:
			return COLOR::BLUE;
		case 2:
			return COLOR::YELLOW;
		case 3:
			return COLOR::GREEN;
		case 4:
			return COLOR::BLACK;
		case 5:
			return COLOR::WHITE;
		case 6:
			return COLOR::GREY;
	}

	return COLOR::BLACK;
}

void SetCommonCursor(HWND hWnd) {
	HCURSOR hCurs = LoadCursor(NULL, IDC_ARROW);
	SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)(hCurs));
}

void SetCrossCursor(HWND hWnd) {
	HCURSOR hCurs = LoadCursor(NULL, IDC_CROSS);
	SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)(hCurs));
}

void DrawLastAddedShape(HDC hdc) {
	HRGN hRegion = CreateRectRgn(0, 0, DRAW_AREA_WIDTH, DRAW_AREA_HEIGHT);
	SelectClipRgn(hdc, hRegion);

	Graphics g(hdc);
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	slist.back()->get()->draw(g);

	DeleteObject(hRegion);

	shape = SelectedShape::NONE;
}

void DrawAllShapes(HDC hdc) {
	HRGN hRegion = CreateRectRgn(0, 0, DRAW_AREA_WIDTH, DRAW_AREA_HEIGHT);
	SelectClipRgn(hdc, hRegion);
	
	Graphics g(hdc);
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	for (auto& it : slist) {
		it->draw(g);
	}

	DeleteObject(hRegion);
}

void EraseAll(HWND hWnd) {
	slist.clear();
	InvalidateRect(hWnd, NULL, TRUE);
}

void GetCorrectStartingCoordinates(int _x0, int _y0, int x1, int y1) {
	int width  = abs(x1 - _x0);
	int height = abs(y1 - _y0);

	if (x1 <= _x0 && y1 < _y0) {
		x0coord = x1;
		y0coord = y1;
	}
	else if (x1 > _x0 && y1 < _y0) {
		y0coord -= height;
	}
	else if (x1 < _x0 && y1 >= _y0) {
		x0coord -= width;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int RAD_RETURN_RES = 0;

BOOL CALLBACK RequestRadiusDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case IDOK: {

			BOOL check;
			int res = GetDlgItemInt(hDlg, IDC_EDIT1, &check, FALSE);

			if (check) {

				if (res < 1 || res > 350) {
					MessageBoxW(hDlg, L"Введите натуральное число от 1 до 350!", L"Некорректный ввод!", (UINT)NULL);
					RAD_RETURN_RES = -3;
				}
				else {
					RAD_RETURN_RES = res;
					EndDialog(hDlg, 0);
				}
			}
			else {
				RAD_RETURN_RES = -1;
				MessageBoxW(hDlg, L"Введите натуральное число от 1 до 350!", L"Некорректный ввод!", (UINT)NULL);
			}

			return TRUE;
		}
		case IDCANCEL: {
			EndDialog(hDlg, 0);
			RAD_RETURN_RES = -2;
			return TRUE;
		}
		
		}
		break;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SIDE_RETURN_RES = 0;

BOOL CALLBACK RequestSideDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case IDOK: {

			BOOL check;
			int res = GetDlgItemInt(hDlg, IDC_EDIT1, &check, FALSE);

			if (check) {

				if (res < 1 || res > 350) {
					MessageBoxW(hDlg, L"Введите натуральное число от 1 до 350!", L"Некорректный ввод!", (UINT)NULL);
					SIDE_RETURN_RES = -3;
				}
				else {
					SIDE_RETURN_RES = res;
					EndDialog(hDlg, 0);
				}
			}
			else {
				SIDE_RETURN_RES = -1;
				MessageBoxW(hDlg, L"Введите натуральное число от 1 до 350!", L"Некорректный ввод!", (UINT)NULL);
			}

			return TRUE;
		}
		case IDCANCEL: {
			EndDialog(hDlg, 0);
			SIDE_RETURN_RES = -2;
			return TRUE;
		}

		}
		break;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

wstring TEXT_RETURN_RES;
bool ok = false;

BOOL CALLBACK RequestTextDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case IDOK: {

			wchar_t str[256];
			GetDlgItemTextW(hDlg, IDC_EDIT1, str, 256);
			TEXT_RETURN_RES = wstring(str);
			ok = true;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		case IDCANCEL: {
			EndDialog(hDlg, 0);
			ok = false;
			TEXT_RETURN_RES = L"";
			return TRUE;
		}

		}
		break;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











void ProcessClickInDrawArea(HWND hWnd, HDC hdc, int x, int y) {
	if (!firstPointIsChosen) {
		firstPointIsChosen = true;
		x0coord = x;
		y0coord = y;

		if (shape == SelectedShape::CIRCLE ||
			shape == SelectedShape::SQUARE) {

			if (shape == SelectedShape::CIRCLE) {
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_RADIUSDIALOG), hWnd, RequestRadiusDlgProc);
				if (RAD_RETURN_RES >= 1 && RAD_RETURN_RES <= 350) {
					slist.add(make_unique<ShapeSpace::Circle>(x0coord - RAD_RETURN_RES, y0coord - RAD_RETURN_RES, RAD_RETURN_RES, chosenPenColor, chosenBrushColor));
					DrawLastAddedShape(hdc);
					SetCommonCursor(hWnd);
					firstPointIsChosen = false;
				}
			}
			else if (shape == SelectedShape::SQUARE) {
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SIDEDIALOG), hWnd, RequestSideDlgProc);
				if (SIDE_RETURN_RES >= 1 && SIDE_RETURN_RES <= 350) {
					slist.add(make_unique<ShapeSpace::Square>(x0coord - SIDE_RETURN_RES / 2, y0coord - SIDE_RETURN_RES / 2, SIDE_RETURN_RES, chosenPenColor, chosenBrushColor));
					DrawLastAddedShape(hdc);
					SetCommonCursor(hWnd);
					firstPointIsChosen = false;
				}
			}
		}
	}
	else {
		x1coord = x;
		y1coord = y;

		int width =  abs(x1coord - x0coord);
		int height = abs(y1coord - y0coord);

		GetCorrectStartingCoordinates(x0coord, y0coord, x1coord, y1coord);

		if (shape == SelectedShape::ELLIPSE) {
			slist.add(make_unique<ShapeSpace::Ellipse>(x0coord, y0coord, width, height, chosenPenColor, chosenBrushColor));
		}
		else if (shape == SelectedShape::RECTANGLE) {
			slist.add(make_unique<ShapeSpace::Rectangle>(x0coord, y0coord, width, height, chosenPenColor, chosenBrushColor));
		}
		else if (shape == SelectedShape::TEXT) {
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TEXTDIALOG), hWnd, RequestTextDlgProc);
			if (ok) {
				slist.add(make_unique<ShapeSpace::TextShape>(TEXT_RETURN_RES, x0coord, y0coord, width, height, chosenPenColor, chosenBrushColor));
				DrawLastAddedShape(hdc);
				SetCommonCursor(hWnd);
				firstPointIsChosen = false;
			}
			return;
		}

		DrawLastAddedShape(hdc);
		SetCommonCursor(hWnd);
		firstPointIsChosen = false;
	}
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_CREATE: {
		SetClassLong(hWnd, GCL_HICON, (LONG)hIcon);
		return 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////
    	////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_COMMAND: {
		firstPointIsChosen = false;
		WORD word = LOWORD(wParam);

		if (word == ELLIPSEBTNID	||
			word == CIRCLEBTNID		||
			word == RECTANGLEBTNID	||
			word == SQUAREBTNID		||
			word == TEXTBTNID) {
			SetCrossCursor(hWnd);
		}

		switch (word) {

		case CLEARALLBTNID: {
			EraseAll(hWnd);
			break;
		}

		case ELLIPSEBTNID:{
			shape = SelectedShape::ELLIPSE;
			break;
		}

		case CIRCLEBTNID: {
			shape = SelectedShape::CIRCLE;
			break;
		}

		case RECTANGLEBTNID: {
			shape = SelectedShape::RECTANGLE;
			break;
		}

		case SQUAREBTNID: {
			shape = SelectedShape::SQUARE;
			break;
		}

		case TEXTBTNID: {
			shape = SelectedShape::TEXT;
			break;
		}

		case COLORBTNID1: {
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				chosenPenColor = GetColorByIndex(ItemIndex);
			}
			break;
		}

		case COLORBTNID2: {
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				chosenBrushColor = GetColorByIndex(ItemIndex);
			}
			break;
		}

		}

		return 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_LBUTTONDOWN: {
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		HDC hdc = GetDC(hWnd);
		RECT rect;


		SetRect(&rect, 0, 0, DRAW_AREA_WIDTH, DRAW_AREA_HEIGHT);
		HRGN hRgn = CreateRectRgnIndirect(&rect);
		SelectClipRgn(hdc, hRgn);


		if (PtInRegion(hRgn, x, y) && shape != SelectedShape::NONE) {
			SetFocus(hWnd);
			SelectClipRgn(hdc, NULL);
			ProcessClickInDrawArea(hWnd, hdc, x, y);
		}

		ReleaseDC(hWnd, hdc);
		DeleteObject(hRgn);

		return 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

			DrawAllShapes(hdc);

		EndPaint(hWnd, &ps);
		return 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	slist.add(make_unique<ShapeSpace::Circle>(0, 0, 100, COLOR::BLACK, COLOR::YELLOW));
	slist.add(make_unique<ShapeSpace::Square>(200, 300, 90, COLOR::RED, COLOR::BLUE));
	slist.add(make_unique<ShapeSpace::Rectangle>(500, 500, 80, 90, COLOR::YELLOW, COLOR::GREEN));
	slist.add(make_unique<ShapeSpace::TextShape>(L"Sample Text", 600, 10, 100, 60, COLOR::GREEN, COLOR::BLUE));
	slist.add(make_unique<ShapeSpace::Ellipse>(400, 200, 50, 40, COLOR::BLACK, COLOR::RED));
	slist.add(make_unique<ShapeSpace::Circle>(600, 560, 50, COLOR::BLACK, COLOR::RED));


	WNDCLASSEX wcex;	//Оконный класс для окна нашего приложения

	HWND hWnd;			//Главное окно нашего приложения
	MSG msg;			//Структура для получения и отправки сообщений

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//////////////////////////////////////////////
	//////////////////////////////////////////////			//Заполнение полей оконного класса
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = MyWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MyWindowClass";
	hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	wcex.hIconSm = NULL;
	//////////////////////////////////////////////
	//////////////////////////////////////////////

	RegisterClassEx(&wcex);		//Регистрация оконного класса


	//Создание главного окна приложения
	hWnd = CreateWindowEx(0, L"MyWindowClass", L"Примитивный графический редактор",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 800, 700, 0, 0, hInstance, NULL);

	//Создание рамки для меню приложения
	HWND groupButtonAn = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | BS_GROUPBOX,
		MENU_AREA_UPPER_LEFT_X,
		MENU_AREA_UPPER_LEFT_Y,
		MENU_AREA_WIDTH,
		MENU_AREA_HEIGHT, hWnd, NULL, NULL, NULL);

	HWND ellipseButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Ellipse",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		10,
		615,
		80,
		40, hWnd, (HMENU)ELLIPSEBTNID, NULL, NULL);

	HWND circleButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Circle",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		100,
		615,
		80,
		40, hWnd, (HMENU)CIRCLEBTNID, NULL, NULL);

	HWND rectangleButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Rectangle",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		190,
		615,
		80,
		40, hWnd, (HMENU)RECTANGLEBTNID, NULL, NULL);

	HWND squareButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Square",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		280,
		615,
		80,
		40, hWnd, (HMENU)SQUAREBTNID, NULL, NULL);

	HWND drawTextButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Text Draw",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		370,
		615,
		80,
		40, hWnd, (HMENU)TEXTBTNID, NULL, NULL);

	HWND clearButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"Button", L"Clear All",
		WS_VISIBLE | WS_CHILD | BS_MULTILINE,
		460,
		615,
		80,
		40, hWnd, (HMENU)CLEARALLBTNID, NULL, NULL);


	HWND hWndComboBox = CreateWindow(L"combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		550, 630, 80, 140, hWnd, 
		(HMENU)COLORBTNID1, NULL,	NULL);


	HWND hWndComboBox2 = CreateWindow(L"combobox", NULL,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		660, 630, 80, 140, hWnd,
		(HMENU)COLORBTNID2, NULL, NULL);


	HWND hLabel1 = CreateWindow(L"static", L"Цвет 1",
		SS_SIMPLE | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		565, 610, 80, 140, hWnd, NULL, NULL,
		NULL);

	HWND hLabel2 = CreateWindow(L"static", L"Цвет 2",
		SS_SIMPLE | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		675, 610, 80, 140, hWnd, NULL, NULL,
		NULL);



	TCHAR Colors[7][7] =
	{
		TEXT("Red"), TEXT("Blue"), TEXT("Yellow"), TEXT("Green"),
		TEXT("Black"), TEXT("White"), TEXT("Grey")
	};
	TCHAR A[16];
	int  k = 0;
	memset(&A, 0, sizeof(A));
	for (k = 0; k <= 6; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)Colors[k]);

		SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
		SendMessage(hWndComboBox2, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}
	SendMessage(hWndComboBox,  CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	SendMessage(hWndComboBox2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);



	//Показ главного окна приложения
	ShowWindow(hWnd, nCmdShow);

	//Цикл обработки сообщений
	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);

	//Возвращение результата работы
	return msg.wParam;
}