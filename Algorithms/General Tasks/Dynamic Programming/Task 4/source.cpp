#include <iostream>
#include <vector>

struct str {
	int n;
	int m;
	long long znach;
};

void main() {
	FILE* fi;
	FILE* fo;
	fopen_s(&fi, "input.txt", "r");
	fopen_s(&fo, "output.txt", "w");
	int s;
	fscanf_s(fi, "%d", &s);
	std::vector<std::vector<str>> F(s, std::vector<str>(s, { 0,0,0 }));
	for (int i = 0; i < s; ++i) {
		fscanf_s(fi, "%d %d", &F[i][i].n, &F[i][i].m);
	}
	for (int i = 1; i < s; ++i) {
		for (int j = 0; j < s - i; ++j) {
			if (i == 1) {
				F[j][j + i].n = F[j][j].n;
				F[j][j + i].m = F[j + 1][j + 1].m;
				F[j][j + i].znach = F[j][j].n * F[j][j].m * F[j + 1][j + 1].m;
			}
			else {
				F[j][j + i].n = F[j][j].n;
				F[j][j + i].m = F[j + 1][j + i].m;
				F[j][j + i].znach = LLONG_MAX;
				for (int k = j; k < j + i; ++k) {
					long long a = F[j][k].znach + F[k + 1][j + i].znach + F[j][k].n * F[j][k].m * F[k + 1][j + i].m;
					if (a < F[j][j + i].znach) {
						F[j][j + i].znach = a;
					}
				}
			}
		}
	}
	fprintf_s(fo, "%lld", F[0][s - 1].znach);
}
