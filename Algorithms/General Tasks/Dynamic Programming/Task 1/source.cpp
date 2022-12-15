#include <iostream>
#include <algorithm>
#include <vector>

void main() {
	FILE* fi;
	FILE* fo;
	fopen_s(&fi, "input.txt", "r");
	fopen_s(&fo, "output.txt", "w");
	int n = 0;
	fscanf_s(fi, "%i", &n);
	std::vector<int> arr;
	arr.resize(n + 1);
	arr[0] = -1;
	for (int i = 1; i < n + 1; ++i) {
		fscanf_s(fi, "%i", &arr[i]);
	}
	if (n > 1) arr[2] = -1;
	for (int i = 3; i <= n; ++i) {
		arr[i] += std::max(arr[i - 2], arr[i - 3]);
	}
	fprintf_s(fo, "%i", arr[n]);
}
