#include <iostream>
#include <vector>

long long LowerBound(long long zapr, std::vector<long long>& arr) {
	unsigned long long l = 0;
	auto r = arr.size();
	unsigned long long i;
	while (l < r) {
		i = (l + r) / 2;
		if (zapr <= arr[i]) {
			r = i;
		}
		else {
			l = i + 1;
		}
	}
	return l;
}

void main() {
	FILE* in;
	FILE* out;
	fopen_s(&in, "input.txt", "r");
	fopen_s(&out, "output.txt", "w");
	int n;
	fscanf_s(in, "%d", &n);
	std::vector<long long> arr(n);
	std::vector<long long> F;
	F.reserve(n);
	for (int i = 0; i < n; ++i) {
		fscanf_s(in, "%lld", &arr[i]);
	}
	F.push_back(arr[0]);
	for (int i = 1; i < n; ++i) {
		long long k = LowerBound(arr[i], F);
		if (k == i || k >= F.size()) {
			F.push_back(arr[i]);
		}
		else {
			F[k] = arr[i];
		}
	}
	fprintf_s(out, "%lld", F.size());
}
