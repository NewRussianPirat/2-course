#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

class BinaryTree {
private:
	struct Element {
		Element() : Info(0) {}
		explicit Element(long long a) : Info(a) {}
		Element(long long a, Element* l, Element* r) : Info(a), left(l), right(r) {}
		~Element() = default;

		long long Info;
		long long height = 0;
		long long number_of_roots = 0;
		long long max_root = 0;
		bool block = false;
		Element* left = nullptr;
		Element* right = nullptr;
	};
public:
	BinaryTree() = default;
	~BinaryTree() { Erase(Root); }
	void Push(long long a);
	void Remove(Element* e1, Element* e2, long long a);

	void Func(std::string& s);
	long long FirstRound(Element* e);
	void SecondRound(Element* e);
	void ThirdRound(Element* e1, Element* e2);
	void Obhod(Element* e, std::string& s) const;

	void FindRoot(Element* e, long long old_num);
private:
	void Erase(Element* e);

	Element* Root = nullptr;
	long long Max_tree_root = 0;
	long long Max_number_of_roots = 0;
};

void BinaryTree::Erase(Element* e) {
	if (e == nullptr) return;
	Erase(e->left);
	Erase(e->right);
	delete e;
}

void BinaryTree::Push(long long a) {
	if (Root == nullptr) {
		Root = new Element(a);
		return;
	}
	Element* p1 = nullptr;
	Element* p2 = Root;
	while (p2 != nullptr) {
		if (a > p2->Info) {
			p1 = p2;
			p2 = p2->right;
		}
		else if (a < p2->Info) {
			p1 = p2;
			p2 = p2->left;
		}
		else return;
	}
	if (a > p1->Info) {
		p1->right = new Element(a);
	}
	else {
		p1->left = new Element(a);
	}
}

void BinaryTree::Func(std::string& s) {
	FirstRound(Root);
	SecondRound(Root);
	ThirdRound(nullptr, Root);
	Obhod(Root, s);
}

long long BinaryTree::FirstRound(Element* e) {
	if (e == nullptr) return -1;
	long long lh = FirstRound(e->left);
	long long lr = FirstRound(e->right);
	e->height = std::max(lh, lr) + 1;
	e->max_root = lh + lr + 2;
	if (e->max_root > Max_tree_root) {
		Max_tree_root = e->max_root;
	}
	return e->height;
}

void BinaryTree::SecondRound(Element* e) {
	if (e == nullptr) return;
	if (e->max_root == Max_tree_root) {
		FindRoot(e, e->number_of_roots);
	}
	SecondRound(e->left);
	SecondRound(e->right);
}

void BinaryTree::ThirdRound(Element* e1, Element* e2) {
	if (e2 == nullptr) return;
	ThirdRound(e2, e2->right);
	ThirdRound(e2, e2->left);
	if (e2->number_of_roots == Max_number_of_roots) {
		Remove(e1, e2, e2->Info);
	}
}

void BinaryTree::Obhod(Element* e, std::string& s) const {
	if (e == nullptr) return;
	s += std::to_string(e->Info) + "\n";
	Obhod(e->left, s);
	Obhod(e->right, s);
}

void BinaryTree::FindRoot(Element* e, long long old_num) {
	if (e->number_of_roots >= old_num + 4) return;
	++Max_number_of_roots;
	++e->number_of_roots;
	Element* p1 = e->left;
	Element* p2 = e->right;
	while (p1 != nullptr && !p1->block) {
		if (p1->left == nullptr && p1->right == nullptr) {
			++p1->number_of_roots;
			break;
		}

		if (p1->left != nullptr) {
			if (p1->right == nullptr || p1->left->height > p1->right->height) {
				++p1->number_of_roots;
				p1 = p1->left;
				continue;
			}
		}

		if (p1->left == nullptr || p1->right->height > p1->left->height) {
			++p1->number_of_roots;
			p1 = p1->right;
			continue;
		}

		p1->block = true;
		p1->number_of_roots += 2;
		FindRoot(e, old_num);
		break;
	}

	while (p2 != nullptr && !p2->block) {
		if (p2->left == nullptr && p2->right == nullptr) {
			++p2->number_of_roots;
			break;
		}
		if (p2->left != nullptr) {
			if (p2->right == nullptr || p2->left->height > p2->right->height) {
				++p2->number_of_roots;
				p2 = p2->left;
				continue;
			}
		}
		if (p2->left == nullptr || p2->right->height > p2->left->height) {
			++p2->number_of_roots;
			p2 = p2->right;
			continue;
		}

		p2->block = true;
		p2->number_of_roots += 2;
		FindRoot(e, old_num);
		break;
	}

	if (p1 != nullptr) p1->block = false;
	if (p2 != nullptr) p2->block = false;
}

void BinaryTree::Remove(Element* e1, Element* e2, long long a) {
	if (e2 == nullptr) return;
	if (e2->Info < a) Remove(e2, e2->right, a);
	else if (e2->Info > a) Remove(e2, e2->left, a);
	else {
		if (e2->right == nullptr) {
			if (e1 && e1->right && e1->right->Info == a) e1->right = e2->left;
			if (e1 && e1->left && e1->left->Info == a) e1->left = e2->left;
			if (!e1) Root = e2->left;

			delete e2;
		}
		else if (e2->left == nullptr) {
			if (e1 && e1->right && e1->right->Info == a) e1->right = e2->right;
			if (e1 && e1->left && e1->left->Info == a) e1->left = e2->right;
			if (!e1) Root = e2->right;

			delete e2;
		}
		else {
			Element* p = e2->right;
			while (p->left != nullptr) {
				p = p->left;
			}

			long long k = p->Info;
			Remove(e1, e2, k);
			e2->Info = k;
		}
	}
}

void main() {
	BinaryTree t;
	FILE* fin, * fout;
	fopen_s(&fin, "in.txt", "r");
	fopen_s(&fout, "out.txt", "w");
	long long a;
	while (!feof(fin)) {
		fscanf_s(fin, "%lld", &a);
		t.Push(a);
	}
	std::string s;
	t.Func(s);
	fprintf(fout, "%s", s.c_str());
}
