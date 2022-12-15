#include <iostream>
#include <vector>

long long sochet(int n, int k) {
	long long N = 1;
	long long K = 1;
	long long N_K = 1;
	long long e = 1000000007;
	for (int i = 2; i <= n; ++i) {
		N = (N * (i % e)) % e;
		if (i <= k) K = (K * (i % e)) % e;
		if (i <= n - k) N_K = (N_K * (i % e)) % e;
	}
	int bK = 1;
	int bN_K = 1;
	e -= 2;
	while (e != 0) {
		if (e % 2) {
			--e;
			bK = (bK * K) % 1000000007;
			bN_K = (bN_K * N_K) % 1000000007;
		}
		else {
			e >>= 1;
			K = (K * (K % 1000000007)) % 1000000007;
			N_K = (N_K * (N_K % 1000000007)) % 1000000007;
		}
	}
	return (((N * bK) % 1000000007) * bN_K) % 1000000007;
}

void main() {
	int N;
	int K;
	scanf_s("%d %d", &N, &K);
	long long result;
	result = sochet(N, K);
	printf_s("%lld", result);
}
