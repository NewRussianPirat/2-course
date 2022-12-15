#include <iostream>
#include <vector>

long long sochet(unsigned int n, unsigned int k) {
	std::vector<std::vector<long long>> v(n + 1, std::vector<long long> (n + 1, 1));
	for (int i = 0; i < n + 1; ++i) {
		for (int j = 1; j < i; ++j) {
			v[i][j] = v[i - 1][j - 1] + v[i - 1][j];
			if (v[i][j] >= 1000000007) {
				v[i][j] %= 1000000007;
			}
		}
	}
	return v[n][k];
}

void main() {
	unsigned int N;
	unsigned int K;
	scanf_s("%d %d", &N, &K);
	long long result;
	result = sochet(N, K);
	printf_s("%lld", result);
}
