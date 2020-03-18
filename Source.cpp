#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "resource.h"

INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK ComboBoxAction(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam);

int CALLBACK _tWinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPTSTR lpCmdLine,
	_In_  int nCmdShow)
{
	::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ListBoxExampleProc);
	::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ComboBoxAction);
	
	return 0;
}

typedef struct
{
	TCHAR powText[12];
	int power;
} Power;

Power PowerList[]=
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

typedef struct
{
	TCHAR achName[MAX_PATH];
	TCHAR achPosition[12];
	int nGamesPlayed;
	int nGoalsScored;
} Player;

Player Roster[] =
{
	{TEXT("Haas, Jonathan"), TEXT("Midfield"), 18, 4 },
	{TEXT("Pai, Jyothi"), TEXT("Forward"), 36, 12 },
	{TEXT("Hanif, Kerim"), TEXT("Back"), 26, 0 },
	{TEXT("Anderberg, Michael"), TEXT("Back"), 24, 2 },
	{TEXT("Jelitto, Jacek"), TEXT("Midfield"), 26, 3 },
	{TEXT("Raposo, Rui"), TEXT("Back"), 24, 3},
	{TEXT("Joseph, Brad"), TEXT("Forward"), 13, 3 },
	{TEXT("Bouchard, Thomas"), TEXT("Forward"), 28, 5 },
	{TEXT("Salmre, Ivo "), TEXT("Midfield"), 27, 7 },
	{TEXT("Camp, David"), TEXT("Midfield"), 22, 3 },
	{TEXT("Kohl, Franz"), TEXT("Goalkeeper"), 17, 0 },
};


INT_PTR CALLBACK ComboBoxAction(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam) 
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hWndComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		for (int i = 0; i < ARRAYSIZE(PowerList); i++)
		{
			/*SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);*/
			int pos = (int)SendMessage(hWndComboBox, LB_ADDSTRING, 0,
				(LPARAM)PowerList[i].powText);
			SendMessage(hWndComboBox, LB_SETITEMDATA, pos, (LPARAM)i);
		}

		/*SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);*/
		SetFocus(hWndComboBox);
		return TRUE;
	}
	}

	return FALSE;
}


INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// Add items to list. 
		HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
		for (int i = 0; i < ARRAYSIZE(Roster); i++)
		{
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
				(LPARAM)Roster[i].achName);
			// Set the array index of the player as item data.
			// This enables us to retrieve the item from the array
			// even after the items are sorted by the list box.
			SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
		}
		// Set input focus to the list box.
		SetFocus(hwndList);
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);

				// Get selected index.
				int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

				// Get item data.
				int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

				// Do something with the data from Roster[i]
				TCHAR buff[MAX_PATH];
				StringCbPrintf(buff, ARRAYSIZE(buff),
					TEXT("Position: %s\nGames played: %d\nGoals: %d"),
					Roster[i].achPosition, Roster[i].nGamesPlayed,
					Roster[i].nGoalsScored);

				SetDlgItemText(hDlg, IDC_EDIT3, buff);
				return TRUE;
			}
			}
		}
		return TRUE;
		}
	}
	return FALSE;
}