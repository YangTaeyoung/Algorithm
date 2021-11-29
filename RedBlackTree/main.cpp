#include <iostream>
#include <string>
#define BLACK true
#define RED false
using namespace std;

class Node {
private:
	int id;
	string name;
	int size;
	int price;
	bool color; 
	Node* parent;
	Node* lChild;
	Node* rChild;
public:
	Node(int id, string name, int size, int price) {
		this->id = id;
		this->name = name;
		this->size = size;
		this->price = price;
		this->color = RED;
		this->parent = nullptr;
		this->lChild = nullptr;
		this->rChild = nullptr; 
	}

	void setSale(int P) {
		double per = ((100.0 - P)/ 100.0);
		this->price *= per;
	}

	void updateNode(string name, int size, int price) {
		this->name = name;
		this->size = size;
		this->price = price;
	}
	void setLChild(Node* node) { this->lChild = node; }
	void setRChild(Node* node) { this->rChild = node; }
	void setParent(Node* node) { this->parent = node; }
	void setColor(bool color) { this->color = color; }
	void setPrice(int price) { this->price = price; }
	void setName(string name) { this->name = name; }
	void setSize(int size) { this->size = size; }
	Node* getParent() { return this->parent; }
	Node* getLChild() { return this->lChild; }
	Node* getRChild() { return this->rChild; }
	int getId() { return this->id;}
	bool getColor() { return this->color; }
	string getName() { return this->name; }
	int getSize() { return this->size; }
	int getPrice() { return this->price; }

	// ������ �ڽ����� ��ȯ
	bool isLChild() { return this->parent->lChild == this; }
	bool isRChild() { return this->parent->rChild == this; }
	
};

class RedBlackTree {
private:
	Node* root;
public:
	
	RedBlackTree() {
		this->root = nullptr;
	}
	
	Node* getRoot() {
		return this->root;
	}

	bool isEmpty() {
		return this->root == nullptr;
	}

	bool isRoot(Node* node) {
		return node->getParent() == nullptr;
	}
	
	bool isLeaf(Node* node) {
		return node == nullptr;
	}
	
	Node* find(int id) {
		if (isEmpty()) {
			return nullptr;
		}
		Node* curNode = root;
		while (true) {
			if (isLeaf(curNode)) {
				return nullptr;
			}
			if (curNode->getId() == id) {
				return curNode;
			}
			else if (curNode->getId() > id) {
				curNode = curNode->getLChild();
			}
			else {
				curNode = curNode->getRChild();
			}
		}
		
	}

	void insertNode(Node* newNode) {
		
		// Ʈ���� ����ִ��� üũ
		if (isEmpty()) {
			this->root = newNode;
			this->root->setColor(BLACK); // ��Ʈ�� ��� ������ ����������.
			cout << 0 << endl; // ��Ʈ�� ����.
			return;
		}

		// �̹� ������ ��尡 Ʈ�� �ȿ� �ִ��� üũ
		Node* existNode = find(newNode->getId());
		if (existNode != nullptr)
		{
			// �̹� �ִ� ���� ���̸� ����ϰ� ����
			cout << getDepth(existNode) << endl;
			return;
		}

		// ## ���� �����ϴ� ��� ## //

		// ��ȸ�� ���
		Node* curNode = root;
		Node* parentNode = root;

		// ���ο� ����� ��ġ�� ã�� ����
		while (true) {
			
			if (isLeaf(curNode)) {
				newNode->setParent(parentNode);
				break;
			}

			if (curNode->getId() > newNode->getId()) {
				parentNode = curNode;
				curNode = curNode->getLChild();
			}
			else {
				parentNode = curNode;
				curNode = curNode->getRChild();
			}	
		}

		if (parentNode->getId() > newNode->getId()) {
			parentNode->setLChild(newNode);
		}
		else {
			parentNode->setRChild(newNode);
		}
	
		// �籸��ȭ, ���÷��� �� �ǽ�
		restructOrRecoloring(newNode);

		// ���� ������ ��� ���� ���
		cout << getDepth(newNode) << endl;
	}


	bool isDoubleRed(Node* node) {
		if (node == nullptr || node->getParent() == nullptr) return false;
		return node->getColor() == RED && node->getParent()->getColor() == RED;
	}

	Node* getUncle(Node* node) {
		if (node->getParent()->isLChild()) return node->getParent()->getParent()->getRChild();
		else return node->getParent()->getParent()->getLChild();
	}
	
	void restructOrRecoloring(Node* node) {
		Node* curNode = node;
		// ���θ� ��尡 �����鼭 �����尡 �߻����� ���
		// ���θ� ��尡 ���� ��� -> ��Ʈ�� ��� -> ��Ʈ�� ������ �����̹Ƿ� ������ �߻� �Ұ�. 
		while (isDoubleRed(curNode)) {
			Node* uncle = getUncle(curNode);
			// uncle�� ��
			if (isLeaf(uncle) || uncle->getColor() == BLACK) {
				restructuring(curNode);
				break;
			}
			// uncle�� ����
			else {
				recoloring(curNode);
				curNode = curNode->getParent()->getParent();
			}
		}
	}
	
	void restructuring(Node* node) {
		Node* subGrandParent = node->getParent()->getParent()->getParent();
		Node* subRoot;
		Node* subLChild;
		Node* subRChild;

		if (node->getParent()->isLChild())
		{

			// left & left case
			if (node->isLChild()) {
				// ����Ʈ�� ����
				subRoot = node->getParent();
				subLChild = node;
				subRChild = node->getParent()->getParent();

				// ����Ʈ�� ����
				if (!isLeaf(subRoot->getRChild())) subRoot->getRChild()->setParent(subRChild);
				subRChild->setLChild(subRoot->getRChild());
				subRoot->setRChild(subRChild);
				subRChild->setParent(subRoot);

			}
			// left & right case
			else {
				// ����Ʈ�� ����
				subRoot = node;
				subLChild = node->getParent();
				subRChild = node->getParent()->getParent();
				
				// ����Ʈ�� ����
				
				if(!isLeaf(subRoot->getLChild())) subRoot->getLChild()->setParent(subLChild);
				if(!isLeaf(subRoot->getRChild())) subRoot->getRChild()->setParent(subRChild);
				subLChild->setRChild(subRoot->getLChild());
				subRChild->setLChild(subRoot->getRChild());

				subRoot->setLChild(subLChild);
				subLChild->setParent(subRoot);
				subRoot->setRChild(subRChild);
				subRChild->setParent(subRoot);
			}
		}

		else {
			// right & left case
			if (node->isLChild()) {
				// ����Ʈ�� ����
				subRoot = node;
				subLChild = node->getParent()->getParent();
				subRChild = node->getParent();
				
				// ����Ʈ�� ����
				if(!isLeaf(subRoot->getLChild())) subRoot->getLChild()->setParent(subLChild);
				if(!isLeaf(subRoot->getRChild())) subRoot->getRChild()->setParent(subRChild);
				subLChild->setRChild(subRoot->getLChild());
				subRChild->setLChild(subRoot->getRChild());
				
				subRoot->setLChild(subLChild);
				subLChild->setParent(subRoot);
				subRoot->setRChild(subRChild);
				subRChild->setParent(subRoot);
			}

			// right & right case
			else {
				subRoot = node->getParent();
				subLChild = node->getParent()->getParent();
				subRChild = node;
				
				if(!isLeaf(subRoot->getLChild()))subRoot->getLChild()->setParent(subLChild);
				subLChild->setRChild(subRoot->getLChild());
				subLChild->setParent(subRoot);
				subRoot->setLChild(subLChild);
			}
		}

		if (subGrandParent == nullptr) {
			root = subRoot;
			root->setParent(nullptr);
		}
		else {
			if (subGrandParent->getId() < subRoot->getId()) {
				subGrandParent->setRChild(subRoot);
				subRoot->setParent(subGrandParent);
			}
			else {
				subGrandParent->setLChild(subRoot);
				subRoot->setParent(subGrandParent);
			}
		}
		// ������ Ʈ�� ���� ����.
		subRoot->setColor(BLACK);
		subLChild->setColor(RED);
		subRChild->setColor(RED);
	}

	void recoloring(Node* node) {
		Node* grandParent = node->getParent()->getParent();
		// ���θ� ��尡 ������ ���
		if (isRoot(grandParent)) grandParent->setColor(BLACK);
		// �ƴѰ�� �������� �ٲ�
		else grandParent->setColor(RED);
		
		// �� �� �θ� ���� ���� ���� �������� �ٲ�
		node->getParent()->setColor(BLACK);
		getUncle(node)->setColor(BLACK);
	}

	// Ư�� ����� ���̸� ���ϴ� �Լ�.
	int getDepth(Node* node) { 
		int depth = 0; 
		while (node->getParent() != nullptr) {
			node = node->getParent();
			depth++;
		}
		return depth;
	}
	
	void inOrderTraversal(Node* node, int x, int y, int P) {
		// Ʈ���� ����ְų�, ��尡 ������� �� ��� ���� ����.
		if (isEmpty() || isLeaf(node)) return;
		
		inOrderTraversal(node->getLChild(), x, y, P);
		if (node->getId() >= x && y >= node->getId()) {
			node->setSale(P);
		}
		inOrderTraversal(node->getRChild(), x, y, P);
		
	}
	
	void update(int id, string name, int size, int price) {
		Node* existNode = find(id);
		if (existNode == nullptr) {
			cout << "NULL" << endl;
			return;
		}
		existNode->updateNode(name, size, price);
		cout << getDepth(existNode) << endl;
	}

	void search(int id) {
		Node* existNode = find(id);
		if (existNode == nullptr) {
			cout << "NULL" << endl;
			return;
		}
		cout << getDepth(existNode) << ' ' << existNode->getName() << ' ' << existNode->getSize() << ' ' << existNode->getPrice() << endl;
	}
};

int main() {
	int N;
	cin >> N;
	RedBlackTree rbt;
	for (int i = 0; i < N; i++) {
		char oper;
		cin >> oper;

		switch (oper) {
		case 'I':
		{
			int id, size, price;
			string name;
			cin >> id >> name >> size >> price;
			rbt.insertNode(new Node(id, name, size, price));
			break; 
		}
		case 'F':
		{
			int id;
			cin >> id;
			rbt.search(id);
			break;
		}
		case 'R':
		{
			int id, size, price;
			string name;
			cin >> id >> name >> size >> price;
			rbt.update(id, name, size, price);
			break;
		}
		case 'D':
		{
			int x, y, P;
			cin >> x >> y >> P;
			rbt.inOrderTraversal(rbt.getRoot(), x, y, P);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}