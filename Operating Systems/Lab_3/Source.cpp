#include <iostream>
#include <Windows.h>

CRITICAL_SECTION cs1;
CRITICAL_SECTION cs2;
HANDLE Event;

struct Array {
	int k;
	int n;
	char* arr;
	int result;
};

DWORD WINAPI work(LPVOID Arr) {
	EnterCriticalSection(&cs1);
	auto massiv = (Array*)(Arr);
	std::cout << "\nEnter time interval (milliseconds): ";
	int Interval;
	std::cin >> Interval;
	int i = 0;
	for (int j = 0; j < massiv->n; ++j) {
		if (massiv->arr[j] >= '0' && massiv->arr[j] <= '9') {
			if (i != j) {
				massiv->arr[i] = massiv->arr[j];
			}
			++i;
			Sleep(Interval);
		}
	}
	if (i < massiv->k) {
		massiv->k = i;
	}
	for (i; i < massiv->n; ++i) {
		massiv->arr[i] = ' ';
	}
	LeaveCriticalSection(&cs1);
	return 0;
}

DWORD WINAPI sumElement(LPVOID Arr) {
	EnterCriticalSection(&cs2);
	auto massiv = (Array*)Arr;
	massiv->result = 0;
	for (int i = 0; i < massiv->k; ++i) {
		massiv->result += massiv->arr[i] - '0';
	}
	massiv->result /= massiv->k;
	SetEvent(Event);
	LeaveCriticalSection(&cs2);
	return 0;
}

void main() {
	Array massiv;
	std::cout << "Enter array size: ";
	std::cin >> massiv.n;
	massiv.arr = new char[massiv.n];
	std::cout << "Enter elements (char): ";
	for (int i = 0; i < massiv.n; ++i) {
		std::cin >> massiv.arr[i];
	}
	std::cout << "Array size: " << massiv.n << "\nArray: ";
	for (int i = 0; i < massiv.n; ++i) {
		std::cout << massiv.arr[i] << " ";
	}

	DWORD IDThread_1;
	DWORD IDThread_2;
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);
	
	EnterCriticalSection(&cs2);
	
	HANDLE Work = CreateThread(nullptr, NULL, work, &massiv, CREATE_SUSPENDED, &IDThread_1);
	if (Work == nullptr) {
		std::cout << "Thread Work wasn't crated";

		LeaveCriticalSection(&cs2);
		CloseHandle(Event);
		DeleteCriticalSection(&cs1);
		DeleteCriticalSection(&cs2);
		return;
	}
	HANDLE SumElement = CreateThread(nullptr, NULL, sumElement, &massiv, CREATE_SUSPENDED, &IDThread_2);
	if (SumElement == nullptr) {
		std::cout << "Thread SumElement wasn't crated";

		LeaveCriticalSection(&cs2);
		CloseHandle(Event);
		DeleteCriticalSection(&cs1);
		DeleteCriticalSection(&cs2);
		return;
	}
	std::cout << "\nEnter k: ";
	std::cin >> massiv.k;
	ResumeThread(Work);
	ResumeThread(SumElement);
	Sleep(1);
	EnterCriticalSection(&cs1);
	std::cout << "New array: ";
	for (int i = 0; i < massiv.n; ++i) {
		std::cout << massiv.arr[i] << " ";
	}
	LeaveCriticalSection(&cs1);

	LeaveCriticalSection(&cs2);
	Sleep(1);
	WaitForSingleObject(Event, INFINITE);

	std::cout << "\nResult = " << massiv.result;
	
	CloseHandle(Work);
	CloseHandle(SumElement);
	CloseHandle(Event);
	DeleteCriticalSection(&cs1);
	DeleteCriticalSection(&cs2);
}