#include <iostream>
#include <vector>
#include <queue>

void DFS(int i, std::vector<int>& visited, std::vector<std::vector<int>>& matr, int& k) {
	if (visited[i] == 0) {
		visited[i] = k;
		++k;
	}
	for (int j = 0; j < matr.size(); ++j) {
		if (matr[i][j] == 1 && visited[j] == 0) {
			DFS(j, visited, matr, k);
		}
	}
}

void main() {
	FILE* fin;
	FILE* fout;
	fopen_s(&fin, "input.txt", "r");
	fopen_s(&fout, "output.txt", "w");
	int n;
	fscanf_s(fin, "%d", &n);
	std::vector<std::vector<int>> matr(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fscanf_s(fin, "%d", &matr[i][j]);
		}
	}
	std::vector<int> visited(n, 0);
	int k = 1;
	for (int i = 0; i < n; ++i) {
		DFS(i, visited, matr, k);
	}
	for (int i = 0; i < n; ++i) {
		fprintf_s(fout, "%d ", visited[i]);
	}
}
