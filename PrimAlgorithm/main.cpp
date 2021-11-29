#include <iostream>
#include <vector>

using namespace std;

// ���� ������ ��� Edge
// �Ϲ����� Edge Ŭ������ ������ ���������� ���������� ���ÿ� ������,
// �̹� ��������Ʈ���� ������ ������ ��� �����Ƿ�, ������ ������ ��Ƶ� ��.
class Edge {
private:
    // ���� ���� ��ȣ
    int dst;
    // ����ġ
    int weight;
public:
    // ������
    Edge(int dst, int weight) {
        this->dst = dst;
        this->weight = weight;
    }
    
    // get �Լ�, �˰��򿡼� ���� ������ �䱸���� �����Ƿ�, set�Լ��� ���� �������� ����.
    int getDst() {
        return dst;
    }
    int getWeight() {
        return weight;
    }

};

// pq�� ������ ��
class Heap {
private:
    // Edge�� ��� ���� ����
    vector<Edge*> heap;
public:
    Heap() {
        heap.push_back(nullptr); // ���� �ε��� ���� inplace�� ����.
    }

    // �� ���� ��� �ΰ��� �ٲٴ� �Լ� 0�� ���� ������ tmp�� ���
    void swap(int idx1, int idx2) {
        heap[0] = heap[idx1];
        heap[idx1] = heap[idx2];
        heap[idx2] = heap[0];
    }

    // ���� �Լ�
    void upHeap() {
        int tmp = heap.size() - 1; // �� ����� �ε���.
        int parent = tmp / 2;
        while (parent != 0 && heap[parent]->getWeight() >= heap[tmp]->getWeight()) {
            // ����ġ�� ���� ���� ���
            if (heap[parent]->getWeight() == heap[tmp]->getWeight()) {
                // ��� ��ȣ�� �� ���� ���� �θ� ������ ������.
                if (heap[parent]->getDst() > heap[tmp]->getDst()) {
                    swap(parent, tmp);
                }
            }
            // ����ġ�� ���� �ٸ� ���
            else if (heap[parent]->getWeight() > heap[tmp]->getWeight()) {
                swap(parent, tmp);
            }
            tmp = parent;
            parent = tmp / 2;
        }
    }

    // �θ� �ڽİ� �ٲ� �ʿ䰡 �ִ��� �����ϴ� �Լ�
    // �־��� ��� ����ġ �񱳿� ��� ��ȣ �񱳸� ���ÿ� ���������� 2���� ����ð��� �ʿ� W(n) = O(1)
    bool compareWithParent(int parent, int child) {
        if (heap[parent]->getWeight() == heap[child]->getWeight()) return heap[parent]->getDst() > heap[child]->getDst();
        else return heap[parent]->getWeight() > heap[child]->getWeight();
    }

    // �ڽİ� �� ���� �ڽ��� ���� �Լ�.
    int selectSmallerChild(int lChild, int rChild) {
        if (heap[lChild]->getWeight() == heap[rChild]->getWeight())
        {
            if (heap[lChild]->getDst() < heap[rChild]->getDst()) return lChild;
            else return rChild;
        }
        else {
            if (heap[lChild]->getWeight() < heap[rChild]->getWeight()) {
                return lChild;
            }
            else return rChild;
        }
    }

    // �ٿ� �� �Լ�
    // �ش� �Լ��� �ڽ��� ���ذ��� ������. �ε����� * 2 �ϰų� *2+1�ϸ鼭 �������Ƿ� ���� �� ����� �ٰ����� ���� �־��� ��� W(n) = O(log N) time�� �ҿ��
    void downHeap(int idx) {
        int left = idx * 2;
        int right = idx * 2 + 1;
        int smaller;

        // left�� right�� ���� �ڽ� �ε����� �� �۴�. -> �ش� �κ��� �� ������� ���ų� ũ�ٴ� ���� Ž�� �ε����� ���� ������ ������� �ǹ�.(Ž�� ����)
        if (left >= heap.size()) return;
        // left�� heap.size() - 1 �ε� right�� ��� heap.size()�� ���, �� ������ ����� �ڽ��� �ϳ��ۿ� ���� ��� ���� �ڽ��� smaller�� ä����.
        else if (right >= heap.size()) smaller = left;
        // �ڽ� �� �� ���� ���� �ִ� ��� �� ���� ��带 smaller���� ä����.
        else smaller = selectSmallerChild(left, right);
        
        // �θ�� �ڽİ��� ��
        if (compareWithParent(idx, smaller)) {
            swap(idx, smaller);
            downHeap(smaller);
        }
    }


    void push(Edge* edge) {
        heap.push_back(edge);
        upHeap();
    }

    // ���� ���� �ִ� ��Ҹ� �����ϴ� �Լ� 
    void pop() {
        if (empty()) {
            return;
        }
        else {
            // 1�� ��Ҹ� ���� �ڿ� �ִ� ��ҷ� ����
            heap[1] = heap.back();
            // ���� �ڿ� �ִ� ��Ҹ� ����
            heap.pop_back();

            // ���� ���� �ִ� �ε���, 1���� �������� �ٿ��� ���� (0���� ����)
            int top = 1;
            downHeap(top);
        }
    }
    // ���̳�常 �����ϰų�, ���� �� ��츦 �Ǵ��ϴ� �Լ�
    bool empty() { 
        // ���� �ƿ� ���ų�, ������ ����� 1���� ��� (�� 1�� �ε����� �����ϴ� ���)
        return heap.empty() || heap.size() == 1;
    }

    // ���� ���� ���� �ִ� �κ��� ������. �ش� ���� 0���ε����� ���������� 1�� �ε����� �����ϵ��� ����.
    Edge* top() {
        if (empty()) return nullptr;
        return heap[1];
    }
};



vector<Edge*>* adjList; // ������ �� ������ �迭 �� ���� ���� ����Ʈ
bool* visited; // ���� �湮 ���θ� �����ϴ� ��. 
int answer = 0; // �ּ� ����ġ
vector<int> answer_path; // ���� �� ��θ� ����



// ���� �˰��� �Լ�
void prim(int start) {
    Heap fringeSet; // fringe set ���� (Heap ���)
    for (auto& i : adjList[start]) { // ó�� �����ϴ� ����� ���� ����Ʈ ����
        int next = i->getDst();
        int distance = i->getWeight();

        fringeSet.push(new Edge(next, distance)); // fringe_set�� ù ����� ���� ����� ��´�.
    }
    // ������ �� ��ο� ù ��� start�� ����
    answer_path.push_back(start);
    // ù ����� �湮 ���θ� true�� �ٲ�
    visited[start] = true;

    // pq�� �� ������ ���
    while (!fringeSet.empty()) {
        // top = weight�� ���� ������ ���� ����ġ�� ������ ���� �͵� �� dst�� �ּ��� ���
        int weight = fringeSet.top()->getWeight();
        int curNode = fringeSet.top()->getDst();
        fringeSet.pop();

        // ������ ��尡 �湮���� ���� ��� ���� ����Ʈ�� ȣ���ϰ� fringe set�� ����.
        if (!visited[curNode]) {
            visited[curNode] = true; // �湮�ߴٰ� ����
            answer_path.push_back(curNode); // ���� �н��� �ش� ��� �߰�
            answer += weight;

            // cur����� ���� ����Ʈ�� fringe set�� �߰��ϴ� ��.
            for (auto& i : adjList[curNode]) {
                int candidateWeight = i->getWeight();
                int next = i->getDst();
                if (!visited[next]) fringeSet.push(new Edge(next, candidateWeight)); // ���� �湮���� ���� ����� ��� �ش� edge�� fringe set�� �߰���.
            }
        }
    }
}

// �湮 ���θ� �ʱ�ȭ �ϴ� �Լ�
void initVisited(bool* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = false;
    }
}

int main() {
    // �ִ� ���� ����, ���� ����, ��� ������ ����
    int VERTEX_MAX, EDGE_MAX, N;
    cin >> VERTEX_MAX >> EDGE_MAX >> N;
    // �� ��� �� �湮 ���θ� �迭�� ���� (0�� �ε����� ���̷� ����: ������ 1���� �����ϱ� ������)
    visited = new bool[VERTEX_MAX + 1];
    
    // ��� ������ �湮���� �ʱ�ȭ
    initVisited(visited, VERTEX_MAX + 1);
    // ��� ������ ���� ����Ʈ ����
    adjList = new vector<Edge*>[VERTEX_MAX + 1];

    for (int i = 0; i < EDGE_MAX; i++) {
        int src, dst, weight;
        cin >> src >> dst >> weight;

        // ���� �׷��� �ʱ�ȭ: ������ �����Ƿ� ������ ���⿡�� edge�� ������ �־�� �Ѵ�.
        adjList[src].push_back(new Edge(dst, weight));
        adjList[dst].push_back(new Edge(src, weight));
    }

    for (int i = 0; i < N; i++)
    {
        char flag;
        cin >> flag;
        if (flag == 'P') {

            // ���� �ε����� �Է¹���
            int start;
            cin >> start;
            
            // prim �˰��� ����.
            prim(start);

            // prim �Լ��� ���� ���� �ּ� ����ġ �� ���
            cout << answer << " ";
            // prim �Լ��� ���� ���� ��θ� ���������� ���
            for (auto& path : answer_path) {
                cout << path << " ";
            }
            cout << endl;

            // �湮 ���� �ʱ�ȭ
            initVisited(visited, VERTEX_MAX + 1);
            answer = 0;
            answer_path.clear();
        }
    }


    return 0;
}
