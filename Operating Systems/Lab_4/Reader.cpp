#include <iostream>
#include <Windows.h>
#include <stdlib.h>

void main(int argc, char** argv) {
	auto* Mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"Mutex");
	if (Mutex == nullptr) {
		std::cout << "Reader: Mutex opening failed\n";
		CloseHandle(Mutex);
		system("pause");
		return;
	}

	WaitForSingleObject(Mutex, INFINITE);
	std::cout << "Reader: Active process\n";

	HANDLE Event_Reader_A = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Reader_A");
	if (Event_Reader_A == nullptr) {
		std::cout << "Reader: Event_Reader_A opening failed\n";
		CloseHandle(Mutex);
		CloseHandle(Event_Reader_A);
		system("pause");
		return;
	}

	HANDLE Event_Reader_B = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Reader_B");
	if (Event_Reader_B == nullptr) {
		std::cout << "Reader: Event_B opening failed\n";
		CloseHandle(Mutex);
		CloseHandle(Event_Reader_A);
		CloseHandle(Event_Reader_B);
		system("pause");
		return;
	}

	HANDLE Event_Reader_Ended = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Reader_Ended");
	if (Event_Reader_Ended == nullptr) {
		std::cout << "Reader: End opening failed\n";
		CloseHandle(Mutex);
		CloseHandle(Event_Reader_A);
		CloseHandle(Event_Reader_B);
		CloseHandle(Event_Reader_Ended);
		system("pause");
		return;
	}

	for (int i = 0; i < atoi(argv[1]); ++i) {
		char c;
		std::cout << "Reader: Enter 'A' or 'B': ";
		std::cin >> c;
		if (c == 'A') {
			SetEvent(Event_Reader_A);
		}
		else if (c == 'B') {
			SetEvent(Event_Reader_B);
		}
	}

	SetEvent(Event_Reader_Ended);
	ReleaseMutex(Mutex);
	CloseHandle(Mutex);
	CloseHandle(Event_Reader_A);
	CloseHandle(Event_Reader_B);
	CloseHandle(Event_Reader_Ended);
	system("pause");
}