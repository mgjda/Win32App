// dodatkowa konfiguracja dla kompilatora MSVC
#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif

#include <iostream>

// pliki biblioteki standardowej jezyka C:
#include <stdlib.h>

// plik naglowkowy z deklaracjami elementow interfejsu Win32 API:
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "resource.h"
#include <winuser.h>
// deklaracja funkcji okna:
LRESULT CALLBACK FunOkna(HWND, UINT, WPARAM, LPARAM);

// nazwa klasy rejestrowanej w systemie dla okna aplikacji
char nazwaKlasy[] = "OknoAplikacji";
//strukura wyswietlanie i liczba potegowa
typedef struct
{
	TCHAR powText[MAX_PATH];
	int power;
} Power;

// tu lista
Power PowerList[] =
{
	{TEXT("x^2"), 2},
	{TEXT("x^3"), 3},
	{TEXT("x^4"), 4},
	{TEXT("x^5"), 5},
	{TEXT("x^6"), 6},
	{TEXT("x^7"), 7},
	{TEXT("x^8"), 8},
	{TEXT("x^9"), 9},
	{TEXT("x^10"), 10},
};


// glowna funkcja programu, parametry: uchwyty do aplikacji biezacej i poprzedniej (nie uzywane obecnie),
//                                     lancuch ze linia plecen, tryb wyswietlania okna
int WINAPI WinMain(HINSTANCE biezAplik, HINSTANCE poprzAplik, LPSTR linPolec, int trybOkna)
{
	WNDCLASS klasaOkna; // rekord do opisu nowej klasy okna
	HWND okno; // uchwyt obiektu okna z p/w klasy

	// wypelnienie rekordu parametrami nowej klasy okna:
	klasaOkna.style = CS_HREDRAW | CS_VREDRAW; // wspolny styl okien klasy - odrysowywanie okna w pionie i poziomie
	// klasaOkna.style = 0; // wspolny styl okien klasy - brak
	klasaOkna.hInstance = biezAplik;  // uchwyt (biezacej) aplikacji dla ktorej powstanie nowa klasa
	klasaOkna.lpszClassName = nazwaKlasy; // nazwa klasy okna
	klasaOkna.lpfnWndProc = FunOkna;  // adres procedury okna
	klasaOkna.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ikona okna na ekranie - standardowa dla wszystkich aplikacji
	klasaOkna.hCursor = LoadCursor(NULL, IDC_ARROW); // obraz kursora myszki nad oknem - standardowy w postaci strzalki
	klasaOkna.lpszMenuName = NULL; // nazwa menu - brak
	klasaOkna.cbClsExtra = 0; // dodatkowa pamiec uzytkowa dla klasy - brak
	klasaOkna.cbWndExtra = 0; // i nowo tworzonego obiektu okna - brak
	klasaOkna.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // pedzel dla tla okna - standardowy bialy kolor
   /*
	Zadanie: odkomentuj brak stylu okna, zakomentuj styl odrysowania w pionie i poziomie,
			 przetestuj aplikacje zmieniajac jej rozmiar
   */

   // rejestrowanie klasy okna w systemie:
	if (!RegisterClass(&klasaOkna)) return 0;

	okno = CreateDialog(biezAplik, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)FunOkna);

	// wyswietlanie okna i aktualizacja zawartosci jego obszaru roboczego:
	ShowWindow(okno, trybOkna);
	UpdateWindow(okno);

	{ // Glowny kod wykonawczy programu
		MSG komunikat; // rekord z opisem komunikatu

		// petla programu do przetwarzania komunikatow aplikacji w systemie:
		while (GetMessage(&komunikat, NULL, 0, 0)) // pobierz biezacy komunikat z kolejki biezacego procesu
		{
			TranslateMessage(&komunikat); // przeksztalca biezacy komunikat (jedynie zamienia kod zdarzenia dot. klawiszy)
			DispatchMessage(&komunikat); // wysyla biezacy komunikat do docelowego okna
		}

		// zakonczenie programu i zwrocenie wartosci parametru z ostatniego komunikatu:
		return (int)komunikat.wParam;
	}
}



int DisplayResourceNAMessageBox()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCSTR)L"Resource not available\nDo you want to try again?",
		(LPCSTR)L"Account Details",
		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
	);

	switch (msgboxID)
	{
	case IDCANCEL:
		// TODO: add code
		break;
	case IDTRYAGAIN:
		// TODO: add code
		break;
	case IDCONTINUE:
		// TODO: add code
		break;
	}

	return msgboxID;
}

HWND bEdit;
HWND lBox;

// funkcja okna do obslugi jego komunikatow,
//             parametry: uchwyt okna, identyfikator liczbowy biezacego komunikatu, 
//                        dwa uzytkowe parametry komunikatu
LRESULT CALLBACK FunOkna(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
{
	switch (komunikat)
	{
	case WM_INITDIALOG:
	{
		HWND hWndComboBox = GetDlgItem(okno, IDC_COMBO1);
		for (int i = 0; i < ARRAYSIZE(PowerList); i++)
		{

			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)PowerList[i].powText);
		}
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1) { // close button click
			lBox = GetDlgItem(okno, IDC_LIST1);
			LRESULT lResult = SendMessage(lBox, LB_ADDSTRING, NULL, LPARAM("some constant text"));
		}
		return 0;
		//if (LOWORD(wParam) == IDC_BUTTON1) // close button click
		//	EndDialog(okno, 0);
		//return TRUE;
	}
	case WM_CLOSE: // obsluz komunikat zamkniecia okna
	{
		DestroyWindow(okno); // zniszcz okno glowne wysylajac komunikat WM_DESTROY i nastepnie zakoncz program
		//PostQuitMessage(0); // natychmiast zakoncz program wysylajac komunikat WM_QUIT ale bez zniszczenia okna
		return 0; // powrot z funkcji do petli glownej 
	}
	case WM_DESTROY: // obsluz komunikat zniszczenia okna
	{
		PostQuitMessage(0); // wyslij komunikat WM_QUIT do kolejki programu  
	 /*
	  Zadanie: zakomentuj p/w operacje i sprawdz stan wykonywania programu
			   po zamknieciu okna poleceniem Alt-F4
	 */
		return 0; // powrot z funkcji do petli glownej i jej przerwanie
	}
	default: // jezeli brak jest obslugi dla biezacego komunikatu w niniejszej funkcji, to ...
	{
		// ... nalezy wywolac funkcje systemowa ze domyslna obsluge tego komunikatu:
		return DefWindowProc(okno, komunikat, wParam, lParam);
	}
	}
}