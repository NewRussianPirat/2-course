#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex critical_section_1;
std::mutex critical_section_2;
std::mutex event;

void Work(std::vector<char>& array, int n, int& k) {
	std::unique_lock critical_section_1_locker(critical_section_1);
	std::cout << "\nEnter time interval (milliseconds): ";
	int interval;
	std::cin >> interval;

	int i = 0;
	for (int j = 0; j < n; ++j) {
		if (array[j] >= '0' && array[j] <= '9') {
			if (i != j) {
				array[i] = array[j];
			}
			++i;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}

	if (i < k) {
		k = i;
	}

	for (i; i < n; ++i) {
		array[i] = ' ';
	}

	critical_section_1_locker.unlock();
}

void SumElement(std::vector<char>& array, int& k, int& result) {
	std::unique_lock critical_section_2_locker(critical_section_2);
	std::unique_lock event_locker(event);

	for (int i = 0; i < k; ++i) {
		result += array[i] - '0';
	}
	result /= k;

	critical_section_2_locker.unlock();
}

void main() {
	int n;
	int k;
	int result = 0;
	std::cout << "Enter array size: ";
	std::cin >> n;
	std::vector<char> array(n);
	std::cout << "Enter array elements: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> array[i];
	}
	std::cout << "Array size: " << array.size() << "\nArray: ";
	for (auto it : array) {
		std::cout << it << " ";
	}

	std::cout << "\nEnter k: ";
	std::cin >> k;

	std::unique_lock critical_section_2_locker(critical_section_2);

	std::jthread work(Work, std::ref(array), n, std::ref(k));
	std::jthread sumElement(SumElement, std::ref(array), std::ref(k), std::ref(result));
	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	std::unique_lock critical_section_1_locker(critical_section_1);

	std::cout << "New array: ";
	for (auto it : array) {
		std::cout << it << " ";
	}

	critical_section_1_locker.unlock();
	critical_section_2_locker.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	std::unique_lock event_locker(event);
	std::cout << "\nResult = " << result;
	event_locker.unlock();
}