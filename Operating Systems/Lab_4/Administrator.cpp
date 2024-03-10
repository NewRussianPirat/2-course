#include <iostream>
#include <Windows.h>
#include <string>

void main() {
	auto* Mutex = CreateMutex(nullptr, FALSE, L"Mutex");
	auto* Event_Reader_Ended = CreateEvent(nullptr, FALSE, FALSE, L"Reader_Ended");
	auto* Event_Writer_Ended = CreateEvent(nullptr, FALSE, FALSE, L"Writer_Ended");
	auto* Event_Reader_A = CreateEvent(nullptr, FALSE, FALSE, L"Reader_A");
	auto* Event_Reader_B = CreateEvent(nullptr, FALSE, FALSE, L"Reader_B");
	auto* Events_Writer = new HANDLE[2];
	Events_Writer[0] = CreateEvent(nullptr, FALSE, FALSE, L"Writer_A");
	Events_Writer[1] = CreateEvent(nullptr, FALSE, FALSE, L"Writer_B");

	int n;
	int n_w;
	int n_r;
	std::cout << "Administrator: Enter number of processes: ";
	std::cin >> n;
	std::cout << "Administrator: Enter number of sended messages for Writer and Reader: ";
	std::cin >> n_w >> n_r;

	auto* si_r = new STARTUPINFO[n];
	auto* si_w = new STARTUPINFO[n];
	auto* pi_r = new PROCESS_INFORMATION[n];
	auto* pi_w = new PROCESS_INFORMATION[n];
	auto* Semaphore = CreateSemaphore(nullptr, 2, 2, L"Semaphore");

	std::wstring str_r = L"\"Reader.exe\" ";
	str_r += std::to_wstring(n_r);
	auto* wstr_r = new wchar_t[str_r.length()];
	wcscpy_s(wstr_r, str_r.length() + 1, str_r.c_str());

	std::wstring str_w = L"\"Writer.exe\" ";
	str_w += std::to_wstring(n_w);
	auto* wstr_w = new wchar_t[str_w.length()];
	wcscpy_s(wstr_w, str_w.length() + 1, str_w.c_str());

	for (int i = 0; i < n; ++i) {
		ZeroMemory(&si_r[i], sizeof(STARTUPINFO));
		ZeroMemory(&si_w[i], sizeof(STARTUPINFO));
		if (!CreateProcess(nullptr, wstr_r, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si_r[i], &pi_r[i])) {
			std::cout << "Administrator: Reader opening Error";
			CloseHandle(Mutex);
			CloseHandle(Semaphore);
			CloseHandle(Event_Reader_Ended);
			CloseHandle(Event_Writer_Ended);
			CloseHandle(Event_Reader_A);
			CloseHandle(Event_Reader_B);
			CloseHandle(Events_Writer[0]);
			CloseHandle(Events_Writer[1]);
			return;
		}
		if (!CreateProcess(nullptr, wstr_w, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si_w[i], &pi_w[i])) {
			std::cout << "Administrator: Writer opening Error";
			CloseHandle(Mutex);
			CloseHandle(Semaphore);
			CloseHandle(Event_Reader_Ended);
			CloseHandle(Event_Writer_Ended);
			CloseHandle(Event_Reader_A);
			CloseHandle(Event_Reader_B);
			CloseHandle(Events_Writer[0]);
			CloseHandle(Events_Writer[1]);
			return;
		}
	}

	for (int i = 0; i < n * n_w; ++i) {
		int k = WaitForMultipleObjects(2, Events_Writer, FALSE, INFINITE);
		k -= WAIT_OBJECT_0;
		if (k == 0) {
			ResetEvent(Events_Writer[0]);
			std::cout << "Administrator: A\n";
		}
		else {
			ResetEvent(Events_Writer[0]);
			std::cout << "Administrator: B\n";
		}
		if (!((i + 1) % n_w)) {
			WaitForSingleObject(Event_Reader_Ended, INFINITE);
			std::cout << "Administrator: Reader ended\n";
			WaitForSingleObject(Event_Writer_Ended, INFINITE);
			std::cout << "Administrator: Writer ended\n";
		}
	}

	CloseHandle(Mutex);
	CloseHandle(Semaphore);
	CloseHandle(Event_Reader_Ended);
	CloseHandle(Event_Writer_Ended);
	CloseHandle(Event_Reader_A);
	CloseHandle(Event_Reader_B);
	CloseHandle(Events_Writer[0]);
	CloseHandle(Events_Writer[1]);
}