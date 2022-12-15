#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	std::string s1;
	std::getline(in, s1);
	int n = s1.length();
	std::vector<std::vector<int>> matr(n, std::vector<int>(n, 1));
	for (int j = 1; j < n; ++j) {
		for (int i = j - 1; i >= 0; --i) {
			if (i == j - 1) {
				if (s1[i] == s1[j]) {
					matr[i][j] = 2;
				}
			}
			else {
				if (s1[i] == s1[j]) {
					matr[i][j] = matr[i + 1][j - 1] + 2;
				}
				else {
					matr[i][j] = std::max(matr[i + 1][j], matr[i][j - 1]);
				}
			}
		}
	}
	int i = 0;
	int j = n - 1;
	std::vector<char> str(matr[0][n - 1]);
	int k1 = 0;
	int k2 = matr[0][n - 1] - 1;
	while (j >= i) {
		if (s1[i] == s1[j]) {
			str[k1] = s1[i];
			str[k2] = s1[i];
			++k1;
			--k2;
			++i;
			--j;
		}
		else {
			if (matr[i + 1][j] >= matr[i][j - 1]) {
				++i;
			}
			else {
				--j;
			}
		}
	}
	out << matr[0][n - 1] << std::endl;
	for (int i = 0; i < matr[0][n - 1]; ++i) {
		out << str[i];
	}
	in.close();
	out.close();
}
