#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 1
#define ID_EDIT2 2
#define ID_STATIC_TEXT 7
#define ID_BUTTON_ADD 3
#define ID_BUTTON_SUB 4
#define ID_BUTTON_MUL 5
#define ID_BUTTON_DIV 6

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void PerformCalculation(HWND, int);

HINSTANCE hInst;
HWND hEdit1, hEdit2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyCalculator";
    wc.hbrBackground = CreateSolidBrush(RGB(255, 200, 100));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClass(&wc)) return 0;

    HWND hwnd = CreateWindow("MyCalculator", "My Calculator", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE,
                20, 5, 200, 20, hwnd, (HMENU)ID_STATIC_TEXT, NULL, NULL);

            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                20, 30, 80, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                140, 30, 80, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);
            
            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
                20, 70, 50, 30, hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
                80, 70, 50, 30, hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
                140, 70, 50, 30, hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
                200, 70, 50, 30, hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;
        
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case ID_BUTTON_ADD: PerformCalculation(hwnd, ID_BUTTON_ADD); break;
                case ID_BUTTON_SUB: PerformCalculation(hwnd, ID_BUTTON_SUB); break;
                case ID_BUTTON_MUL: PerformCalculation(hwnd, ID_BUTTON_MUL); break;
                case ID_BUTTON_DIV: PerformCalculation(hwnd, ID_BUTTON_DIV); break;
            }
            break;
        
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

void PerformCalculation(HWND hwnd, int operation) {
    char buffer1[100], buffer2[100], resultText[100];
    GetWindowText(hEdit1, buffer1, 100);
    GetWindowText(hEdit2, buffer2, 100);
    
    double num1 = atof(buffer1);
    double num2 = atof(buffer2);
    double result = 0;
    
    switch (operation) {
        case ID_BUTTON_ADD: result = num1 + num2; break;
        case ID_BUTTON_SUB: result = num1 - num2; break;
        case ID_BUTTON_MUL: result = num1 * num2; break;
        case ID_BUTTON_DIV: 
            if (num2 != 0) 
                result = num1 / num2; 
            else {
                MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                return;
            }
            break;
    }
    
    sprintf(resultText, "%f", result);
    MessageBox(hwnd, resultText, "Result", MB_OK | MB_ICONINFORMATION);
}
