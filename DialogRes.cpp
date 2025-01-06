#include"DialogRes.h"
#include"MyRes.h"
#include<cwchar>
#include<iostream>
#include<sstream>
#include<Windows.h>
#include<string>
using namespace std;

void LimitTextLen(HWND hDlg, int EditID, int length) {
	SendMessage(GetDlgItem(hDlg, EditID), EM_SETLIMITTEXT, length, 0);
}

int GetUsefulWindowText(HWND hDlg, int EditID, int& Out_Text_Len, wchar_t*& Out_Text) {
    Out_Text_Len = (int)SendMessage(GetDlgItem(hDlg, EditID), WM_GETTEXTLENGTH, 0, 0);
    if (!Out_Text_Len) {
        return -1;
    }
	Out_Text = new wchar_t[Out_Text_Len];
    GetWindowText(GetDlgItem(hDlg, EditID), Out_Text, Out_Text_Len + 1);
    SetWindowText(GetDlgItem(hDlg, EditID), Out_Text);
    return 0;
}

int isNotDigitW(wchar_t text) {
	return (text != L'0' && text != L'1' && text != L'2' && text != L'3' && text != L'4' && text != L'5'
		&& text != L'6' && text != L'7' && text != L'8' && text != L'9');
}
int isDigitW(wchar_t text) {
    return (text == '0' || text == '1' || text == '2' || text == '3' || text == '4' || text == '5'
        || text == '6' || text == '7' || text == '8' || text == '9');
}

int mx = 0, my = 0;


bool GRID::GetUserTypeRGBVal(wchar_t* wh_text, int len, int nMsg, HWND hDlg, WPARAM wParam){
    bool tellIfSuc = true;

    wstring Rnum;
    bool RIfGet = false;
    int Rlen = -1;
    
    wstring Gnum;
    bool GIfGet = false;
    int Glen = -1;
    
    wstring Bnum;
    bool BIfGet = false;
    int Blen = -1;
    

    int Ncount = 0;
    int Dcount = 0;

    int i = -1;//virtual count
    for (auto now : wstring(wh_text)) {
        i++;
        if (isNotDigitW(now) && now != L',') {
            tellIfSuc = false;
            break;
        }
        else if (now == L',') {
            Dcount++;
            Ncount = 0;
            if (Dcount > 0 && Dcount < 3 && i != 0 && i != len - 1) {
                if (RIfGet == false && GIfGet == false && BIfGet == false) {
                    if (i == 1) {
                        Rlen = 1;
                        wchar_t tmp[1];
                        tmp[0] = wh_text[i - 1];
                        Rnum = tmp;
                    }
                    else if (i == 2) {
                        Rlen = 2;
                        wchar_t tmp[2];
                        tmp[0] = wh_text[i - 2];
                        tmp[1] = wh_text[i - 1];
                        Rnum = tmp;
                    }
                    else if (i == 3) {
                        Rlen = 3;
                        wchar_t tmp[3];
                        tmp[0] = wh_text[i - 3];
                        tmp[1] = wh_text[i - 2];
                        tmp[2] = wh_text[i - 1];
                        Rnum = tmp;
                    }
                    //precaution
                    else {
                        tellIfSuc = false;
                        break;
                    }
                    RIfGet = true;
                }
                else if (RIfGet == true && GIfGet == false && BIfGet == false) {
                    if (i - Rlen - 1 == 1) {
                        Glen = 1;
                        wchar_t tmp[1];
                        tmp[0] = wh_text[Rlen + 1];
                        Gnum = tmp;
                    }
                    else if (i - Rlen - 1 == 2) {
                        Glen = 2;
                        wchar_t tmp[2];
                        tmp[0] = wh_text[Rlen + 1];
                        tmp[1] = wh_text[Rlen + 2];
                        Gnum = tmp;
                    }
                    else if (i - Rlen - 1 == 3) {
                        Glen = 3;
                        wchar_t tmp[3];
                        tmp[0] = wh_text[Rlen + 1];
                        tmp[1] = wh_text[Rlen + 2];
                        tmp[2] = wh_text[Rlen + 3];
                        Gnum = tmp;
                    }
                    //precaution
                    else {
                        tellIfSuc = false;
                        break;
                    }
                    GIfGet = true;
                }
                
                continue;
            }
            else {
                tellIfSuc = false;
                break;
            }
        }
        else {
            Ncount++;
            if (Ncount > 0 && Ncount < 4) {
                if (i == len - 1) {
                    if (RIfGet == true && GIfGet == true && BIfGet == false) {
                        if (i - Rlen - Glen - 1 == 1) {
                            Blen = 1;
                            wchar_t tmp[1];
                            tmp[0] = wh_text[Rlen + Glen + 2];
                            Bnum = tmp;
                        }
                        else if (i - Rlen - Glen - 1 == 2) {
                            Blen = 2;
                            wchar_t tmp[2];
                            tmp[0] = wh_text[Rlen + Glen + 2];
                            tmp[1] = wh_text[Rlen + Glen + 3];
                            Bnum = tmp;
                        }
                        else if (i - Rlen - Glen - 1 == 3){
                            Blen = 3;
                            wchar_t tmp[3];
                            tmp[0] = wh_text[Rlen + Glen + 2];
                            tmp[1] = wh_text[Rlen + Glen + 3];
                            tmp[2] = wh_text[Rlen + Glen + 4];
                            Bnum = tmp;
                        }
                        //precaution
                        else {
                            tellIfSuc = false;
                            break;
                        }
                        BIfGet = true;
                    }
                }
                continue;
            }
            else {
                tellIfSuc = false;
                break;
            }
        }
        
    }
    
    if (tellIfSuc == false) {
        return false;
    }
    else {
        int tmpRVal = stoi(Rnum);
        int tmpGVal = stoi(Gnum);
        int tmpBVal = stoi(Bnum);
        if (tmpRVal >= 0 && tmpGVal >= 0 && tmpBVal >= 0 &&
            tmpRVal <= 255 && tmpGVal <= 255 && tmpBVal <= 255) {
            HBRUSH now = CreateSolidBrush(RGB(tmpRVal, tmpGVal, tmpBVal));
            switch (nMsg)
            {
            case 0: {
                this->BKG_color_EX.color = now;
                this->BKG_color_EX.rgb_string = wh_text;
                this->BKG_color = now;
                break;
            }
            case 1: {
                this->SCFR_color_EX.color = now;
                this->SCFR_color_EX.rgb_string = wh_text;
                this->color_cmd.color_frame = now;
                break;
            }
            case 2: {
                this->SCTFI_color_EX.color = now;
                this->SCTFI_color_EX.rgb_string = wh_text;
                this->color_cmd.true_color_fill = now;
                break;
            }
            case 3: {
                this->SCFFI_color_EX.color = now;
                this->SCFFI_color_EX.rgb_string = wh_text;
                this->color_cmd.false_color_fill = now;
                break;
            }
            default:
                break;
            }
        }
        else {
            tellIfSuc = false;
            return false;
        }
    }
    return true;
}

int GRID::StoreSizeData(int row_num, int col_num) {
    if (row_num > 30 or col_num > 30) {
        return -1;
    }
    if (row_num < 2 or col_num < 2) {
        return -2;
    }
    for (int m = 0; m < this->rows; m++) {
        delete[] this->Rect_States[m];
    }
    delete[] this->Rect_States;
    
    for (int m = 0; m < this->rows; m++) {
        delete[] this->rect_arr[m];
    }
    delete[] this->rect_arr;

    this->rows = row_num;
    this->cols = col_num;

    this->Rect_States = new bool* [this->rows];
    for (int m = 0; m < this->rows; m++) {
        Rect_States[m] = new bool[this->cols];
    }

    this->rect_arr = new RECT * [this->rows];
    for (int m = 0; m < this->rows; m++) {
        rect_arr[m] = new RECT[this->cols];
    }
    GetClientRect(hWnd, &this->ClientRect);
    this->each_square_sidelength = (this->ClientRect.bottom - ClientRect.top) / (this->rows + 2);
    this->x = (ClientRect.right - ClientRect.left - this->each_square_sidelength * ReturnColNum()) / 2;
    this->y = (ClientRect.bottom - ClientRect.top - this->each_square_sidelength * ReturnRowNum()) / 2;
    
    initNewSize(this->ClientRect, this->x, this->y, this->each_square_sidelength);
    return 0;
}
