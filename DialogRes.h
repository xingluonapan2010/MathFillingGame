#pragma once
#ifndef DIALOG_RES_H
#define DIALOG_RES_H
#include<Windows.h>

void LimitTextLen(HWND hDlg,int EditID,int length);

int GetUsefulWindowText(HWND hDlg, int EditID, int& Out_Text_Len, wchar_t*& Out_Text);

int isNotDigitW(wchar_t text);
int isDigitW(wchar_t text);

#endif//!DIALOG_RES_H