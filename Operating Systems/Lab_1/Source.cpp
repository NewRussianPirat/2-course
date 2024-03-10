#include <iostream>
#include <Windows.h>
#include <process.h>

struct STR {
	INT n;
	PINT arr;
};

DWORD WINAPI Worker(LPVOID a) {
	auto s = (STR*)(a);
	DWORD sum = 0;
	for (INT i = 0; i < s->n; ++i) {
		sum += s->arr[i];
		Sleep(12);
	}
	ExitThread(sum / s->n);
}

void main() {
	STR a;
	HANDLE hThread;
	DWORD result;
	DWORD StartTime;
	DWORD StopTime;
	std::cout << "Enter n: ";
	std::cin >> a.n;
	a.arr = new INT[a.n];
	srand(time(nullptr));
	for (INT i = 0; i < a.n; ++i) {
		a.arr[i] = rand() % 100;
		std::cout << a.arr[i] << ' ';
	}
	std::cout << "\nEnter StartTime and StopTime in milliseconds: ";
	std::cin >> StartTime >> StopTime;
	hThread = CreateThread(nullptr, 0, Worker, &a, CREATE_SUSPENDED, nullptr);
	if (hThread == nullptr) {
		std::cout << "Thread wasn't created";
		return;
	}
	Sleep(StartTime);
	ResumeThread(hThread);
	Sleep(StopTime);
	SuspendThread(hThread);
	Sleep(500);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &result);
	std::cout << "arithmetical mean = " << result;
	result = 0;
	hThread = (HANDLE)_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)Worker, &a, 0, nullptr);
	if (hThread == nullptr) {
		std::cout << "Thread wasn't created";
		return;
	}
	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &result);
	std::cout << "\narithmetical mean = " << result;
	CloseHandle(hThread);
}