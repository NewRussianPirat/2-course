#include <iostream>
#include <vector>

int FindSet(std::vector<int>& v, int x) {
	if (v[x] < 0) {
		return x;
	}
	v[x] = FindSet(v, v[x]);
	return v[x];
}

void Union(std::vector<int>& v, int u, int w, int& k) {
	u = FindSet(v, u);
	w = FindSet(v, w);
	if (u != w) {
		if (v[u] <= v[w]) {
			v[u] += v[w];
			v[w] = u;
			--k;
		}
		else {
			v[w] += v[u];
			v[u] = w;
			--k;
		}
	}
}

void main() {
	FILE* in;
	FILE* out;
	fopen_s(&in, "input.txt", "r");
	fopen_s(&out, "output.txt", "w");
	int n;
	int q;
	fscanf_s(in, "%d %d", &n, &q);
	std::vector<int> v(n, -1);
	int k = n;
	for (int i = 0; i < q; ++i) {
		int u;
		int w;
		fscanf_s(in, "%d %d", &u, &w);
		--u;
		--w;
		Union(v, u, w, k);
		fprintf_s(out, "%d\n", k);
	}
}
