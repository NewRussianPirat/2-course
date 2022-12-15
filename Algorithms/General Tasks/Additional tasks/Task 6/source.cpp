#include <iostream>
#include <vector>

int FindSet(std::vector<int>& v, int x) {
	if (v[x] < 0) {
		return x;
	}
	v[x] = FindSet(v, v[x]);
	return v[x];
}

bool Union(std::vector<int>& v, int u, int w) {
	u = FindSet(v, u);
	w = FindSet(v, w);
	if (u != w) {
		if (v[u] <= v[w]) {
			v[u] += v[w];
			v[w] = u;
		}
		else {
			v[w] += v[u];
			v[u] = w;
		}
		return true;
	}
	else {
		return false;
	}
}

void main() {
	FILE* in;
	FILE* out;
	fopen_s(&in, "input.txt", "r");
	fopen_s(&out, "output.txt", "w");
	int n;
	int m;
	int q;
	fscanf_s(in, "%d %d %d", &n, &m, &q);
	std::vector<int> v(n, -1);
	std::vector<std::pair<int, int>> v1(m);
	std::vector<std::pair<int, int>> v2(m);
	std::vector<int> v3(q);
	std::vector<char> str(q);
	for (int i = 0; i < m; ++i) {
		fscanf_s(in, "%d %d", &v1[i].first, &v1[i].second);
		v2[i].first = v1[i].first;
		v2[i].second = v1[i].second;
	}
	for (int i = 0; i < q; ++i) {
		int k;
		fscanf_s(in, "%d", &k);
		--k;
		v1[k].first = v1[k].second = 0;
		v3[i] = k;
	}
	--n;
	for (int i = 0; i < v1.size(); ++i) {
		if (v1[i].first != 0) {
			if (Union(v, v1[i].first - 1, v1[i].second - 1)) {
				--n;
			}
		}
	}
	for (int i = q - 1; i >= 0; --i) {
		if (n == 0) {
			for (int j = i; j >= 0; --j) {
				str[j] = '1';
			}
			break;
		}
		if (Union(v, v2[v3[i]].first - 1, v2[v3[i]].second - 1)) {
			--n;
		}
		str[i] = '0';
	}
	for (int i = 0; i < q; ++i) {
		fprintf_s(out, "%c", str[i]);
	}
}
