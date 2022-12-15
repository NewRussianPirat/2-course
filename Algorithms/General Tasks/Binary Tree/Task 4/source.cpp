#include <fstream>

void main() {
	std::ofstream fout("bst.out");
	FILE* fi;
	fopen_s(&fi, "bst.in", "r");
	int n;
	long long v;
	fscanf_s(fi, "%d %lld", &n, &v);
	long long* arrNum = new long long[n];
	arrNum[0] = v;
	std::pair<long long, long long>* arrProm = new std::pair<long long, long long>[n];
	arrProm[0].first = -20000000000;
	arrProm[0].second = 20000000000;
	long long m;
	int p;
	char c;
	for (int i = 1; i < n; ++i) {
		fscanf_s(fi, "%lld %d %c", &m, &p, &c);
		if (c == 'R') {
			arrProm[i].first = arrNum[p - 1] - 1;
			arrProm[i].second = arrProm[p - 1].second;
			if (m <= arrProm[i].first || m >= arrProm[i].second) {
				fout << "NO";
				return;
			}
		}
		else {
			arrProm[i].second = arrNum[p - 1];
			arrProm[i].first = arrProm[p - 1].first;
			if (m <= arrProm[i].first || m >= arrProm[i].second) {
				fout << "NO";
				return;
			}
		}

		arrNum[i] = m;
	}

	fout << "YES";
}
