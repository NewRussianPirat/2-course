#include <iostream>
#include <Windows.h>
#include <stdlib.h>

void main(int args, char** argv) {
	auto* Semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");
	if (Semaphore == nullptr) {
		std::cout << "Writer: Semaphore opening failed\n";
		CloseHandle(Semaphore);
		system("pause");
		return;
	}

	WaitForSingleObject(Semaphore, INFINITE);
	std::cout << "Writer: Active process\n";

	auto* Events_Reader = new HANDLE[2];
	Events_Reader[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Reader_A");
	if (Events_Reader[0] == nullptr) {
		std::cout << "Reader: Event_A opening failed\n";
		CloseHandle(Semaphore);
		CloseHandle(Events_Reader[0]);
		system("pause");
		return;
	}

	Events_Reader[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Reader_B");
	if (Events_Reader[1] == nullptr) {
		std::cout << "Reader: Event_B opening failed\n";
		CloseHandle(Semaphore);
		CloseHandle(Events_Reader[0]);
		CloseHandle(Events_Reader[1]);
		system("pause");
		return;
	}

	HANDLE Event_Writer_A = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Writer_A");
	if (Event_Writer_A == nullptr) {
		std::cout << "Reader: Writer_A opening failed\n";
		CloseHandle(Semaphore);
		CloseHandle(Events_Reader[0]);
		CloseHandle(Events_Reader[1]);
		CloseHandle(Event_Writer_A);
		system("pause");
		return;
	}

	HANDLE Event_Writer_B = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Writer_B");
	if (Event_Writer_B == nullptr) {
		std::cout << "Reader: Writer_B opening failed\n";
		CloseHandle(Semaphore);
		CloseHandle(Events_Reader[0]);
		CloseHandle(Events_Reader[1]);
		CloseHandle(Event_Writer_A);
		CloseHandle(Event_Writer_B);
		system("pause");
		return;
	}

	HANDLE Event_Writer_Ended = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Writer_Ended");
	if (Event_Writer_Ended == nullptr) {
		std::cout << "Reader: End opening failed\n";
		CloseHandle(Semaphore);
		CloseHandle(Events_Reader[0]);
		CloseHandle(Events_Reader[1]);
		CloseHandle(Event_Writer_A);
		CloseHandle(Event_Writer_B);
		CloseHandle(Event_Writer_Ended);
		system("pause");
		return;
	}

	for (int i = 0; i < atoi(argv[1]); ++i) {
		int k = WaitForMultipleObjects(2, Events_Reader, FALSE, INFINITE);
		k -= WAIT_OBJECT_0;
		if (k == 0) {
			std::cout << "Writer: A\n";
			SetEvent(Event_Writer_A);
			ResetEvent(Events_Reader[0]);
		}
		else {
			std::cout << "Writer: B\n";
			SetEvent(Event_Writer_B);
			ResetEvent(Events_Reader[1]);
		}
	}

	ReleaseSemaphore(Semaphore, 1, nullptr);
	SetEvent(Event_Writer_Ended);
	CloseHandle(Semaphore);
	CloseHandle(Events_Reader[0]);
	CloseHandle(Events_Reader[1]);
	CloseHandle(Event_Writer_A);
	CloseHandle(Event_Writer_B);
	CloseHandle(Event_Writer_Ended);
	system("pause");
}