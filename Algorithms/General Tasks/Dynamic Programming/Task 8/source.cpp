#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void main() {
	std::ifstream in("in.txt");
	std::ofstream out("out.txt");
	long long x;
	long long y;
	long long z;
	std::string s1;
	std::string s2;
	in >> x;
	in.get();
	in >> y;
	in.get();
	in >> z;
	in.get();
	std::getline(in, s1);
	std::getline(in, s2);
	std::vector<std::vector<long long>> F(s1.length() + 1, std::vector<long long>(s2.length() + 1, 0));
	for (int i = 1; i < F[0].size(); ++i) {
		F[0][i] = i * y;
	}
	for (int i = 1; i < s1.length() + 1; ++i) {
		F[i][0] = i * x;
		for (int j = 1; j < F[i].size(); ++j) {
			int d = (s2[j - 1] == s1[i - 1]) ? 0 : 1;
			F[i][j] = std::min(F[i - 1][j] + x, std::min(F[i][j - 1] + y, F[i - 1][j - 1] + d * z));
		}
	}
	out << F[s1.length()][s2.length()];
}
