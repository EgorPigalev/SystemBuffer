#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
LPWSTR ClipboardOutputText();

LPWSTR a = "";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	while (TRUE)
	{
		LPSTR Data = ClipboardOutputText();
		DWORD len;
		len = wcslen(Data);
		int kol = 0;
		for (int i = 0; i < 2*len; i++)
		{
			if (Data[i] == 49)
			{
				kol += 8;
			}
			else if (Data[i] == "2")
			{
				kol += 3;
			}
			else
			{
				kol++;
			}
		}
		TCHAR *str = calloc(kol, sizeof(LPSTR));
		int j = 0;
		for (int i = 0; i < 2*len; i++)
		{
			if (Data[i] == 49)
			{
				str[j] = L'о\0';
				j++;
				str[j] = L'д\0';
				j++;
				str[j] = L'и\0';
				j++;
				str[j] = L'н\0';
				j++;
			}
			else if(Data[i] == "2")
			{
				str[j] = 'д';
				j++;
				str[j] = 'в';
				j++;
				str[j] = 'а';
				j++;
			}
			else
			{
				str[j] = Data[i];
				j++;
			}
		}
		if (strcmp(Data, a) != 0)
		{
			a = str;
			MessageBoxW(NULL, str, L"Внимание!!! Нарушение!!!", MB_OK | MB_ICONWARNING);
			ClicboardInputText(str);
		}
		Sleep(1000);
	}
	return 0;
}

int ClicboardInputText(LPWSTR buffer)
{
	DWORD len;
	HANDLE hMem;
	len = wcslen(buffer) + 1;

	hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
	memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR));
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
	return 0;
}

TCHAR* ClipboardOutputText()
{
	LPWSTR Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (LPWSTR)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	EmptyClipboard();
	return Mess;
}