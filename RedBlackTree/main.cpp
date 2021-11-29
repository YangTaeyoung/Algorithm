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

	// 무슨쪽 자식인지 반환
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
		
		// 트리가 비어있는지 체크
		if (isEmpty()) {
			this->root = newNode;
			this->root->setColor(BLACK); // 루트의 경우 색상은 검정색으로.
			cout << 0 << endl; // 루트의 깊이.
			return;
		}

		// 이미 삽일할 노드가 트리 안에 있는지 체크
		Node* existNode = find(newNode->getId());
		if (existNode != nullptr)
		{
			// 이미 있는 경우는 깊이만 출력하고 종료
			cout << getDepth(existNode) << endl;
			return;
		}

		// ## 새로 삽입하는 경우 ## //

		// 순회할 노드
		Node* curNode = root;
		Node* parentNode = root;

		// 새로운 노드의 위치를 찾고 삽입
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
	
		// 재구조화, 리컬러링 중 실시
		restructOrRecoloring(newNode);

		// 새로 삽입한 노드 깊이 출력
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
		// 조부모 노드가 있으면서 더블레드가 발생했을 경우
		// 조부모 노드가 없는 경우 -> 루트인 경우 -> 루트는 무조건 검정이므로 더블레드 발생 불가. 
		while (isDoubleRed(curNode)) {
			Node* uncle = getUncle(curNode);
			// uncle이 블랙
			if (isLeaf(uncle) || uncle->getColor() == BLACK) {
				restructuring(curNode);
				break;
			}
			// uncle이 레드
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
				// 서브트리 지정
				subRoot = node->getParent();
				subLChild = node;
				subRChild = node->getParent()->getParent();

				// 서브트리 조정
				if (!isLeaf(subRoot->getRChild())) subRoot->getRChild()->setParent(subRChild);
				subRChild->setLChild(subRoot->getRChild());
				subRoot->setRChild(subRChild);
				subRChild->setParent(subRoot);

			}
			// left & right case
			else {
				// 서브트리 지정
				subRoot = node;
				subLChild = node->getParent();
				subRChild = node->getParent()->getParent();
				
				// 서브트리 조정
				
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
				// 서브트리 지정
				subRoot = node;
				subLChild = node->getParent()->getParent();
				subRChild = node->getParent();
				
				// 서브트리 조정
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
		// 조정된 트리 색상 지정.
		subRoot->setColor(BLACK);
		subLChild->setColor(RED);
		subRChild->setColor(RED);
	}

	void recoloring(Node* node) {
		Node* grandParent = node->getParent()->getParent();
		// 조부모 노드가 루투인 경우
		if (isRoot(grandParent)) grandParent->setColor(BLACK);
		// 아닌경우 빨강으로 바꿈
		else grandParent->setColor(RED);
		
		// 그 외 부모 노드와 삼촌 노드는 검정으로 바꿈
		node->getParent()->setColor(BLACK);
		getUncle(node)->setColor(BLACK);
	}

	// 특정 노드의 깊이를 구하는 함수.
	int getDepth(Node* node) { 
		int depth = 0; 
		while (node->getParent() != nullptr) {
			node = node->getParent();
			depth++;
		}
		return depth;
	}
	
	void inOrderTraversal(Node* node, int x, int y, int P) {
		// 트리가 비어있거나, 노드가 리프노드 일 경우 하지 않음.
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