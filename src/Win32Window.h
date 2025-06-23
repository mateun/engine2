#pragma once

#include <windows.h>

class Win32Window {
public:
    Win32Window(HINSTANCE hInstance, int nCmdShow);
    ~Win32Window();
    bool ProcessMessages();
    HWND GetHwnd() const { return hwnd_; }

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    HWND hwnd_ = nullptr;
    HINSTANCE hInstance_ = nullptr;
}; 