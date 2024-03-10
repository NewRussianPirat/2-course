#include <iostream>
#include <Windows.h>
#include <conio.h>

void main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Error";
		return;
	}
	HANDLE hWritePipe = (HANDLE)atoi(argv[1]);
	HANDLE hReadPipe = (HANDLE)atoi(argv[2]);
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");
	if (hEvent == nullptr) {
		std::cout << "Client: Event wasn't read";
		CloseHandle(hWritePipe);
		CloseHandle(hReadPipe);
		return;
	}
	long info[3];

	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, info, sizeof(long) * 3, &dwBytesRead, nullptr)) {
		std::cout << "Client: info wasn't read";
	}

	long* arr = new long[info[0]];
	srand(time(0));
	for (int i = 0; i < info[0]; ++i) {
		arr[i] = info[1] + (rand() % (info[2] - info[1]));
		std::cout << arr[i] << " ";
	}

	DWORD dwBytesWritten;
	if (!WriteFile(hWritePipe, arr, sizeof(long) * info[0], &dwBytesWritten, nullptr)) {
		std::cout << "Client: arr wasn't written";
	}

	SetEvent(hEvent);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEvent);

	std::cout << "\nEnter Q for exit\n";
	char c = _getch();
	while (c != 'q') {
		c = _getch();
	}
}