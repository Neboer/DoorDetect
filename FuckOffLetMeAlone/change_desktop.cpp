// change desktop by simulating a keystrock
#define WINVER 0x0500
#include <windows.h>

void stroke_change_window()
{
    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    //ip.ki.wVk = 0x41; // virtual-key code for the "a" key
    //ip.ki.dwFlags = 0; // 0 for key press
    ip.ki.wVk = VK_CONTROL;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.wVk = VK_LWIN;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.wVk = VK_LEFT;
    SendInput(1, &ip, sizeof(INPUT));
    // Release
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));// release LEFT
    ip.ki.wVk = VK_LWIN;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.wVk = VK_CONTROL;
    SendInput(1, &ip, sizeof(INPUT));
    return;
    // Exit normally
}