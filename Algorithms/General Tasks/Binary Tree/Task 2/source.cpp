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
	while (fin) {
		int a;
		fin >> a;
		t.Push(a);
	}
	std::string s;
	t.LevObh(s);
	fout << s;
}
