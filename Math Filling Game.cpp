// Math Filling Game.cpp : 定义应用程序的入口点。
//
#include "framework.h"
#include "Math Filling Game.h"
#include<iostream>
#include <locale>
#include<string>
#define MAX_LOADSTRING 100

//used in WndProc,WM_PAINT
bool IfIsFirstPainted = true;
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ContactMe(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SC_SelfDef(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    SizeChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MATHFILLINGGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MATHFILLINGGAME));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MATHFILLINGGAME);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//


//“主回调函数”全局变量资源

RECT** X_square;
GRID X_B_grid;
RECT X_M_win_rect;
int X_Mid_x;
int X_Mid_y;
int X_Mid_ESSL;//ESSL:each square sidelength
int a = 0;
HDC X_hdc;

//end

//“颜色自定义”全局变量资源

RECT X_SC_ClientFill;
HDC X_SC_hdc;
wchar_t* X_SCFR_text;
int X_SCFR_textlong;
wchar_t* X_SCTFI_text;
int X_SCTFI_textlong;
wchar_t* X_SCFFI_text;
int X_SCFFI_textlong;
wchar_t* X_SCBKG_text;
int X_SCBKG_textlong;

//end

wchar_t* X_ROW_text;
int X_ROW_textlong;
wchar_t* X_COL_text;
int X_COL_textlong;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE: {
        //basic grid
        GRID B_grid;
        X_B_grid = B_grid;
        RECT** square = new RECT * [4];
        for (int i = 0; i < 4; i++) {
            square[i] = new RECT[3];
        }
        X_square = square;
        GetClientRect(hWnd, &X_M_win_rect);
        X_Mid_ESSL = (X_M_win_rect.bottom - X_M_win_rect.top) / 6;
        X_Mid_x = (X_M_win_rect.right - X_M_win_rect.left - X_Mid_ESSL * 3) / 2;
        X_Mid_y = (X_M_win_rect.bottom - X_M_win_rect.top - X_Mid_ESSL * 4) / 2;
        X_B_grid.Create(hWnd, square, 4, 3, X_Mid_x, X_Mid_y, X_Mid_ESSL);
        X_B_grid.Show();
        X_hdc = GetDC(hWnd);
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &X_M_win_rect);
        X_Mid_ESSL = (X_M_win_rect.bottom - X_M_win_rect.top) / (X_B_grid.ReturnRowNum() + 2);
        X_Mid_x = (X_M_win_rect.right - X_M_win_rect.left - X_Mid_ESSL * X_B_grid.ReturnColNum()) / 2;
        X_Mid_y = (X_M_win_rect.bottom - X_M_win_rect.top - X_Mid_ESSL * X_B_grid.ReturnRowNum()) / 2;
        X_B_grid.RemainAll(X_M_win_rect, X_Mid_x, X_Mid_y, X_Mid_ESSL);
        EndPaint(hWnd, &ps);
    }break;
    case WM_LBUTTONUP: {
        X_B_grid.PlayBasicGame();
    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_CONTACTME:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CONTACTME), hWnd, ContactMe);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_SIZE:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_SIZE), hWnd, SizeChange);
            break;
        //colors
        case IDM_SC_SELFDEF:{
            DialogBox(hInst, MAKEINTRESOURCE(IDD_SC_SELFDEF), hWnd, SC_SelfDef);
            break;
        }
        case IDM_SCFFI_BLACK: {
            X_B_grid.FFI_EX(hbe_black);
            break;
        }
        case IDM_SCFFI_WHITE: {
            X_B_grid.FFI_EX(hbe_white);
            break;
        }
        case IDM_SCFFI_RED: {
            X_B_grid.FFI_EX(hbe_red);
            break;
        }
        case IDM_SCFFI_GREEN: {
            X_B_grid.FFI_EX(hbe_green);
            break;
        }
        case IDM_SCFFI_BLUE: {
            X_B_grid.FFI_EX(hbe_blue);
            break;
        }
        case IDM_SCFFI_YELLOW: {
            X_B_grid.FFI_EX(hbe_yellow);
            break;
        }
        case IDM_SCFFI_GREY: {
            X_B_grid.FFI_EX(hbe_grey);
            break;
        }
        case IDM_SCTFI_BLACK: {
            X_B_grid.TFI_EX(hbe_black);
            break;
        }
        case IDM_SCTFI_WHITE: {
            X_B_grid.TFI_EX(hbe_white);
            break;
        }
        case IDM_SCTFI_RED: {
            X_B_grid.TFI_EX(hbe_red);
            break;
        }
        case IDM_SCTFI_GREEN: {
            X_B_grid.TFI_EX(hbe_green);
            break;
        }
        case IDM_SCTFI_BLUE: {
            X_B_grid.TFI_EX(hbe_blue);
            break;
        }
        case IDM_SCTFI_YELLOW: {
            X_B_grid.TFI_EX(hbe_yellow);
            break;
        }
        case IDM_SCTFI_GREY: {
            X_B_grid.TFI_EX(hbe_grey);
            break;
        }
        case IDM_SCFR_BLACK: {
            X_B_grid.FR_EX(hbe_black);
            break;
        }
        case IDM_SCFR_WHITE: {
            X_B_grid.FR_EX(hbe_white);
            break;
        }
        case IDM_SCFR_RED: {
            X_B_grid.FR_EX(hbe_red);
            break;
        }
        case IDM_SCFR_GREEN: {
            X_B_grid.FR_EX(hbe_green);
            break;
        }
        case IDM_SCFR_BLUE: {
            X_B_grid.FR_EX(hbe_blue);
            break;
        }
        case IDM_SCFR_YELLOW: {
            X_B_grid.FR_EX(hbe_yellow);
            break;
        }
        case IDM_SCFR_GREY: {
            X_B_grid.FR_EX(hbe_grey);
            break;
        }
        case IDM_SCB_BLACK: {
            X_B_grid.ChangeBKG_EX(hbe_black);
            break;
        }
        case IDM_SCB_WHITE: {
            X_B_grid.ChangeBKG_EX(hbe_white);
            break;
        }
        case IDM_SCB_RED: {
            X_B_grid.ChangeBKG_EX(hbe_red);
            break;
        }
        case IDM_SCB_GREEN: {
            X_B_grid.ChangeBKG_EX(hbe_green);
            break;
        }
        case IDM_SCB_BLUE: {
            X_B_grid.ChangeBKG_EX(hbe_blue);
            break;
        }
        case IDM_SCB_YELLOW: {
            X_B_grid.ChangeBKG_EX(hbe_yellow);
            break;
        }
        case IDM_SCB_GREY: {
            X_B_grid.ChangeBKG_EX(hbe_grey);
            break;
        }
        //end colors
        //clear
        case IDM_CLEAR: {
            X_B_grid.ClearAll();
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
int wx = 0;
// “联系我”框的消息处理程序。
INT_PTR CALLBACK ContactMe(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG: {
        return (INT_PTR)TRUE;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == IDOK) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}


//“颜色自定义”框的消息处理程序。
INT_PTR CALLBACK SC_SelfDef(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG: {

        X_SC_hdc = GetDC(hDlg);
        LimitTextLen(hDlg, IDC_SCFR_EDIT, 11);
        LimitTextLen(hDlg, IDC_SCTFI_EDIT, 11);
        LimitTextLen(hDlg, IDC_SCFFI_EDIT, 11);
        LimitTextLen(hDlg, IDC_SCBKG_EDIT, 11);
        SetWindowText(GetDlgItem(hDlg, IDC_SCFR_EDIT), X_B_grid.NowLPCWSTR_RGBVal(1));
        SetWindowText(GetDlgItem(hDlg, IDC_SCTFI_EDIT), X_B_grid.NowLPCWSTR_RGBVal(2));
        SetWindowText(GetDlgItem(hDlg, IDC_SCFFI_EDIT), X_B_grid.NowLPCWSTR_RGBVal(3));
        SetWindowText(GetDlgItem(hDlg, IDC_SCBKG_EDIT), X_B_grid.NowLPCWSTR_RGBVal(0));
        
        return (INT_PTR)TRUE;

    }//break;

    case WM_COMMAND: {
        if (LOWORD(wParam) == IDOK)
        {

            if (GetUsefulWindowText(hDlg, IDC_SCFR_EDIT, X_SCFR_textlong, X_SCFR_text) == 0
                && GetUsefulWindowText(hDlg, IDC_SCTFI_EDIT, X_SCTFI_textlong, X_SCTFI_text) == 0
                && GetUsefulWindowText(hDlg, IDC_SCFFI_EDIT, X_SCFFI_textlong, X_SCFFI_text) == 0
                && GetUsefulWindowText(hDlg, IDC_SCBKG_EDIT, X_SCBKG_textlong, X_SCBKG_text) == 0
                && X_B_grid.GetUserTypeRGBVal(X_SCFR_text, X_SCFR_textlong, 1, hDlg, wParam)
                && X_B_grid.GetUserTypeRGBVal(X_SCTFI_text, X_SCTFI_textlong, 2, hDlg, wParam)
                && X_B_grid.GetUserTypeRGBVal(X_SCFFI_text, X_SCFFI_textlong, 3, hDlg, wParam)
                && X_B_grid.GetUserTypeRGBVal(X_SCBKG_text, X_SCBKG_textlong, 0, hDlg, wParam)) {
                
                X_B_grid.RemainAll(X_M_win_rect, X_Mid_x, X_Mid_y, X_Mid_ESSL);
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            else {
                MessageBox(hDlg, L"Error:C0002 Type error.", L"Error", MB_OK);
                EndDialog(hDlg, LOWORD(wParam));
            }
            
            
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            //delete X_SCFR_text, X_SCTFI_text, X_SCFFI_text, X_SCBKG_text;

            //return (INT_PTR)TRUE;
        }

    }//break;
    
    }
    return (INT_PTR)FALSE;
}

//“尺寸”框的消息处理程序
INT_PTR CALLBACK SizeChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG: {
        int hererow = X_B_grid.ReturnRowNum();
        int herecol = X_B_grid.ReturnColNum();
        SetWindowText(GetDlgItem(hDlg, IDC_EDIT_ROW), std::to_wstring(hererow).c_str());
        SetWindowText(GetDlgItem(hDlg, IDC_EDIT_COL), std::to_wstring(herecol).c_str());
        LimitTextLen(hDlg, IDC_EDIT_COL, 2);
        LimitTextLen(hDlg, IDC_EDIT_ROW, 2);
        return (INT_PTR)TRUE;
    }break;
    case WM_COMMAND: {
        if (LOWORD(wParam) == IDOK) {
            bool tellIfSuc = true;
            if (GetUsefulWindowText(hDlg, IDC_EDIT_ROW, X_ROW_textlong, X_ROW_text) == 0
                && GetUsefulWindowText(hDlg, IDC_EDIT_COL, X_COL_textlong, X_COL_text) == 0) {
                std::wstring tmpROW(X_ROW_text);
                std::wstring tmpCOL(X_COL_text);

                for (wchar_t k : tmpROW) {
                    if (isNotDigitW(k)) {
                        tellIfSuc = false;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                for (wchar_t f : tmpCOL) {
                    if (isNotDigitW(f)) {
                        tellIfSuc = false;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if (tellIfSuc == false) {
                    MessageBox(hDlg, L"Error:C0002 Type error.", L"Error", MB_OK);
                }
                else {
                    int valROW = std::stoi(tmpROW);
                    int valCOL = std::stoi(tmpCOL);
                    int tell = X_B_grid.StoreSizeData(valROW, valCOL);
                    if (tell == 0) {
                        EndDialog(hDlg, LOWORD(wParam));
                    }
                    else if (tell == -1) {
                        MessageBox(hDlg, L"Error:C0003 Dimensions exceeding 30 * 30 (or n * 30, 30 * n)\nare not supported.", L"Error", MB_OK);
                    }
                    else {
                        MessageBox(hDlg, L"Error:C0004 Dimensions below 2 * 2 (or n * 2, 2 * n)\nare not supported.", L"Error", MB_OK);
                    }
                }
            }
            else {
                MessageBox(hDlg, L"Error:C0002 Type error.", L"Error", MB_OK);
            }
            return (INT_PTR)FALSE;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }break;
    
    }
    return (INT_PTR)FALSE;
}