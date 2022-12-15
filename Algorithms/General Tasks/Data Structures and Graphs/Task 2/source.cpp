#include <iostream> 
#include <vector>

void main() {
	FILE* in;
	FILE* out;
	fopen_s(&in, "input.txt", "r");
	fopen_s(&out, "output.txt", "w");
	long long m;
	long long c;
	long long n;
	fscanf_s(in, "%lld %lld %lld", &m, &c, &n);
	std::vector<long long> v(m, -1);
	for (int y = 0; y < n; ++y) {
		long long x;
		fscanf_s(in, "%lld", &x);
		for (int i = 0; i < m; ++i) {
			long long a = ((x % m) + c * i) % m;
			if (v[a] == -1) {
				v[a] = x;
				break;
			}
			else if (v[a] == x) {
				break;
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		fprintf_s(out, "%lld ", v[i]);
	}
}
