#include "MyRes.h"
#include<sstream>
#include<string>
#include<iostream>
//colors

COLORREF co_black = RGB(0, 0, 0);
COLORREF co_white = RGB(255, 255, 255);
COLORREF co_red = RGB(255, 0, 0);
COLORREF co_green = RGB(0, 255, 0);
COLORREF co_blue = RGB(0, 0, 255);
COLORREF co_yellow = RGB(255, 255, 0);
HBRUSH hb_black = CreateSolidBrush(co_black);
HBRUSH hb_white = CreateSolidBrush(co_white);
HBRUSH hb_red = CreateSolidBrush(co_red);
HBRUSH hb_green = CreateSolidBrush(co_green);
HBRUSH hb_blue = CreateSolidBrush(co_blue);
HBRUSH hb_yellow = CreateSolidBrush(co_yellow);
HBRUSH hb_grey = CreateSolidBrush(RGB(128, 128, 128));

HBRUSHEX hbe_black = { hb_black,L"0,0,0" };
HBRUSHEX hbe_white = { hb_white,L"255,255,255" };
HBRUSHEX hbe_red = { hb_red,L"255,0,0" };
HBRUSHEX hbe_green = { hb_green,L"0,255,0" };
HBRUSHEX hbe_blue = { hb_blue,L"0,0,255" };
HBRUSHEX hbe_yellow = { hb_yellow,L"255,255,0" };
HBRUSHEX hbe_grey = { hb_grey,L"128,128,128" };

void GRID::Create(HWND hWnd, RECT** rect_arr, int rows, int cols, int x, int y, int each_square_sidelength) {
	
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	this->rows = rows;
	this->cols = cols;
	this->x = x;
	this->y = y;
	this->each_square_sidelength = each_square_sidelength;
	this->rect_arr = rect_arr;
	GetClientRect(hWnd, &this->ClientRect);
	this->Rect_States = new bool* [this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->Rect_States[i] = new bool[this->cols];
	}
	for (int ii = 0; ii < rows; ii++) {
		for (int jj = 0; jj < cols; jj++) {
			this->Rect_States[ii][jj] = false;
			rect_arr[ii][jj].left = x + jj * each_square_sidelength;
			rect_arr[ii][jj].top = y + ii * each_square_sidelength;
			rect_arr[ii][jj].right = x + (jj + 1) * each_square_sidelength;
			rect_arr[ii][jj].bottom = y + (ii + 1) * each_square_sidelength;
		}
	}

	RECT decorater = { rect_arr[0][0].left - 1,rect_arr[0][0].top - 1,rect_arr[this->rows - 1][this->cols - 1].right + 1,rect_arr[this->rows - 1][this->cols - 1].bottom + 1 };
	FillRect(this->hdc, &decorater, this->color_cmd.color_frame);
}


void GRID::ShowFalse(int row_num,int col_num) {
	this->Rect_States[row_num - 1][col_num - 1] = false;
	FillRect(this->hdc, &this->rect_arr[row_num-1][col_num-1], this->color_cmd.false_color_fill);
	FrameRect(this->hdc, &this->rect_arr[row_num-1][col_num-1], this->color_cmd.color_frame);
}


bool GRID::MouseIsInIt() {
	GetCursorPos(&this->pt);
	ScreenToClient(this->hWnd, &pt);
	
	return (this->pt.x >= this->rect_arr[0][0].left and this->pt.x <= this->rect_arr[rows-1][cols-1].right and this->pt.y >= this->rect_arr[0][0].top and this->pt.y <= this->rect_arr[rows-1][cols-1].bottom);
}

bool GRID::MouseIsInRect(RECT wh_rect) {
	
	return (this->pt.x >= wh_rect.left and this->pt.x <= wh_rect.right and this->pt.y >= wh_rect.top and this->pt.y <= wh_rect.bottom);
}

void GRID::ShowTrue(int row_num, int col_num) {
	this->Rect_States[row_num - 1][col_num - 1] = true;
	FillRect(this->hdc, &this->rect_arr[row_num-1][col_num-1], this->color_cmd.true_color_fill);
	FrameRect(this->hdc, &this->rect_arr[row_num-1][col_num-1], this->color_cmd.color_frame);
}

int ffftmp = 0;
int GRID::GetMouseInWhatColNum() {
	this->Extra_A = (this->pt.x - this->rect_arr[0][0].left) / this->each_square_sidelength + 1;
	//specially
	if (this->Extra_A == this->cols + 1) {
		this->Extra_A = cols;
	}
	//precaution
	else if (this->Extra_A > cols or this->Extra_A < 0) {
		this->Extra_A = 0;
		MessageBox(this->hWnd, L"Error:C0001 Not found.", L"Error", MB_OK);
	}

	return this->Extra_A;
}

int GRID::GetMouseInWhatRowNum(){
	
	this->Extra_B = (this->pt.y - this->rect_arr[0][0].top) / this->each_square_sidelength + 1;

	//specially
	if (this->Extra_B == this->rows + 1) {
		this->Extra_B = rows - 1;
	}
	//precaution
	else if (this->Extra_B > rows or this->Extra_B < 0) {
		this->Extra_B = 0;
		MessageBox(this->hWnd, L"Error:C0001 Not found.", L"Error", MB_OK);
	}
	return this->Extra_B;
}

void GRID::GetNowMousePos() {
	GetCursorPos(&this->pt);
	ScreenToClient(this->hWnd, &this->pt);
}

RECT GRID::FromPosToRect(int rows, int cols) {
	return this->rect_arr[rows - 1][cols - 1];
}

void GRID::RemainStates() {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->cols; jj++) {
			if (this->Rect_States[ii][jj] == true) {
				FillRect(this->hdc, &this->rect_arr[ii][jj], this->color_cmd.true_color_fill);
				FrameRect(this->hdc, &this->rect_arr[ii][jj], this->color_cmd.color_frame);
			}
			else {
				FillRect(this->hdc, &this->rect_arr[ii][jj], this->color_cmd.false_color_fill);
				FrameRect(this->hdc, &this->rect_arr[ii][jj], this->color_cmd.color_frame);
			}
		}
	}
	
}

void GRID::Show() {
	for (int ii = 0; ii < rows; ii++) {
		for (int jj = 0; jj < cols; jj++) {
			ShowFalse(ii + 1, jj + 1);
		}
	}
}

void GRID::ChangeState(int row_num, int col_num) {
	if (Rect_States[row_num - 1][col_num - 1] == true) {
		ShowFalse(row_num, col_num);
	}
	else {
		ShowTrue(row_num, col_num);
	}
}

int GRID::NowMouseInWhatColNum() {
	return this->Extra_A;
}

int GRID::NowMouseInWhatRowNum() {
	return this->Extra_B;
}

void GRID::ChangeSetColors_FFI_EX(HBRUSHEX to_wh_color) {
	this->color_cmd.false_color_fill = to_wh_color.color;
	this->SCFFI_color_EX = to_wh_color;
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->cols; jj++) {
			if (this->Rect_States[ii][jj] == false) {
				ShowFalse(ii + 1, jj + 1);
			}
		}
	}
}

void GRID::ChangeSetColors_TFI_EX(HBRUSHEX to_wh_color) {
	this->color_cmd.true_color_fill = to_wh_color.color;
	this->SCTFI_color_EX = to_wh_color;
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->cols; jj++) {
			if (this->Rect_States[ii][jj] == true) {
				ShowTrue(ii + 1, jj + 1);
			}
		}
	}
}

void GRID::ChangeSetColors_FR_EX(HBRUSHEX to_wh_color) {
	this->color_cmd.color_frame = to_wh_color.color;
	this->SCFR_color_EX = to_wh_color;
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->cols; jj++) {
			if (this->Rect_States[ii][jj] == true) {
				ShowTrue(ii + 1, jj + 1);
			}
			else {
				ShowFalse(ii + 1, jj + 1);
			}
		}
	}
	
}

void GRID::RemainPos(int Now_x, int Now_y, int Now_ESSL) {
	for (int ii = 0; ii < rows; ii++) {
		for (int jj = 0; jj < cols; jj++) {
			rect_arr[ii][jj].left = Now_x + jj * Now_ESSL;
			rect_arr[ii][jj].top = Now_y + ii * Now_ESSL;
			rect_arr[ii][jj].right = Now_x + (jj + 1) * Now_ESSL;
			rect_arr[ii][jj].bottom = Now_y + (ii + 1) * Now_ESSL;
		}
	}
	this->x = Now_x;
	this->y = Now_y;
	this->each_square_sidelength = Now_ESSL;
	RECT decorater = { rect_arr[0][0].left - 1,rect_arr[0][0].top - 1,rect_arr[this->rows - 1][this->cols - 1].right + 1,rect_arr[this->rows - 1][this->cols - 1].bottom + 1 };
	FillRect(this->hdc, &decorater, this->color_cmd.color_frame);
}

int GRID::GetRows() {
	return this->rows;
}

int GRID::GetCols() {
	return this->cols;
}

void GRID::ChangeRows(TO wh_row_num) {
	this->rows = wh_row_num;
}

void GRID::ChangeCols(TO wh_col_num) {
	this->cols = wh_col_num;
}

void GRID::ClearAll() {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->cols; jj++) {
			this->Rect_States[ii][jj] = true;
			ShowFalse(ii + 1, jj + 1);
		}
	}
}

void GRID::ChangeBKG_EX(HBRUSHEX to_what_color) {
	this->BKG_color = to_what_color.color;
	FillRect(this->hdc, &this->ClientRect, to_what_color.color);
	RemainStates();
	
}



void GRID::RemainAll(RECT NowClientRect, int Now_x, int Now_y, int Now_ESSL) {
	this->ClientRect = NowClientRect;
	FillRect(this->hdc, &this->ClientRect, this->BKG_color);
	RemainPos(Now_x, Now_y, Now_ESSL);
	RemainStates();
}

const wchar_t* GRID::NowLPCWSTR_RGBVal(int nMsg) {
	switch (nMsg) {
	case 0:
		return this->BKG_color_EX.rgb_string;
		break;
	case 1:
		return this->SCFR_color_EX.rgb_string;
		break;
	case 2:
		return this->SCTFI_color_EX.rgb_string;
		break;
	case 3:
		return this->SCFFI_color_EX.rgb_string;
		break;
	default:
		return nullptr;
	}
}

