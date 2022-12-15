#include <iostream>
#include <fstream>
#include <set>
void main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::set<int> s;
	while (fin) {
		int a;
		fin >> a;
		s.insert(a);
	}
	long long sum = 0;
	for (auto it = s.begin(); it != s.end(); ++it) {
		sum += *it;
	}
	fout << sum << std::endl;
}
