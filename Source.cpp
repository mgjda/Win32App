#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "resource.h"
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message	,WPARAM wParam, LPARAM lParam);
int CALLBACK _tWinMain(
	_In_  HINSTANCE hInstance,	_In_  HINSTANCE hPrevInstance,	_In_  LPTSTR lpCmdLine,	_In_  int nCmdShow){
	::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ListBoxExampleProc);
	return 0;
}
typedef struct{
	TCHAR achName[MAX_PATH];
	TCHAR achPosition[12];
	int nGamesPlayed;
	int nGoalsScored;
} Player;
Player Roster[] ={
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
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam){
	switch (message)	{
	case WM_INITDIALOG:	{
		// Add items to list. 
		HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
		for (int i = 0; i < ARRAYSIZE(Roster); i++)		{
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
		switch (LOWORD(wParam))	{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDC_LIST1:{
			switch (HIWORD(wParam))	{
				case LBN_SELCHANGE:	{
					HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
					// Get selected index.
					int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
					// Get item data.
					int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
					// Do something with the data from Roster[i]
					TCHAR buff[MAX_PATH];
					StringCbPrintf(buff, ARRAYSIZE(buff),TEXT("Position: %s\nGames played: %d\nGoals: %d"),
						Roster[i].achPosition, Roster[i].nGamesPlayed,Roster[i].nGoalsScored);
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