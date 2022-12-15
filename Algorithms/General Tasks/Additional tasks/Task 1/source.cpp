#include <iostream>
#include <queue>
#include <vector>

void main() {
	FILE* fin;
	FILE* fout;
	fopen_s(&fin, "huffman.in", "r");
	fopen_s(&fout, "huffman.out", "w");
	int n;
	fscanf_s(fin, "%d", &n);
	std::priority_queue<long long, std::vector<long long>, std::greater<long long>> v;
	for (int i = 0; i < n; ++i) {
		long long k;
		fscanf_s(fin, "%lld", &k);
		v.push(k);
	}
	long long sum = 0;
	while (v.size() != 1) {
		long long k = v.top();
		v.pop();
		long long m = v.top();
		v.pop();
		v.push(k + m);
		sum += k + m;
	}
	fprintf_s(fout, "%lld", sum);
}
