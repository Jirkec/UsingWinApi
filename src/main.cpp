#include <windows.h>
#include <cstdio>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 4
#define FILE_MENU_EXIT 3
#define FILE_MENU_HELP 2

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND hwnd);
HMENU hMenu;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case FILE_MENU_NEW:
                    MessageBeep(MB_OK);
                    break;
                case FILE_MENU_HELP:
                    MessageBeep(MB_HELP);
                    break;
                case FILE_MENU_OPEN:
                    MessageBeep(MB_ICONINFORMATION);
                    break;
                case FILE_MENU_EXIT:
                    DestroyWindow(hwnd);
                    break;
                default:
                    MessageBeep(MB_ICONERROR);
            }
            break;
        case WM_CREATE:
            AddMenus(hwnd);
            break;
        case WM_DESTROY:
            printf("Exit app");
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

void AddMenus(HWND hwnd){
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, nullptr);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, 2, "Help");

    SetMenu(hwnd, hMenu);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hinstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"My window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, nullptr, nullptr, nullptr, nullptr);

    MSG msg = {nullptr};
    while( GetMessage(&msg, nullptr, NULL, NULL) ){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

