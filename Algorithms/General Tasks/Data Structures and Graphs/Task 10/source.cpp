#include <iostream>
#include <vector>
#include <queue>
#include <list>

void Insert(std::vector<std::pair<int, long long>>& min_heap, int v, long long k) {
	min_heap.push_back(std::make_pair(v, k));
	int i = min_heap.size() - 1;
	while (i > 0) {
		int j = (i - 1) / 2;
		if (min_heap[i].second >= min_heap[j].second) {
			break;
		}
		std::swap(min_heap[i], min_heap[j]);
		i = j;
	}
}

void DeleteMin(std::vector<std::pair<int, long long>>& min_heap) {
	min_heap[0] = min_heap[min_heap.size() - 1];
	min_heap.pop_back();
	int i = 0;
	while (2 * i + 1 < min_heap.size()) {
		int j;
		if (2 * i + 2 == min_heap.size() || min_heap[2 * i + 1].second < min_heap[2 * i + 2].second) {
			j = 2 * i + 1;
		}
		else {
			j = 2 * i + 2;
		}
		if (min_heap[j].second > min_heap[i].second) {
			break;
		}
		std::swap(min_heap[i], min_heap[j]);
		i = j;
	}
}

void main() {
	FILE* fin;
	FILE* fout;
	fopen_s(&fin, "input.txt", "r");
	fopen_s(&fout, "output.txt", "w");
	int n;
	int m;
	fscanf_s(fin, "%d %d", &n, &m);
	std::vector<std::vector<std::pair<int, long long>>> matr(n, std::vector<std::pair<int, long long>>());
	for (int i = 0; i < m; ++i) {
		int v;
		int w;
		long long k;
		fscanf_s(fin, "%d %d %lld", &v, &w, &k);
		matr[v - 1].push_back(std::make_pair(w - 1, k));
		matr[w - 1].push_back(std::make_pair(v - 1, k));
	}

	std::vector<bool> processed(n, false);
	std::vector<long long> dist(n, LLONG_MAX);
	std::vector<std::pair<int, long long>> min_heap;
	Insert(min_heap, 0, 0);
	while (!min_heap.empty()) {
		std::pair<int, long long> pair = min_heap[0];
		DeleteMin(min_heap);
		if (processed[pair.first]) {
			continue;
		}
		processed[pair.first] = true;
		dist[pair.first] = pair.second;
		for (int i = 0; i < matr[pair.first].size(); ++i) {
			if (!processed[matr[pair.first][i].first] && pair.second + matr[pair.first][i].second < dist[matr[pair.first][i].first]) {
				Insert(min_heap, matr[pair.first][i].first, pair.second + matr[pair.first][i].second);
			}
		}
	}
	fprintf_s(fout, "%lld", dist[n - 1]);
}
