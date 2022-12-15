#include <iostream>
#include <vector>
#include <string>

void main() {
	int n1;
	std::cin >> n1;
	std::vector<long long> v1(n1);
	for (int i = 0; i < n1; ++i) {
		std::cin >> v1[i];
	}
	auto n2 = (int)sqrt(n1);
	std::vector<long long> v2(n2, 0);
	int blok_size = (n1 % n2) ? (n1 / n2) + 1 : n1 / n2;
	for (int i = 0, k = 0; i < n1; ++i) {
		v2[k] += v1[i];
		if ((i + 1) % blok_size == 0) {
			++k;
		}
	}
	int number_requests;
	std::cin >> number_requests;
	for (int i = 0; i < number_requests; ++i) {
		std::string str;
		std::cin >> str;
		if (str == "Add") {
			int ind;
			std::cin >> ind;
			long long slag;
			std::cin >> slag;
			v1[ind] += slag;
			v2[ind / blok_size] += slag;
		}
		else {
			int first_ind;
			std::cin >> first_ind;
			int last_ind;
			std::cin >> last_ind;
			int first_blok = first_ind / blok_size;
			int last_blok = (last_ind - 1) / blok_size;
			long long result = 0;
			if (first_blok == last_blok) {
				for (int k = first_ind; k < last_ind; ++k) {
					result += v1[k];
				}
			}
			else {
				for (int k = first_ind; k < (first_blok + 1) * blok_size; ++k) {
					result += v1[k];
				}
				for (int k = first_blok + 1; k < last_blok; ++k) {
					result += v2[k];
				}
				for (int k = last_blok * blok_size; k < last_ind; ++k) {
					result += v1[k];
				}
			}
			std::cout << result << std::endl;
		}
	}
}
