#include <iostream>
#include <string>
#include <fstream>
class BinaryTree {
private:
	struct Element {
		Element() : Info(0), left(nullptr), right(nullptr) {}
		explicit Element(int a) : Info(a), left(nullptr), right(nullptr) {}
		Element(int a, Element* l, Element* r) : Info(a), left(l), right(r) {}
		~Element() {}

		int Info;
		Element* left;
		Element* right;
	};
public:
	BinaryTree() : Root(nullptr) {}
	~BinaryTree() { Erase(Root); }
	void Push(int a);
	void Remove(int a);
	void Remove(Element* e1, Element* e2, int a);
	void LevObh(std::string& s);
	void LevObh(Element* e, std::string& s);
private:
	void Erase(Element* e);
	void Push(Element** ee, Element* e, int a);

	Element* Root;
};

void BinaryTree::Erase(Element* e) {
	if (e == nullptr) return;
	Erase(e->left);
	Erase(e->right);
	delete e;
}

void BinaryTree::Push(int a) {
	Element** ee = &Root;
	Element* e = Root;
	Push(ee, e, a);
}

void BinaryTree::Remove(int a) {
	Remove(nullptr, Root, a);
}

void BinaryTree::Remove(Element* e1, Element* e2, int a) {
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

			int k = p->Info;
			Remove(e1, e2, k);
			e2->Info = k;
		}
	}
}

void BinaryTree::Push(Element** ee, Element* e, int a) {
	if (e == nullptr) {
		*ee = new Element(a);
		return;
	}
	if (a > e->Info) Push(&e->right, e->right, a);
	if (a < e->Info) Push(&e->left, e->left, a);
}

void BinaryTree::LevObh(std::string& s) {
	LevObh(Root, s);
}

void BinaryTree::LevObh(Element* e, std::string& s) {
	if (e == nullptr) return;
	s += std::to_string(e->Info) + "\n";
	LevObh(e->left, s);
	LevObh(e->right, s);
}

void main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	BinaryTree t;
	bool b = true;
	int key = 0;
	while (fin) {
		int a;
		fin >> a;
		if (b) {
			fin.seekg(1, std::ios::cur);
			b = false;
			key = a;
			continue;
		}
		t.Push(a);
	}
	std::string s;
	t.Remove(key);
	t.LevObh(s);
	fout << s;
}
