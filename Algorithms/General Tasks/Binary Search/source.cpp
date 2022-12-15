#include <iostream>

bool BinarySearch(int zapr, int* arr, int n) {
	int l = 0;
	int r = n;
	int i;
	while (l < r) {
		i = (l + r) / 2;
		if (zapr == arr[i]) {
			return true;
		}
		else if (zapr < arr[i]) {
			r = i;
		}
		else {
			l = i + 1;
		}
	}
	return false;
}

int LowerBound(int zapr, int* arr, int n) {
	int l = 0;
	int r = n;
	int i;
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

int UpperBound(int zapr, int* arr, int n) {
	int l = 0;
	int r = n;
	int i;
	while (l < r) {
		i = (l + r) / 2;
		if (zapr < arr[i]) {
			r = i;
		}
		else {
			l = i + 1;
		}
	}

	return l;
}

void main() {
	int n;
	scanf_s("%d", &n);
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		scanf_s("%d", &arr[i]);
	}
	int k;
	scanf_s("%d", &k);
	int zapr;
	int b;
	int l;
	int r;
	for (int i = 0; i < k; ++i) {
		scanf_s("%d", &zapr);
		bool tf = BinarySearch(zapr, arr, n);
		if (tf) {
			b = 1;
		}
		else {
			b = 0;
		}
		l = LowerBound(zapr, arr, n);
		r = UpperBound(zapr, arr, n);
		printf("%d %d %d\n", b, l, r);
	}
}
