#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>

void main(int argc, char** argv) {
	long info[3];
	std::cout << "Server: Enter array size: ";
	std::cin >> info[0];
	long* arr = new long[info[0]];
	std::cout << "Server: Enter numbers N and M (N < M): ";
	std::cin >> info[1] >> info[2];
	while (info[1] >= info[2]) {
		std::cout << "Wrong N and M, try again" << std::endl;
		std::cout << "Server: Enter numbers N and M (N < M): ";
		std::cin >> info[1] >> info[2];
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe;
	HANDLE hReadPipe;
	HANDLE hEvent;
	SECURITY_ATTRIBUTES sa;

	hEvent = CreateEvent(nullptr, FALSE, FALSE, L"Event");
	if (hEvent == nullptr) {
		std::cout << "Server: Event wasn't created";
		return;
	}

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = nullptr;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
		std::cout << "Server: Pipe creation failed";
		CloseHandle(hWritePipe);
		CloseHandle(hReadPipe);
		CloseHandle(hEvent);
		return;
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	wchar_t* wstr = new wchar_t[80];
	wsprintf(wstr, L"\"Client.exe\" %d %d", (int)hWritePipe, (int)hReadPipe);

	if (!CreateProcess(nullptr, wstr, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, FALSE, FALSE, &si, &pi)) {
		std::cout << "Server: Client creation failed";
		CloseHandle(hWritePipe);
		CloseHandle(hReadPipe);
		CloseHandle(hEvent);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return;
	}

	DWORD dwBytesWritten;
	if (!WriteFile(hWritePipe, info, sizeof(long) * 3, &dwBytesWritten, nullptr)) {
		std::cout << "Server: info wasn't written";
		CloseHandle(hWritePipe);
		CloseHandle(hReadPipe);
		CloseHandle(hEvent);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return;
	}

	WaitForSingleObject(hEvent, INFINITE);

	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, arr, sizeof(long) * info[0], &dwBytesRead, nullptr)) {
		std::cout << "Server: arr wasn't read";
		CloseHandle(hWritePipe);
		CloseHandle(hReadPipe);
		CloseHandle(hEvent);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return;
	}

	for (int i = 0; i < info[0]; ++i) {
		std::cout << arr[i] << " ";
	}

	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEvent);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	std::cout << "\nEnter Q for exit\n";
	char c = _getch();
	while (c != 'q') {
		c = _getch();
	}
}