#include <Windows.h>
#include <stdio.h>

void ShowDesktop()
{
    INPUT inputs[6] = {};
    ZeroMemory(inputs, sizeof(inputs));
    for (int i = 0; i < 5; i++) {
        inputs[i].type = INPUT_KEYBOARD;
    }
    inputs[0].ki.wVk = VK_CONTROL;

    inputs[1].ki.wVk = VK_LWIN;

    inputs[2].ki.wVk = VK_LEFT;

    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[4].ki.wVk = VK_LWIN;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[5].ki.wVk = VK_LEFT;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;


    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        wprintf(L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}