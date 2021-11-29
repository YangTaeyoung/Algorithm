#include <iostream>
#include <vector>

using namespace std;

// 간선 정보를 담는 Edge
// 일반적인 Edge 클래스는 정점의 시작정보와 도착정보를 동시에 담으나,
// 이미 인접리스트에서 시작점 정보를 담고 있으므로, 도착점 정보만 담아도 됨.
class Edge {
private:
    // 도착 정점 번호
    int dst;
    // 가중치
    int weight;
public:
    // 생성자
    Edge(int dst, int weight) {
        this->dst = dst;
        this->weight = weight;
    }
    
    // get 함수, 알고리즘에서 따로 변경을 요구하지 않으므로, set함수는 따로 지정하지 않음.
    int getDst() {
        return dst;
    }
    int getWeight() {
        return weight;
    }

};

// pq를 구현할 힙
class Heap {
private:
    // Edge를 담는 벡터 선언
    vector<Edge*> heap;
public:
    Heap() {
        heap.push_back(nullptr); // 더미 인덱스 설정 inplace를 위함.
    }

    // 힙 안의 요소 두개를 바꾸는 함수 0이 더미 임으로 tmp로 사용
    void swap(int idx1, int idx2) {
        heap[0] = heap[idx1];
        heap[idx1] = heap[idx2];
        heap[idx2] = heap[0];
    }

    // 업힙 함수
    void upHeap() {
        int tmp = heap.size() - 1; // 들어간 요소의 인덱스.
        int parent = tmp / 2;
        while (parent != 0 && heap[parent]->getWeight() >= heap[tmp]->getWeight()) {
            // 가중치가 서로 같을 경우
            if (heap[parent]->getWeight() == heap[tmp]->getWeight()) {
                // 노드 번호가 더 작은 것이 부모에 가도록 설정함.
                if (heap[parent]->getDst() > heap[tmp]->getDst()) {
                    swap(parent, tmp);
                }
            }
            // 가중치가 서로 다른 경우
            else if (heap[parent]->getWeight() > heap[tmp]->getWeight()) {
                swap(parent, tmp);
            }
            tmp = parent;
            parent = tmp / 2;
        }
    }

    // 부모 자식간 바꿀 필요가 있는지 결정하는 함수
    // 최악의 경우 가중치 비교와 노드 번호 비교를 동시에 수행함으로 2번의 수행시간이 필요 W(n) = O(1)
    bool compareWithParent(int parent, int child) {
        if (heap[parent]->getWeight() == heap[child]->getWeight()) return heap[parent]->getDst() > heap[child]->getDst();
        else return heap[parent]->getWeight() > heap[child]->getWeight();
    }

    // 자식간 더 작은 자식을 고르는 함수.
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

    // 다운 힙 함수
    // 해당 함수는 자식을 비교해가며 내려감. 인덱스를 * 2 하거나 *2+1하면서 내려가므로 실제 힙 사이즈에 다가가기 위해 최악의 경우 W(n) = O(log N) time이 소요됨
    void downHeap(int idx) {
        int left = idx * 2;
        int right = idx * 2 + 1;
        int smaller;

        // left는 right에 비해 자식 인덱스가 더 작다. -> 해당 부분이 힙 사이즈보다 같거나 크다는 것은 탐색 인덱스가 힙의 범위를 벗어났음을 의미.(탐색 중지)
        if (left >= heap.size()) return;
        // left는 heap.size() - 1 인데 right의 경우 heap.size()인 경우, 즉 마지막 노드의 자식이 하나밖에 없는 경우 남은 자식을 smaller로 채택함.
        else if (right >= heap.size()) smaller = left;
        // 자식 둘 다 범위 내에 있는 경우 더 작은 노드를 smaller노드로 채택함.
        else smaller = selectSmallerChild(left, right);
        
        // 부모와 자식간의 비교
        if (compareWithParent(idx, smaller)) {
            swap(idx, smaller);
            downHeap(smaller);
        }
    }


    void push(Edge* edge) {
        heap.push_back(edge);
        upHeap();
    }

    // 가장 위에 있는 요소를 제거하는 함수 
    void pop() {
        if (empty()) {
            return;
        }
        else {
            // 1번 요소를 가장 뒤에 있는 요소로 설정
            heap[1] = heap.back();
            // 가장 뒤에 있는 요소를 제거
            heap.pop_back();

            // 가장 위에 있는 인덱스, 1번을 기준으로 다운힙 실행 (0번은 더미)
            int top = 1;
            downHeap(top);
        }
    }
    // 더미노드만 존재하거나, 힙이 빈 경우를 판단하는 함수
    bool empty() { 
        // 힙에 아예 없거나, 벡터의 사이즈가 1개인 경우 (즉 1번 인덱스만 존재하는 경우)
        return heap.empty() || heap.size() == 1;
    }

    // 힙의 가장 위에 있는 부분을 리턴함. 해당 힙은 0번인덱스가 더미임으로 1번 인덱스를 리턴하도록 설정.
    Edge* top() {
        if (empty()) return nullptr;
        return heap[1];
    }
};



vector<Edge*>* adjList; // 엣지가 들어갈 백터의 배열 즉 노드당 인접 리스트
bool* visited; // 노드당 방문 여부를 설정하는 것. 
int answer = 0; // 최소 가중치
vector<int> answer_path; // 답이 될 경로를 저장



// 프림 알고리즘 함수
void prim(int start) {
    Heap fringeSet; // fringe set 선언 (Heap 기반)
    for (auto& i : adjList[start]) { // 처음 시작하는 노드의 인접 리스트 접근
        int next = i->getDst();
        int distance = i->getWeight();

        fringeSet.push(new Edge(next, distance)); // fringe_set에 첫 노드의 인접 행렬을 담는다.
    }
    // 정답이 될 경로에 첫 노드 start를 넣음
    answer_path.push_back(start);
    // 첫 노드의 방문 여부를 true로 바꿈
    visited[start] = true;

    // pq가 빌 때까지 계속
    while (!fringeSet.empty()) {
        // top = weight가 가장 작으며 만약 가중치가 같더라도 같은 것들 중 dst가 최소인 노드
        int weight = fringeSet.top()->getWeight();
        int curNode = fringeSet.top()->getDst();
        fringeSet.pop();

        // 선택한 노드가 방문하지 않은 경우 인접 리스트를 호출하고 fringe set에 넣음.
        if (!visited[curNode]) {
            visited[curNode] = true; // 방문했다고 변경
            answer_path.push_back(curNode); // 정답 패스에 해당 노드 추가
            answer += weight;

            // cur노드의 인접 리스트를 fringe set에 추가하는 것.
            for (auto& i : adjList[curNode]) {
                int candidateWeight = i->getWeight();
                int next = i->getDst();
                if (!visited[next]) fringeSet.push(new Edge(next, candidateWeight)); // 만약 방문하지 않은 노드의 경우 해당 edge를 fringe set에 추가함.
            }
        }
    }
}

// 방문 여부를 초기화 하는 함수
void initVisited(bool* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = false;
    }
}

int main() {
    // 최대 정점 개수, 간선 개수, 명령 개수를 설정
    int VERTEX_MAX, EDGE_MAX, N;
    cin >> VERTEX_MAX >> EDGE_MAX >> N;
    // 각 노드 별 방문 여부를 배열로 담음 (0번 인덱스는 더미로 설정: 범위가 1부터 시작하기 때문에)
    visited = new bool[VERTEX_MAX + 1];
    
    // 모든 정점의 방문여부 초기화
    initVisited(visited, VERTEX_MAX + 1);
    // 모든 정점의 인접 리스트 생성
    adjList = new vector<Edge*>[VERTEX_MAX + 1];

    for (int i = 0; i < EDGE_MAX; i++) {
        int src, dst, weight;
        cin >> src >> dst >> weight;

        // 무향 그래프 초기화: 방향이 없으므로 양쪽의 방향에서 edge를 설정해 주어야 한다.
        adjList[src].push_back(new Edge(dst, weight));
        adjList[dst].push_back(new Edge(src, weight));
    }

    for (int i = 0; i < N; i++)
    {
        char flag;
        cin >> flag;
        if (flag == 'P') {

            // 시작 인덱스를 입력받음
            int start;
            cin >> start;
            
            // prim 알고리즘 시작.
            prim(start);

            // prim 함수를 통해 계산된 최소 가중치 값 출력
            cout << answer << " ";
            // prim 함수를 통해 계산된 경로를 순차적으로 출력
            for (auto& path : answer_path) {
                cout << path << " ";
            }
            cout << endl;

            // 방문 정보 초기화
            initVisited(visited, VERTEX_MAX + 1);
            answer = 0;
            answer_path.clear();
        }
    }


    return 0;
}
