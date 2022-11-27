#include <stdio.h>
#include <Windows.h>

int main()
{
	LPWSTR Message = L"Какой-либо текст";
	ClicboardInputText(Message);
	ClipboardOutputText();
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

int ClipboardOutputText()
{
	LPWSTR Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (LPWSTR)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	MessageBox(NULL, Mess, L"Содержимое буффера обмена", MB_OK);
	return 0;
}