#include <iostream>
#include <Windows.h>
#include <string>

void main(int argc, char* argv[]) {
	std::cout << "Enter array size: ";
	int n;
	int k;
	std::cin >> n;
	auto* arr = new double[n];
	std::cout << "Enter array element: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}
	std::cout << "Enter 0 <= k < n: ";
	std::cin >> k;
	while (k < 0 || k >= n) {
		std::cout << "Wrong k, try again:" << std::endl;
		std::cout << "Enter 0 <= k < n: ";
		std::cin >> k;
	}
	std::wstring s = L"\"Child.exe\" ";
	s += std::to_wstring(n) + L" ";
	s += std::to_wstring(k) + L" ";
	for (int i = 0; i < n; ++i) {
		s += std::to_wstring(arr[i]) + L" ";
	}
	auto* str = new wchar_t[s.length()];
	wcscpy_s(str, s.length() + 1, s.c_str());
	STARTUPINFO lpStartUpInfo;
	PROCESS_INFORMATION lpProcessInformation;
	ZeroMemory(&lpStartUpInfo, sizeof(STARTUPINFO));
	lpStartUpInfo.dwFlags = STARTF_USEFILLATTRIBUTE;
	lpStartUpInfo.dwFillAttribute = FOREGROUND_BLUE;
	if (!CreateProcess(nullptr, str, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &lpStartUpInfo, &lpProcessInformation)) {
		std::cout << "Process is not created";
	}
	else {
		std::cout << "Process is created" << std::endl;
		WaitForSingleObject(lpProcessInformation.hProcess, INFINITE);
	}
	CloseHandle(lpProcessInformation.hThread);
	CloseHandle(lpProcessInformation.hProcess);
	system("pause");
}