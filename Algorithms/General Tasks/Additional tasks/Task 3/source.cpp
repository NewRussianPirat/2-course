#include <iostream>

void main() {
	FILE* in;
	FILE* out;
	fopen_s(&in, "input.txt", "r");
	fopen_s(&out, "output.txt", "w");
	long long n;
	fscanf_s(in, "%lld", &n);
	int i = 0;
	while (n > 0) {
		if (n % 2 == 1) {
			fprintf_s(out, "%d\n", i);
		}
		n >>= 1;
		++i;
	}
}
