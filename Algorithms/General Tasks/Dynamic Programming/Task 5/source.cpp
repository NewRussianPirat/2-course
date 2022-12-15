#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

void main() {
	int n;
	scanf_s("%d", &n);
	std::vector<int> str1(n);
	std::vector<int> str2(n);
	std::vector<std::vector<int>> matr(n + 1, std::vector<int>(n + 1, 0));
	for (int i = 0; i < n; ++i) {
		scanf_s("%d", &str1[i]);
	}
	for (int i = 0; i < n; ++i) {
		scanf_s("%d", &str2[i]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (str1[i - 1] == str2[j - 1]) {
				matr[i][j] = matr[i - 1][j - 1] + 1;
			}
			else {
				matr[i][j] = std::max(matr[i][j - 1], matr[i - 1][j]);
			}
		}
	}
	printf_s("%d", matr[n][n]);
	int i = n;
	int j = n;
	std::vector<int> s1;
	std::vector<int> s2;
	while (i != 0 && j != 0) {
		if (str1[i - 1] == str2[j - 1]) {
			s1.push_back(i - 1);
			s2.push_back(j - 1);
			--i;
			--j;
		}
		else {
			if (matr[i][j] == matr[i - 1][j]) {
				--i;
			}
			else {
				--j;
			}
		}
	}
	if (!s1.empty()) {
		printf_s("\n");
		for (auto it = s1.rbegin(); it != s1.rend(); ++it) {
		    std::cout << *it << " ";
		}
		printf_s("\n");
		for (auto it = s2.rbegin(); it != s2.rend(); ++it) {
			std::cout << *it << " ";
		}
	}
}
