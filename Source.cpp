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
#include <string>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <list>
#include "resource.h"
// deklaracja funkcji okna:
LRESULT CALLBACK FunOkna(HWND, UINT, WPARAM, LPARAM);
//TCHAR* CalcPow(); // Obliczenia pot�gowania
// nazwa klasy rejestrowanej w systemie dla okna aplikacji
char nazwaKlasy[] = "OknoAplikacji";
//strukura wyswietlanie i liczba potegowa
typedef struct{
	TCHAR powText[MAX_PATH];
	int power;
} Power;
// tu lista
Power PowerList[] ={
	{TEXT("2^n"), 2},
	{TEXT("3^n"), 3},
	{TEXT("4^n"), 4},
	{TEXT("5^n"), 5},
	{TEXT("6^n"), 6},
	{TEXT("7^n"), 7},
	{TEXT("8^n"), 8},
	{TEXT("9^n"), 9},
	{TEXT("10^n"), 10},
};

class Equation {
private:

	char* equation;
	int number;

public:
	Equation(char* e, int n){
		int i = 0, lenth = 0;
		while (e[i++])
			lenth++;
		equation = new char[lenth + 1];
		i = 0;
		while (e[i])
		{
			equation[i] = e[i];
			i++;
		}
		equation[i] = e[i];
		number = n;
	}

	int getNumber() {
		return number;
	}

	char* printer() {
		return equation;
	}

	void printer2() {
		printf(equation);
	}
};

std::vector<Equation> arr; // Vector

//HWND bEdit; // nic
HWND lBox; // Listbox
HWND hWndComboBox; //Combobox
HWND eVar1; // Input 1
HWND eVar2; // Input 2
HWND eVar3; // To jest ten na samym dole okna z regu�� z jakiej zosta�o wyliczone
// glowna funkcja programu, parametry: uchwyty do aplikacji biezacej i poprzedniej (nie uzywane obecnie), lancuch ze linia plecen, tryb wyswietlania okna
int WINAPI WinMain(HINSTANCE biezAplik, HINSTANCE poprzAplik, LPSTR linPolec, int trybOkna){
	// Zdefiniowana konsola do można używać do debugowania. 
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n"); // Używasz normalnie printf()
	
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
// funkcja okna do obslugi jego komunikatow,
//             parametry: uchwyt okna, identyfikator liczbowy biezacego komunikatu, 
//                        dwa uzytkowe parametry komunikatu
LRESULT CALLBACK FunOkna(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
{
	switch (komunikat)	{
	case WM_INITDIALOG:	{
		hWndComboBox = GetDlgItem(okno, IDC_COMBO1);
		for (int i = 0; i < ARRAYSIZE(PowerList); i++){
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)PowerList[i].powText);
		}
		SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)0, 0);
		eVar1 = GetDlgItem(okno, IDC_EDIT1); //przypisanie id kontrolki do hwnd
		SetWindowText(eVar1, "1"); //ustawienie domy�lnego tekstu
		eVar2 = GetDlgItem(okno, IDC_EDIT2); //przypisanie id kontrolki do hwnd
		SetWindowText(eVar2, "10"); //ustawienie domy�lnego tekstu
		return 0;
	}
	case WM_COMMAND:	{
		if (LOWORD(wParam) == IDC_BUTTON1) { // close button click
			lBox = GetDlgItem(okno, IDC_LIST1); 
			SendMessage(lBox, LB_RESETCONTENT, 0, 0); //czyszczenie listboxa za kazdym razem przy nacisnieciu
			TCHAR buff[1024];
			TCHAR buff2[1024];
			GetWindowText(eVar1, buff, 1024); //Przyjmuje warto�� z inputu
			GetWindowText(eVar2, buff2, 1024); //Przyjmuje warto�� z inputu
			//TCHAR* str = buff; //magiczne sztuczki
			//TCHAR* str2 = buff; //magiczne sztuczki
			int n = _tstoi(buff); 
			int n2 = _tstoi(buff2); 
			//int fooSize = n2 - n; // rozmiar dla tablicy
			//TCHAR ** foo = new TCHAR*[fooSize];
			int sel = SendMessage(hWndComboBox, CB_GETCURSEL, (WPARAM)0, (LPARAM)0); //pobranie aktualnie wybranego indeksu z combobox
			int k = PowerList[sel].power; //wybranie z listy odpowiedniej liczby dla indeksu
			//int result;
			//TCHAR buf[300];
			int sizeofarr = n2 - n;
			arr.reserve(sizeofarr);
			for (int i = n; i <= n2;i++) {
				int a = pow(k,i);
				TCHAR buf[10];
				_stprintf(buf, TEXT("%d"), a);
				SendMessage(lBox, LB_ADDSTRING, NULL, (LRESULT)buf); // Wpisywanie do listboxa
				const size_t concatenated_size = MAX_PATH; //Inicjowanie chara i rozmiaru
				char concatenated[concatenated_size];
				snprintf(concatenated, concatenated_size, "%d^%d = %d", k, i, a); // Laczenie wszystkie w pieknego chara
				Equation eq(concatenated, a); // Tworzenie obiektu char, wartosc liczbowa
				arr.push_back(eq); // Dodawanie do vectora
			}
			return 0;
		}
		else if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE) {
			eVar3 = GetDlgItem(okno, IDC_EDIT3);
			lBox = GetDlgItem(okno, IDC_LIST1);
			_ASSERTE(lBox != NULL);
			// Pobieram aktualnie wskazany indeks w listbox
			int itemIndex = (int)SendMessage(lBox, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (itemIndex == LB_ERR)
			{
				// Nic nie wskazane
				return 1;
			}
			// Dlugosc tekstu w listboxie
			int textLen = (int)SendMessage(lBox, LB_GETTEXTLEN, (WPARAM)itemIndex, 0);
			// Allkuje buffer do przechowywania tekstu (zawiera +1 na koniec łańcucha)
			TCHAR * textBuffer = new TCHAR[textLen + 1];
			// Biore tekst do bufforu
			SendMessage(lBox, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)textBuffer);
			// Pokazówka
			for (std::vector<Equation>::const_iterator i = arr.begin(); i != arr.end(); ++i) {
				//Pobieram po koleji wszystkie obiekty z listy
				Equation eq = *i;
				TCHAR buf[300];
				//Tu konwersja
				_stprintf(buf, TEXT("%d"), eq.getNumber());
				// Porownuje do numeru ktory wybralem z listy
				if (_tcscmp(textBuffer,buf ) == 0 ) {
					// Pobieram chara
					char* cip = eq.printer();
					// Wysylam do okna na dole do wyswietlenia
					SetWindowText(eVar3, (LPCTSTR)cip);
				}
			}
			//SetWindowText(eVar3, (LPCTSTR)textBuffer);
			//MessageBox(NULL, textBuffer, _T("Selected Text:"), MB_OK);
			delete[] textBuffer;
			// Unikanie wiszących odniesień
			textBuffer = NULL;

			return 0;
		}
		else if (LOWORD(wParam) == IDC_BUTTON2) {
			MessageBox(NULL, "Hello, World2!", "Hi!", MB_OK);
		}
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
	  Zadanie: zakomentuj p/w operacje i sprawdz stan wykonywania programu  po zamknieciu okna poleceniem Alt-F4
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