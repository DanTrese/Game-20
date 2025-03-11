#include <windows.h> // підключення бібліотеки з функціями API
#include <stdio.h>

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Sakhnavi Daniel";

HWND staticText;
HWND button;
HWND plus1;
HWND plus2;
HWND plus3;
HWND player;
HWND result;
HWND rules;

int pNum = 1;
int res = 0;


// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	#define IDI_ICON1 132
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = NULL; 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_OVERLAPPEDWINDOW,			// стиль вікна
		GetSystemMetrics(SM_CXSCREEN)/2 - 310, 			// положення по Х	
		GetSystemMetrics(SM_CYSCREEN)/2 - 310, 		 // положення по Y	
		620, 			// розмір по Х
		620, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток

void DrawMain(HWND hWnd, RECT rt) {
	GetClientRect(hWnd, &rt); 		//Область вікна для малювання
	int clientWidth = rt.right - rt.left;
	int clientHeight = rt.bottom - rt.top;
	pNum = 1;
	res = 0;
	staticText = CreateWindowA("STATIC", "ПІДСУМОВУВАННЯ ДО 20", WS_CHILD | WS_VISIBLE | SS_CENTER, (clientWidth - 540) / 2, 100, 540, 160, hWnd, NULL, hInst, NULL);
	HFONT hFontTitel = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(staticText, WM_SETFONT, WPARAM(hFontTitel), TRUE);
	#define ID_START 1001
	button = CreateWindowA("BUTTON", "ПОЧАТИ ГРУ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (clientWidth - 360) / 2, clientHeight - 220, 360, 120, hWnd, (HMENU)ID_START, hInst, NULL);
	HFONT hFontStart = CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(button, WM_SETFONT, WPARAM(hFontStart), TRUE);

}

void ClearScreen() {

		// Уничтожение элементов интерфейса
		DestroyWindow(button);
		DestroyWindow(staticText);
		DestroyWindow(plus1);
		DestroyWindow(plus2);
		DestroyWindow(plus3);
		DestroyWindow(result);
		DestroyWindow(player);
		DestroyWindow(rules);

}

void DrawGame(HWND hWnd, RECT rt) {
	GetClientRect(hWnd, &rt); 		//Область вікна для малювання
	int clientWidth = rt.right - rt.left;
	int clientHeight = rt.bottom - rt.top;
	#define ID_PLUS1 1002
	#define ID_PLUS2 1003
	#define ID_PLUS3 1004

	if (pNum == 1) {
		plus1 = CreateWindowA("BUTTON", "+1",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			50, 130, 50, 80, hWnd, (HMENU)ID_PLUS1,
			hInst, NULL);
		plus2 = CreateWindowA("BUTTON", "+2",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			50, 230, 50, 80, hWnd, (HMENU)ID_PLUS2,
			hInst, NULL);
		plus3 = CreateWindowA("BUTTON", "+3",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			50, 330, 50, 80, hWnd, (HMENU)ID_PLUS3,
			hInst, NULL);
	}
	else {
		plus1 = CreateWindowA("BUTTON", "+1",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			500, 130, 50, 80, hWnd, (HMENU)ID_PLUS1,
			hInst, NULL);
		plus2 = CreateWindowA("BUTTON", "+2",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			500, 230, 50, 80, hWnd, (HMENU)ID_PLUS2,
			hInst, NULL);
		plus3 = CreateWindowA("BUTTON", "+3",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			500, 330, 50, 80, hWnd, (HMENU)ID_PLUS3,
			hInst, NULL);
	}

	HFONT hFontPlus = CreateFont(28, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(plus1, WM_SETFONT, WPARAM(hFontPlus), TRUE);
	SendMessage(plus2, WM_SETFONT, WPARAM(hFontPlus), TRUE);
	SendMessage(plus3, WM_SETFONT, WPARAM(hFontPlus), TRUE);



	if (pNum == 1) {
		player = CreateWindowA("STATIC", "ХІД ГРАВЦЯ\nI", WS_CHILD | WS_VISIBLE | SS_CENTER, (clientWidth - 300) / 2, 30, 300, 120, hWnd, NULL, hInst, NULL);
	}
	else if (pNum == 2) {
		player = CreateWindowA("STATIC", "ХІД ГРАВЦЯ\nII", WS_CHILD | WS_VISIBLE | SS_CENTER, (clientWidth - 300) / 2, 30, 300, 120, hWnd, NULL, hInst, NULL);
	}

	HFONT hFontPlayer = CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(player, WM_SETFONT, WPARAM(hFontPlayer), TRUE);

	

	char numr[10];
	sprintf_s(numr, "%d", res);

	result = CreateWindowA("STATIC", numr, WS_CHILD | WS_VISIBLE | SS_CENTER, (clientWidth / 2 )-50, (clientHeight-120) / 2, 100, 120, hWnd, NULL, hInst, NULL);
	HFONT hFontResult = CreateFont(80, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(result, WM_SETFONT, WPARAM(hFontResult), TRUE);


	#define ID_RULES 1005

	rules = CreateWindowA("BUTTON", "ПРАВИЛА", WS_CHILD | WS_VISIBLE | SS_CENTER, (clientWidth - 120) /2, 500, 120, 40, hWnd, (HMENU)ID_RULES, hInst, NULL);

	HFONT hFontRules = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Fixedsys");
	SendMessage(rules, WM_SETFONT, WPARAM(hFontRules), TRUE);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	RECT rt{};
	PAINTSTRUCT ps{};


	switch (message)
	{
	case WM_CREATE: {
		DrawMain(hWnd, rt);
		break;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_START: {
			ClearScreen();
			DrawGame(hWnd, rt);
			break;
		}

		case ID_RULES: {
			MessageBox(hWnd, "1. Гра призначена для двох гравців.\n2. Гравці по черзі називають числа від 1 до 3, які додаються до \nзагального числа.\n3. Мета полягає в тому, щоб досягти числа 20.\n4. Гравець, який перевищує 20, програє.", "Правила", MB_OK);
			break;
		}

		case ID_PLUS1:
			res += 1;
			if (res == 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			if (pNum == 1) { pNum = 2; } else pNum = 1;
			if (res > 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			ClearScreen();
			DrawGame(hWnd, rt);
			break;

		case ID_PLUS2:
			res += 2;
			if (res == 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			if (pNum == 1) { pNum = 2; }
			else pNum = 1;
			if (res > 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			ClearScreen();
			DrawGame(hWnd, rt);
			break;

		case ID_PLUS3:
			res += 3;
			if (res == 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			if (pNum == 1) { pNum = 2; }
			else pNum = 1;
			if (res > 20) {
				const char* ch1 = "Гравець №";
				char nump[10];
				sprintf_s(nump, "%d", pNum);
				const char* ch2 = " переміг!";
				char winner[100];
				sprintf_s(winner, "%s%s%s", ch1, nump, ch2);
				MessageBox(hWnd, winner, "Message", MB_OK);
				ClearScreen();
				DrawMain(hWnd, rt);
				break;
			}
			ClearScreen();
			DrawGame(hWnd, rt);
			break;

		
		}
		break;
	}

	case WM_CTLCOLORSTATIC:
		return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
		break;


	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
