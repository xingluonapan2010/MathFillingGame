#pragma once
#ifndef MY_RES_H
#define MY_RES_H
#include<Windows.h>
#include<stdio.h>

//all rows and cols users use are started from 1
//normal colors ( HBRUSH type )
extern HBRUSH hb_black;//color black, HBRUSH type
extern HBRUSH hb_white;//color white, HBRUSH type
extern HBRUSH hb_red;//color red, HBRUSH type
extern HBRUSH hb_green;//color green, HBRUSH type
extern HBRUSH hb_blue;//color blue, HBRUSH type
extern HBRUSH hb_yellow;//color yellow, HBRUSH type
//end
//explorer
extern HBRUSH hb_grey;//color grey(Ex), HBRUSH type

//normal colors ( COLORREF type )
extern COLORREF co_black;//color black, COLORREF type
extern COLORREF co_white;//color white, COLORREF type
extern COLORREF co_red;//color red, COLORREF type
extern COLORREF co_green;//color green, COLORREF type
extern COLORREF co_blue;//color blue, COLORREF type
extern COLORREF co_yellow;//color yellow, COLORREF type
//end


//set colors when squares are responded
struct COLOR_CMD {
	HBRUSH color_frame;
	HBRUSH false_color_fill;
	HBRUSH true_color_fill;
};

typedef const wchar_t* WSTRING;
struct HBRUSHEX {
	HBRUSH color;
	const wchar_t* rgb_string;
};

extern HBRUSHEX hbe_black;//color black, HBRUSHEX type
extern HBRUSHEX hbe_white;//color white, HBRUSHEX type
extern HBRUSHEX hbe_red;//color red, HBRUSHEX type
extern HBRUSHEX hbe_green;//color green, HBRUSHEX type
extern HBRUSHEX hbe_blue;//color blue, HBRUSHEX type
extern HBRUSHEX hbe_yellow;//color yellow, HBRUSHEX type
extern HBRUSHEX hbe_grey;//color grey, HBRUSHEX type



typedef int TO;
typedef HBRUSH HB_TO;

//create a rectangular grid filled with sqaures and give it a responce
class GRID {
private:
	HWND hWnd;
	HDC hdc;
	int rows = 0;//started from 1
	int cols = 0;//started from 1
	int x = 0;
	int y = 0;
	int each_square_sidelength = 0;
	
	RECT** rect_arr;
	RECT ClientRect;

	int Extra_A = 0;
	int Extra_B = 0;

	bool** Rect_States;
	
	POINT pt;
	COLOR_CMD color_cmd = { hb_black,hb_white,hb_grey };

	HBRUSH BKG_color = hb_white;
	
	HBRUSHEX BKG_color_EX = hbe_white;
	HBRUSHEX SCFR_color_EX = hbe_black;
	HBRUSHEX SCTFI_color_EX = hbe_grey;
	HBRUSHEX SCFFI_color_EX = hbe_white;

	
public:
	//////////////////////////////////////////////////////////////
	//Resources ( seen in "MyRes.cpp" )
	/*
	create a grid
	# hWnd: the handle of the window
	# rect_arr: the array of the rectangles
	# rows: the rows of the rectangles in the grid
	# cols: the cols of the rectangles in the grid
	# x: the left position of the grid in the window
	# y: the top position of the grid in the window
	# each_square_sidelength: the side length of each square
	# color_cmd: the pointer of the colors which are created
	*/
	void Create(HWND hWnd, RECT** rect_arr, int rows, int cols, int x, int y, int each_square_sidelength);
	//end

	/*
	let the grid turn false
	# row_num: the square's row number
	# col_num: the square's col number
	*/
	void ShowFalse(int row_num, int col_num);
	//end

	/*
	tell if the mouse is in the grid
	*/
	bool MouseIsInIt();
	//end

	/*
	tell if the mouse is in the pointed square
	# wh_rect: the pointed rect
	*/
	bool MouseIsInRect(RECT wh_rect);
	//end

	/*
	let the grid turn true
	# row_num: the square's row number
	# col_num: the square's col number
	*/
	void ShowTrue(int row_num, int col_num);
	//end

	/*
	get the col number
	*/
	int GetMouseInWhatColNum();
	//end

	/*
	get the row number
	*/
	int GetMouseInWhatRowNum();
	//end

	int NowMouseInWhatColNum();
	int NowMouseInWhatRowNum();
	
	/*
	retrieve the position of the mouse
	*/
	void GetNowMousePos();
	//end

	/*
	find the pointed rect and return it
	*/
	RECT FromPosToRect(int rows, int cols);
	//end
	
	/*
	remain the states of the squares filled the grid
	caution: It's not normally used.Use "RemainAll" which can remain all the states.
	*/
	void RemainStates();
	//end

	/*
	show the grid( just be used during the first paint or the size of the grid is changed )
	*/
	void Show();
	//end
	
	/*
	change the state of the square
	*/
	void ChangeState(int row_num, int col_num);
	//end

	//void ChangeSetColors_FR_EX(HBRUSHEX to_wh_color);
	void ChangeSetColors_FR_EX(HBRUSHEX to_wh_color);

	void ChangeSetColors_FFI_EX(HBRUSHEX to_wh_color);
	

	void ChangeSetColors_TFI_EX(HBRUSHEX to_wh_color);

#define FR_EX ChangeSetColors_FR_EX
#define FFI_EX ChangeSetColors_FFI_EX
#define TFI_EX ChangeSetColors_TFI_EX
	
	/*
	let the grid in the correct position when the size of the window is changed and update the position
	caution: It's not normally used.Use "RemainAll" which can remain all the states.
	*/
	void RemainPos(int Now_x, int Now_y, int Now_ESSL);
	//end

	int GetRows();

	int GetCols();

	void ChangeRows(TO wh_row_num);

	void ChangeCols(TO wh_col_num);

	/*
	clear the grid
	*/
	void ClearAll();
	//end

	/*
	change the color of the window which contains the grid
	*/
	void ChangeBKG_EX(HBRUSHEX to_wh_color);
	//end

	/*
	# NowClientRect: get client rect of the window first, then it can be called
	# Now_x: the left position of the grid when the size of the window is changed
	# Now_y: the top position of the grid when the size of the window is changed
	# Now_ESSL: the side length of each of the squares when the size of the window is changed
	*/
	void RemainAll(RECT NowClientRect, int Now_x, int Now_y, int Now_ESSL);
	//end

	void initNewSize(RECT NowClientRect, int Now_x, int Now_y, int Now_ESSL);

	const wchar_t* NowLPCWSTR_RGBVal(int nMsg);
	

	/*
	# $$@ len: °üÀ¨L'\0'£¨½áÎ²·û£©
	# EndDialog() is included
	*/
	bool GetUserTypeRGBVal(wchar_t* wh_text, int len, int nMsg, HWND hDlg, WPARAM wParam);

	int StoreSizeData(int row_num, int col_num);

	int ReturnRowNum() {
		return this->rows;
	}
	int ReturnColNum() {
		return this->cols;
	}
	//********************************************************************//
	//********************************************************************//
	//********************************************************************//



	///////////////////////////////////////////////////////////////////
	//games ( seen in "Explorer.cpp" )
	void PlayBasicGame();

	
};

#endif // !MY_RES_H

