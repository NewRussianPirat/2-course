#include <stdlib.h>
#include <iostream>

void main(int argc, char* argv[]) {
	if (argc > 1) {
		int n = atoi(argv[1]);
		int k = atoi(argv[2]);
		std::cout << "n = " << n << ", k = " << k << "\nArray: ";
		for (int i = 3; i < argc; ++i) {
			std::cout << argv[i] << " ";
		}
		double result = 0;
		for (int i = 3; i <= 3 + k; ++i) {
			result += atof(argv[i]);
		}
		std::cout << "\nSum of elements from Array[0] to Array[" << k << "] = " << result << std::endl;
	}
	else {
		std::cout << "ERROR!!!!!!!!!!!!!!!" << std::endl;
	}
	system("pause");
}