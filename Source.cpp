/*****************************************************************/
/* Najprostsza aplikacja C z interfejsem GUI opartym o Win32 API */     
/*****************************************************************/
 //dodatkowa konfiguracja dla kompilatora MSVC
#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif
 //pliki biblioteki standardowej jezyka C:
#include <stdlib.h>
 //plik naglowkowy z deklaracjami elementow interfejsu Win32 API:
#include <windows.h>
 //deklaracja funkcji okna:
LRESULT CALLBACK FunOkna(HWND, UINT, WPARAM, LPARAM);
 //nazwa klasy rejestrowanej w systemie dla okna aplikacji
char nazwaKlasy[] = "OknoAplikacji";
//HWND hComboBox, hComboBox2, hEdit;
HWND n1, n2,pow_combo, pow_btn, fac_btn;
 //glowna funkcja programu, parametry: uchwyty do aplikacji biezacej i poprzedniej (nie uzywane obecnie),
//lancuch ze linia plecen, tryb wyswietlania okna
int WINAPI WinMain(HINSTANCE biezAplik, HINSTANCE poprzAplik, LPSTR linPolec, int trybOkna){
	WNDCLASS klasaOkna; // rekord do opisu nowej klasy okna
	HWND okno; // uchwyt obiektu okna z p/w klasy
	// wypelnienie rekordu parametrami nowej klasy okna:
	klasaOkna.style = CS_HREDRAW | CS_VREDRAW; // wspolny styl okien klasy - odrysowywanie okna w pionie i poziomie
	 klasaOkna.style = 0; // wspolny styl okien klasy - brak
	klasaOkna.hInstance = biezAplik;  // uchwyt (biezacej) aplikacji dla ktorej powstanie nowa klasa
	klasaOkna.lpszClassName = nazwaKlasy; // nazwa klasy okna
	klasaOkna.lpfnWndProc = FunOkna;  // adres procedury okna
	klasaOkna.hIcon = LoadIcon(NULL,IDI_APPLICATION); // ikona okna na ekranie - standardowa dla wszystkich aplikacji
	klasaOkna.hCursor = LoadCursor(NULL,IDC_ARROW); // obraz kursora myszki nad oknem - standardowy w postaci strzalki
	klasaOkna.lpszMenuName = NULL; // nazwa menu - brak
	klasaOkna.cbClsExtra = 0; // dodatkowa pamiec uzytkowa dla klasy - brak
	klasaOkna.cbWndExtra = 0; // i nowo tworzonego obiektu okna - brak
	klasaOkna.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // pedzel dla tla okna - standardowy bialy kolor
	/*
	Zadanie: odkomentuj brak stylu okna, zakomentuj styl odrysowania w pionie i poziomie,
	przetestuj aplikacje zmieniajac jej rozmiar
	*/
	 //rejestrowanie klasy okna w systemie:
	if (!RegisterClass(&klasaOkna)) return 0;
	 //utworzenie okna glowne aplikacji na podstawie p/w klasy o danej nazwie:
	okno = CreateWindow(
		nazwaKlasy,              // nazwa klasy okna
		"Ciagi",      // tytul okna na ekranie
		WS_OVERLAPPEDWINDOW,     // podstawowe style okna - okno nachodzace na inne
		CW_USEDEFAULT,           // pocz. poz. na osi x - domyslny
		CW_USEDEFAULT,           // pocz. poz. na osi y - domyslny
		CW_USEDEFAULT,           // pocz. szerokosc okna - domyslny
		CW_USEDEFAULT,           // pocz. wysokosc okna - domyslny
		NULL,                    // uchwyt okna nadrzednego (macierzytego) - brak
		NULL,                    // uchwyt menu okna - brak
		biezAplik,               // uchwyt (biezacej) aplikacji dla ktorej powstanie nowe okno
		NULL                     // dodatkowe parametry zapisane w obiekcie okna - brak
	);
	 //wyswietlanie okna i aktualizacja zawartosci jego obszaru roboczego:
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
		 //zakonczenie programu i zwrocenie wartosci parametru z ostatniego komunikatu:
		return (int)komunikat.wParam;
	}
}
 //funkcja okna do obslugi jego komunikatow, parametry: uchwyt okna, identyfikator liczbowy biezacego komunikatu, dwa uzytkowe parametry komunikatu
LRESULT CALLBACK FunOkna(HWND okno, UINT komunikat,WPARAM wParam, LPARAM lParam){
	switch (komunikat){
		case WM_CREATE: {
			HINSTANCE uchwytAplik = (HINSTANCE)GetWindowLong(okno, GWL_HINSTANCE); // posrednie pobranie uchwytu biezacej aplikacji
			// Mo¿liwe do wybrania wielkoœci czcionki
			const char *powers[8] =
			{ "2^n","3^n","4^n","5^n","6^n","7^n","8^n","9^n"};
			HDC kont = GetDC(okno);
			int i;
			//// Twórz dwa okna typu Combobox
			//hComboBox = CreateWindowEx(0, "COMBOBOX", NULL,
			//	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
			//	| CBS_SORT | WS_VSCROLL, 0, 0, 250, 200, okno, NULL, uchwytAplik, NULL);
			//hComboBox2 = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
			//	| WS_VSCROLL, 250, 0, 50, 200, okno, NULL, uchwytAplik, NULL);
			//// Twórz przyciski styli
			//hPogrubienie = CreateWindowEx(0, "BUTTON", "B", WS_CHILD | WS_VISIBLE
			//	| BS_AUTOCHECKBOX | BS_PUSHLIKE, 300, 0, 26, 26, okno, NULL, uchwytAplik, NULL);
			//hKursywa = CreateWindowEx(0, "BUTTON", "/",
			//	WS_CHILD | WS_VISIBLE
			//	| BS_AUTOCHECKBOX | BS_PUSHLIKE,
			//	326, 0, 26, 26, okno, NULL, uchwytAplik, NULL);
			//hPodkreslenie = CreateWindowEx(0, "BUTTON", "&U",
			//	WS_CHILD | WS_VISIBLE
			//	| BS_AUTOCHECKBOX | BS_PUSHLIKE,
			//	352, 0, 26, 26, okno, NULL, uchwytAplik, NULL);
			//// Twórz okno typu Edit
			//hEdit = CreateWindowEx(0, "EDIT", "0",
			//	WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
			//	420, 0, 40, 26, okno, NULL, uchwytAplik, NULL);
			n1= CreateWindowEx(0, "EDIT", "0",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,80,40, 80,20, okno, NULL, uchwytAplik, NULL);
			n2= CreateWindowEx(0, "EDIT", "0",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,80, 80, 80,20, okno, NULL, uchwytAplik, NULL);
			pow_btn= CreateWindowEx(0, "BUTTON", "POTEGI",WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,80, 200,80, 20, okno, NULL, uchwytAplik, NULL);
			pow_combo= CreateWindowEx(0, "COMBOBOX", NULL,WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL, 80, 240, 80, 20, okno, NULL, uchwytAplik, NULL);
			fac_btn = CreateWindowEx(0, "BUTTON", "SILNIA n2!", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE, 80, 280, 80, 20, okno, NULL, uchwytAplik, NULL);
			/* Wywo³aj funkcjê FunCzcionek dla wszystkich
			fontów zainstalowanych w systemie */
		/*	EnumFontFamilies(kont, NULL,
				(FONTENUMPROC)FunCzcionek, 0);*/
			/* Wybierz wstêpnie pierwsz¹ pozycjê z listy
			dostêpnych fontów */
			//SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
			/* Odczytaj nazwê wybranego fontu do
			zmiennej globalnej font */
			//SendMessage(hComboBox, CB_GETLBTEXT, 0, (LPARAM)font);
			// Obetnij pierwsze trzy znaki czyli "   " lub "TT "
			/*strcpy(font, font + 3);*/
			/* Umieœæ w drugim oknie Combobox typowe
			wielkoœci czcionek */
			/*for (i = 0; i < 16; i++)
				SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)rozmiary[i]);*/
			/* Wybierz wstêpnie trzeci¹ wartoœæ z listy
			czyli wielkoœæ 10 */
			for (i = 0; i < 8; i++)
				SendMessage(pow_combo, CB_ADDSTRING, 0, (LPARAM)powers[i]);
			SendMessage(pow_combo, CB_SETCURSEL, 2, 0);
			ReleaseDC(okno, kont);
			return 0;
		}
		case WM_CLOSE: // obsluz komunikat zamkniecia okna
		{
			DestroyWindow(okno); // zniszcz okno glowne wysylajac komunikat WM_DESTROY i nastepnie zakoncz program
			PostQuitMessage(0); // natychmiast zakoncz program wysylajac komunikat WM_QUIT ale bez zniszczenia okna
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
		case WM_PAINT: // obsluz komunikat rysowania w oknie (dokladniej w jego obszarze roboczym)
		{
			LOGFONT lf;
			PAINTSTRUCT paint;
			char buf[5];
			HFONT hFont;
			HDC text = BeginPaint(okno, &paint);
			TextOut(text, 60,42, "n1:", 4);
			TextOut(text, 60,20, "Zakres indexów:", 20);
			TextOut(text, 60,82, "n2:", 4);
			// Wype³nij wszystkie pola struktury lf zerami
			memset(&lf, 0, sizeof(lf));
			// Wpisz wartoœci do odpowiednich pól
			lf.lfHeight = 16;
			lf.lfWeight = FW_NORMAL;
			lf.lfCharSet = DEFAULT_CHARSET;
			// SprawdŸ stan przycisku pogrubienia
			//if (SendMessage(hPogrubienie, BM_GETCHECK, 0, 0)== BST_CHECKED)
				//lf.lfWeight = FW_BOLD;
			/* Przepisz stan przycisków kursywy i podkreœlenia
			do odpowiednich pól */
			//lf.lfItalic = (BYTE)SendMessage(hKursywa, BM_GETCHECK, 0, 0);
			//lf.lfUnderline = (BYTE)SendMessage(hPodkreslenie, BM_GETCHECK, 0, 0);
			// Skopiuj nazwê fontu do odpowiedniego pola
			//strcpy(lf.lfFaceName, font);
			// Odczytaj zawartoœæ pola Edit
			//SendMessage(hEdit, WM_GETTEXT, 4, (LPARAM)buf);
			// i okreœl na tej podstawie k¹t wyœwietlania tekstu
			lf.lfEscapement = lf.lfOrientation = atoi(buf) * 10;
			// Twórz czcionkê i wyœwietl nazwê kroju
			hFont = CreateFontIndirect(&lf);
			//????????????hFont = (HFONT)SelectObject(kont, hFont);
			//TextOut(kont, 100, 300, font, (int)strlen(font));
			//?????????????hFont = (HFONT)SelectObject(kont, hFont);
			DeleteObject(hFont);
			EndPaint(okno, &paint);
			return 0;
		}
		default: // jezeli brak jest obslugi dla biezacego komunikatu w niniejszej funkcji, to ...
		{
			// ... nalezy wywolac funkcje systemowa ze domyslna obsluge tego komunikatu:
			return DefWindowProc(okno, komunikat, wParam, lParam);
		}
	}
}