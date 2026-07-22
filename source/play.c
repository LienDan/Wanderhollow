#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>

#pragma comment(lib, "shlwapi.lib")

// Tried in order - all Chromium-based browsers support the same --app
// flag for a chromeless "app mode" window. Firefox/Safari are excluded
// since they don't support this flag the same way.
static const char* BROWSERS[] = {
    "msedge",   // Microsoft Edge
    "chrome",   // Google Chrome
    "brave",    // Brave
    "vivaldi",  // Vivaldi
    "opera",    // Opera
};
static const int NUM_BROWSERS = sizeof(BROWSERS) / sizeof(BROWSERS[0]);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    PathRemoveFileSpecA(exePath); // folder containing this exe

    char htmlPath[MAX_PATH];
    snprintf(htmlPath, sizeof(htmlPath), "%s\\lucid_dreams_of_roguelike.html", exePath);

    char args[MAX_PATH + 16];
    snprintf(args, sizeof(args), "--app=\"%s\"", htmlPath);

    HINSTANCE result = (HINSTANCE)32; // treat as "not found" to start the loop
    for (int i = 0; i < NUM_BROWSERS; i++) {
        result = ShellExecuteA(NULL, "open", BROWSERS[i], args, NULL, SW_SHOWNORMAL);
        if ((INT_PTR)result > 32) {
            return 0; // launched successfully
        }
    }

    // No Chromium-based browser found - just open the file with whatever
    // the system's default handler for .html is.
    ShellExecuteA(NULL, "open", htmlPath, NULL, NULL, SW_SHOWNORMAL);
    return 0;
}
