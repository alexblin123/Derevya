#include <iostream>
#include <list>
#include <queue>
#include<ctime>
#include <vector>
#include<fstream>
#include <Windows.h>

using namespace std;


struct pos {

	int col; // столбец (х)
	int str; // строка (y)
};

template <class T>
class Tree {

private:


	Tree<T>* left;
	Tree<T>* right;
	Tree<T>* parent;

	T data;

	static Tree<T>* buildBalancedBst(const std::vector<T>& data, int start, int end) {

		if (start > end) { return nullptr; }

		int mid = start + (end - start) / 2;

		Tree<T>* newNode = new Tree<T>(data[mid]);

		newNode->left = buildBalancedBst(data, start, mid - 1);
		newNode->right = buildBalancedBst(data, mid + 1, end);

		return newNode;
	}

public:

	Tree(T); 

	Tree() { left = right = parent = nullptr; } 

	~Tree();

	T get_data();

	void replace(T); // заменяет значение текущего узла на введенное значение

	void delete_left(); // удаляет левое поддерево

	void delete_right();// удаляет правое поддерево

	void insert_left(T); // вставляет новый узел со значением T в левое поддерево

	void insert_right(T); // вставляет новый узел со значением T в правое поддерево

	void direct_way(Tree<T>*); // обходим дерево в прямом порядке

	void symmetric_way(Tree<T>*); // обходим дерево в симметричном порядке

	void reverse_way(Tree<T>*); // обходим дерево в обратном порядке

	void parse(Tree<T>*, list<T>&); // обходим дерево и записываем значения в переданный список

	void print_tree(int);

	void delete_tree() { delete this; }

	void insert(T); // вставка узла со значением T

	void erase(T); // удаление узла с указанным значением 

	void add_left(Tree<T>* temp) { left = temp; } // устанавливаем левое поддерево
	 
	void add_right(Tree<T>* temp) { right = temp; } // устанавливаем правое поддерево


	void print_vertical(int depth = 0) { // вертикальный вывод дерева
	
		if (right != nullptr) { right->print_vertical(depth + 1); }

		for (int i = 0; i < depth; ++i) { cout << "   "; }

		cout << data << endl;

		if (left != nullptr) { left->print_vertical(depth + 1); }

	} 
	void print_horizontal(int depth = 0, char branch = ' ') { // горизонтальный вывод дерева 

		if (right != nullptr) { right->print_horizontal(depth + 1, '/'); }

		for (int i = 0; i < depth; ++i) { cout << "   "; }

		cout << branch << "-" << data << endl;

		if (left != nullptr) { left->print_horizontal(depth + 1, '\\'); }
	}

	void printVTree(); // печать дерева вертикально

	void obhod(Tree<T>* node);

	Tree<T>* replaceNullForEmpty(); // добавляем недостающие узлы для полного дерева

	int getHight(); // получаем высоту дерева

	int getNodes(); // получаем кол-во узлов в дереве

	Tree<T>* replaceHelp(Tree<T>* node, int h); 

	int getPos(int index, int width, int curLevel, int maxLevel) {// считаем кол-во пробелов для узла
		
		int x1 = 0;
		int x2 = pow(2, curLevel) - 1;

		int y1 = width / pow(2, curLevel + 1);
		int y2 = width - pow(2, maxLevel - curLevel);

		double k = (y2 - y1) / (x2 - x1);
		double m = -x1 * k + y1;

		int y = (int)(k * index + m);

		return y;
	}

	void inOrderTraversal(vector<T>& result) { 

		if (left != nullptr) { left->inOrderTraveral(result); }

		result.push_back(data);

		if (right != nullptr) { right->inOrderTraveral(result); }
	}

	static Tree<T>* createBstFromBalancedTree(Tree<T>* root) {

		std::vector<T> soartedData;

		root->inOrderTraversal(soartedData);

		return buildBalancedBst(soartedData, 0, soartedData.size() - 1);
	}

	void levelScan(); // вывод 

	Tree<T>* eject_left(); // удаляем и возвращаем левое поддерево

	Tree<T>* eject_right(); // удаляем и возвращаем правое поддерево

	Tree<T>* get_left(); // получаем указатель на левое поддерево

	Tree<T>* get_right(); // получаем указатель на правое поддерево

	Tree<T>* get_parent(); // получаем указатель на родительский узел

	Tree<T>* copy(); // создаем копию текущего дерева

	Tree<T>* find(T); // находим узел с указанным значением 

	Tree<T>* search(T); // поиск по ключу

	Tree<T>* next(); // получаем указатель на следующий узел

	Tree<T>* prev(); // получаем указатель на предыдущий узел

	Tree<T>* find_min(); // ищем узел с min значением

	Tree<T>* find_max(); // ищем узел с max значением

	Tree<T>* balanced(int); // создаем сбалансированное дерево заданной высоты
};

template<class T>

Tree<T>::Tree(T data) {

	this->data = data;
	left = right = parent = nullptr;
}

template <class T>

Tree<T>::~Tree() {

	delete_left();
	delete_right();
}

template <class T>
T Tree<T>::get_data() { return data; }

template <class T>
Tree<T>* Tree<T>::get_left() { return left; }

template <class T>
Tree<T>* Tree<T>::get_right() { return right; }

template <class T>
Tree<T>* Tree<T>::get_parent() { return parent; }

template <class T>
Tree<T>* Tree<T>::next() {

	Tree<T>* current = this;

	if (current->right() != nullptr) { return current->right->find_min(); }

	Tree<T>* temp = current->parent;

	while (temp != nullptr && current == temp->right) {

		current = temp;
		temp = temp->parent;
	}

	return temp;
}

template <class T>
Tree <T>* Tree<T>::prev() {

	if (left != nullptr) {

		Tree<T>* temp = left;
		
		while (temp->right != nullptr) { temp = temp->right; }

		return temp;
	}

	else {

		Tree<T>* temp = this;

		while (temp->parent != nullptr && temp->parent->left == temp) { temp = temp->parent; }

		return temp->parent;
	}
}

template <class T>
void Tree<T>::insert(T data) {

	Tree<T>* current = this;

	while (current != nullptr) {

		if (data > current->data) {

			if (current->right != nullptr) {

				current = current->right;
			}

			else {

				current->insert_right(data);
				return;
			}
		}

		else if (data < current->data) {

			if (current->left != nullptr) {

				current = current->left;
			}

			else {

				current->insert_left(data);
				return;
			}
		}
		else return;
	}
}

template <class T>
void Tree<T>::insert_right(T data) {

	Tree<T>* newNode = new Tree(data);

	if (this->right != nullptr) {

		this->right->parent = newNode;

		newNode->right = this->right;
	}

	this->right = newNode;
	newNode->parent = this;
}

template <class T>
void Tree<T>::insert_left(T data) {

	left = new Tree(data);
	left->parent = this;
}

template <class T>
void Tree<T>::direct_way(Tree<T>* current) {

	if (current == nullptr) { return; }

	else {

		cout << current->get_data() << " ";

		direct_way(current->get_left());
		direct_way(current->get_right());
	}
}

template <class T>
void Tree<T>::symmetric_way(Tree<T>* tree) {

	if (tree != nullptr) {

		symmetric_way(tree->left);
		
		cout << tree->data << " ";

		symmetric_way(tree->right);
	}
}

template <class T>
void Tree<T>::reverse_way(Tree<T>* tree) {

	if (tree != nullptr) {

		reverse_way(tree->left);
		reverse_way(tree->right);

		cout << tree->data << " ";
	}
}

template <class T>
void Tree<T>::levelScan() {

	vector<Tree<T>*> vect;

	Tree<T>* p = this;

	vect.push_back(p);

	for (int i = 0; i < p->getNodes(); i++) {

		if (vect.at(i)->left != NULL) {
			vect.push_back(vect.at(i)->left);
		}

		if (vect.at(i)->right != NULL) {
			vect.push_back(vect.at(i)->right);
		}
	}

	for (int i = 0; i < vect.size(); i++) { cout << vect.at(i)->getData() << " "; }

	cout << endl;
}

template <class T>
int Tree<T>::getHight() {

	int h1 = 0, h2 = 0, hAdd = 0;

	if (this == NULL) return 0;
	if (this->left != NULL) { h1 = this->left->getHight(); }
	if (this->right != NULL) { h2 = this->right->getHight(); }
	if (h1 >= h2) { return h1 + 1; }
	else return h2 + 1;
}

template <class T>
int Tree<T>::getNodes() {

	if (this == NULL) return 0;
	if ((this->left == NULL) && (this->right == NULL)) return 1;

	int l = 0, r = 0;

	if (this->left != NULL) { l = this->left->getNodes(); }
	if (this->right != NULL) { r = this->right->getNodes(); }

	return (l + r + 1);
}

template <class T>
Tree<T>* Tree<T>::replaceHelp(Tree<T>* node, int h) {

	int curLevel = getLevel(node);

	if ((node->get_left() == NULL) && (curLevel != (h - 1))) { node->insert_left(NULL); }
	if ((node->get_right() == NULL) && (curLevel != (h - 1))) { node->insert_right(NULL); }

	if (node->get_left() != NULL) { node->add_left(replaceHelp(node->get_left(), h)); }
	if (node->get_right() != NULL) { node->add_right(replaceHelp(node->get_right(), h)); }

	return node;
}

template <class T>
Tree<T>* Tree<T>::replaceNullForEmpty() {

	Tree<T>* node = this->copy();

	int h = node->getHight();

	node = replaceHelp(node, h);

	return node;
}

template <class T>
void Tree<T>::obhod(Tree<T>* node) {

	ofstream f("print.txt");

	int amount = node->getNodes();

	queue<Tree<T>*> q;

	q.push(node);

	while (!q.empty()) {

		Tree<T>* temp = q.front();

		q.pop();

		f << temp->data << endl;

		if (temp->left)
			q.push(temp->left);

		if (temp->right)
			q.push(temp->right);
	}

	f.close();
}


template <class T>
void Tree<T>::printVTree() {

	obhod(this);

	ifstream f("print.txt");

	int amount = 0;

	while (!f.eof()) {

		char str[255];
		f.getline(str, 255);
		amount++;

	}

	f.close();

	amount--;
	
	ifstream f1("print.txt");

	int* mas = new int[amount];

	for (int i = 0; i < amount; i++) {

		char str[255];
		f1.getline(str, 255);
		mas[i] = atoi(str);

	}

	f1.close();

	int height = this->getHight();
	int count = 0;
	int* spaces = new int[height];

	spaces[0] = 0;

	for (int i = 1; i < height; i++) {

		spaces[i] = spaces[i - 1] * 2 + 1;
	}

	int amount_p = 0;

	if (height == 1) {
		cout << mas[0] << endl;
	}

	else {

		for (int i = 0, l = height - 1; i < height - 1; i++, l--) {
			for (int j = 0, k = 0; j < pow(2, i); j++, k++) {

				if (k == 0) 
					for (int h = 0; h < spaces[l]; h++) 
						cout << " ";
					
				else {
					for (int h = 0; h < spaces[l + 1]; h++) 
						cout << " ";
				}
				cout << mas[count++];
				amount_p++;
			}
			cout << endl;
		}

		int* last_str = new int[pow(2, height - 1)];

		for (int i = 0; i < pow(2, height - 1); i++)
			last_str[i] = 200000000;

		int sch1 = 0;

		int sch2 = spaces[height - 2] + 1;

		for (int i = amount_p; i < amount; i += 2) {

			if (i <= amount - 1) {

				last_str[sch1] = mas[i];
				sch1 += 2;
			}

			if (i + 1 <= amount - 1) {

				last_str[sch2] = mas[i + 1];
				sch2 += 2;
			}

			if (sch1 >= pow(2, height - 1) || sch2 >= pow(2, height - 1)) {

				sch1 = 1;
				sch2 = spaces[height - 2] + 2;
			}
		}
		for (int i = 0; i < pow(2, height - 1); i++)
			if (last_str[i] != 200000000)
				last_str[i] = mas[amount_p++];

		for (int i = 0; i < pow(2, height - 1); i++)
			if (last_str[i] != 200000000)
				cout << last_str[i] << " ";
			else cout << " ";

		delete[] last_str;
		cout << endl;
	}

	delete[] mas;
	delete[] spaces;

}

template <class T>
void Tree<T>::print_tree(int level) {

	if (this != NULL) {

		this->left->print_tree(level + 1);

		for (int i = 1; i < level; i++) { cout << " "; }

		cout << this->get_data() << endl;

		this->right->print_tree(level + 1);
	}
}

template <class T>
void Tree<T>::parse(Tree<T>* current, list<T>& lst) {

	if (current == nullptr) { return; }

	else {

		lst.push_back(current->get_data());

		parse(current->get_left(), lst);
		parse(current->get_right(), lst);
	}
}

template <class T>
Tree<T>* Tree<T>::balanced(int count) {

	if (count <= 0) { return nullptr; }

	T data;

	cout << "Введите данные для сбалансированного дерева: "; cin >> data;

	Tree<T>* temp = new Tree<T>(data);

	temp->add_left(balanced(count / 2));
	temp->add_right(balanced(count - count / 2 - 1));

	return temp;
}

template <class T>
void Tree<T>::erase(T data) {

	Tree<T>* toErase = this->find(data);
	Tree<T>* teParent = toErase->parent;

	if (toErase->left == nullptr && toErase->right == nullptr) {

		if (teParent->left == toErase) {

			teParent->left == nullptr;
			delete toErase;
		}

		else {

			teParent->right = nullptr;
			delete toErase;
		}
	}
	else if ((toErase->left != nullptr && toErase->right == nullptr) || ((toErase->left == nullptr && toErase->right != nullptr))) {

		if (toErase->left == nullptr) {

			if (toErase == teParent->left) { teParent->left == toErase->right; }
			else { teParent->right == toErase->right; }

			toErase->right->parent = teParent;

		}

		else {

			if (teParent->left == toErase) { teParent->left = toErase->left; }
			else { teParent->right = toErase->left; }

			toErase->left->parent = teParent;
		}
	}

	else {

		Tree<T>* next = toErase->next();

		toErase->data = next->data;

		if (next == next->parent->left) {

			next->parent->left = next->right;

			if (next->right != nullptr) {

				next->right->parent = next->parent;
			}
		}

		else {

			next->parent->right = next->right;

			if (next->right != nullptr) {
				
				next->right->parent = next->parent;
			}
		}
		delete next;
	}
}

template <class T>
void Tree<T>::delete_left() {

	if (left != NULL) {

		left->delete_left();
		left->delete_right();

		delete left;
	}
}

template <class T>
void Tree<T>::delete_right() {

	if (right != NULL) {

		right->delete_left();
		right->delete_right();

		delete right;
	}
}

template <class T>
Tree<T>* Tree<T>::eject_left() {

	Tree<T>* temp = left;

	left = nullptr;

	if (temp != nullptr) { temp->parent = nullptr; }

	return temp;
}

template <class T>
Tree<T>* Tree<T>::eject_right() {

	Tree<T>* temp = right;

	right = nullptr;

	if (temp != nullptr) { temp->parent = nullptr; }

	return temp;
}

template <class T>
Tree<T>* Tree<T>::search(T key) {

	if (data == key) { return this; }

	if (left != nullptr) {

		Tree<T>* result = left->search(key);

		if (result != nullptr) { return result; }
	}

	if (right != nullptr) {

		Tree<T>* result = right->search(key);

		if (result != nullptr) { return result; }
	}

	return nullptr;
}

template <class T>
Tree<T>* Tree<T>::find(T data) {

	if (this == nullptr || this->data == data) { return this; }

	else if (data > this->data) { return this->right->find(data); }
	
	else { return this->left->find(data); }
}

template <class T>
Tree<T>* Tree<T>::find_max() {

	if (this->right == nullptr) { return this; }

	return this->right->find_max();
}

template <class T>
Tree<T>* Tree<T>::find_min() {

	Tree<T>* minNode = this;

	while (minNode->left != nullptr) { minNode = minNode->left; }

	return minNode;
}

template <class T>
void Tree<T>::replace(T data) {

	Tree<T>* searchTree = new Tree<T>();

	list<T> listOne;

	parse(this, listOne);

	for (auto data : listOne) { searchTree->insert(data); }

	Tree<T>* current = searchTree->find(data);
	
	if (current == nullptr) return;

	cout << "Затем:\n";

	if (current->left == nullptr && current->right == nullptr) {

		current->data = "L";
		searchTree->print_tree(2);

		return;
	}
}

template <class T>
Tree<T>* Tree<T>::copy() {

	Tree<T>* newTree = new Tree<T>(data);

	if (left != nullptr) {

		newTree->left = left->copy();
		newTree->left->parent = newTree;
	}

	if (right != nullptr) {

		newTree->right = right->copy();
		newTree->right->parent = newTree;

	}

	return newTree;
}

int main() {

	system("chcp 1251 > Null");
	srand(time(0));

	Tree<int>* root1 = new Tree<int>(1);

	root1->insert_left(2);
	root1->insert_right(3);

	root1->get_left()->insert_left(4);
	root1->get_left()->insert_right(5);

	root1->get_right()->insert_left(6);
	root1->get_right()->insert_right(7);

	cout << "Пример вывода дерева\n\n";
	root1->print_vertical();

	cout << "\nЕще один вывод дерева\n\n";
	root1->print_horizontal(0, '-');

	cout << endl;

	Tree<string>* tree = new Tree<string>("корень");

	tree->insert_left("левый потомок");
	tree->insert_right("правый потомок");

	tree->get_left()->insert_left("левый потомок левого потомка");
	tree->get_left()->insert_right("правый потомок левого потомка");

	tree->get_right()->insert_right("правый потомок правого потомка");

	cout << "\nБинарное дерево типа строки\n\n";
	
	tree->print_horizontal(2, '-');

	int n;

	cout << "\nВведите кол-во элементов для сбалансированного дерева: "; cin >> n;

	Tree<string>* balancedTree = tree->balanced(n);
	cout << endl << endl;

	balancedTree->get_left()->replace("найден");

	balancedTree->print_horizontal(1, '-');

	cout << "\n\nВертикальный вывод дерева\n\n";

	Tree<int>* root = new Tree<int>(10);

	root->insert_left(1);
	root->insert_right(2);

	root->get_left()->insert_left(3);
	root->get_left()->insert_right(4);

	root->get_right()->insert_left(5);
	root->get_right()->insert_right(6);

	root->get_left()->get_left()->insert_left(9);
	root->get_left()->get_left()->insert_right(10);

	root->get_left()->get_right()->insert_left(11);
	root->get_left()->get_right()->insert_right(12);

	root->get_right()->get_left()->insert_left(13);
	root->get_right()->get_left()->insert_right(14);

	root->printVTree();


}
				
