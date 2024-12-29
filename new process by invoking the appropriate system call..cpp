#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Get current process ID and parent process ID (Windows-specific)
    DWORD currentPID = GetCurrentProcessId();

    printf("Parent process:\n");
    printf("  PID: %lu\n", currentPID);

    // Create a child process
    if (!CreateProcess(
            NULL,               // No module name (use command line)
            "notepad",          // Command line (can specify a program like "notepad")
            NULL,               // Process handle not inheritable
            NULL,               // Thread handle not inheritable
            FALSE,              // Set handle inheritance to FALSE
            0,                  // No creation flags
            NULL,               // Use parent's environment block
            NULL,               // Use parent's starting directory
            &si,                // Pointer to STARTUPINFO structure
            &pi                 // Pointer to PROCESS_INFORMATION structure
        )) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Display child process ID
    printf("Created child process with PID: %lu\n", pi.dwProcessId);

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

