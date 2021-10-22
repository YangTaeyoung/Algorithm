#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 부모노드를 찾는 함수
int getParent(int parent[], int x) {
    if (parent[x] == x) return x;
    return parent[x] = getParent(parent, parent[x]);
}

// 두 부모 노드를 합치는 함수
void unionParent(int parent[], int a, int b) {
    a = getParent(parent, a);
    b = getParent(parent, b);
    // 부모를 합칠 때는 두 부모중 더 작은 값을 입력한다.
    if (a < b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

// 같은 부모를 가지는 지 확인 (같은 그래프에 속해 있는지 확인
bool findParent(int parent[], int a, int b) {
    a = getParent(parent, a);
    b = getParent(parent, b);
    if (a == b) return true;
    else return false;
}

class Edge {
public:
    int node[2];
    int distance;

    Edge(int a, int b, int distance) {
        this->node[0] = a;
        this->node[1] = b;
        this->distance = distance;
    }

    bool operator<(Edge edge) const {
        return distance < edge.distance;
    }


};


int main() {
    int n = 7;
    vector<Edge> v;
    v.push_back(Edge(1, 7, 12));
    v.push_back(Edge(1, 4, 28));
    v.push_back(Edge(1, 2, 67));
    v.push_back(Edge(1, 5, 17));
    v.push_back(Edge(2, 4, 24));
    v.push_back(Edge(2, 5, 62));
    v.push_back(Edge(3, 5, 20));
    v.push_back(Edge(3, 6, 37));
    v.push_back(Edge(4, 7, 13));
    v.push_back(Edge(5, 6, 45));
    v.push_back(Edge(5, 7, 73));

    sort(v.begin(), v.end());

    // 각 정점이 포함된 그래프가 어디인지 저장
    int parent[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < v.size(); i++) {
        // 추가적으로 있을 경우 노드가 다 연결된 상태에서 추가적인 연산을 하지 않고 끝낼 수 있음.
        if (cnt == n-1){
            break;
        }
        // 두 노드의 부모 노드가 갖지 않은지 보는 것.같지 않으면 사이클이 형성되지 않는다.
        if (!findParent(parent, v[i].node[0] - 1, v[i].node[1] - 1)) {
            sum += v[i].distance;
            unionParent(parent, v[i].node[0] - 1, v[i].node[1] - 1);
            cnt++;
        }
    }
    printf("%d\n", sum);
    return 0;
}
