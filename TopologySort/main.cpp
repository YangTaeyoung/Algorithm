#include <iostream>
#include <vector>
#include <queue>
#define MAX 10
using namespace std;

// 위상 정렬
// 순서가 정해져 있는 작업을 차례로 수행해야 할 때 그 순서를 결정해주기 위해 사용하는 알고리즘.
// 여러개의 답이 함께 존재할 수 있음.
// 사이클이 발생하지 않는 유향그래프 (DAG: Directed Acyclic Graph)에서만 적용이 가능하다
// 스텍이나 큐를 이용한 알고리즘을 이용해 풀며, 일반적으로 큐를 사용한다.

int n, inDegree[MAX]; // 노드의 수, 진입 차수
vector<int> a[MAX]; // 간선 정보

void topologySort(){
    // 위상정렬을 수행한 결과값이 담길 배열
    int result[MAX];
    queue<int> q;

    // 집입 차수가 0인 노드를 큐에 삽입
    for(int i = 1; i <= n; i++){
        if(inDegree[i] == 0) q.push(i);
    }

    // 위상정렬이 완전히 수행되려면 정확히 N개의 노드를 방문합니다.
    for(int i = 1; i <= n; i++){
        if(q.empty()){
            cout << "사이클이 발생하였습니다." << endl;
            return;
        }

        int x = q.front(); // 큐에 가장 앞에 있는 값
        q.pop();
        result[i] = x; // 결과 값에 추가.
        for(int i = 0; i < a[x].size(); i++){
            int y = a[x][i];
            // 새롭게 진입차수가 0이 된 정접을 큐에 삽입
            if(--inDegree[y] == 0){
                q.push(y);
            }
        }
    }
    for(int i = 1; i<= n; i++){
        cout << result[i] << " ";
    }
    cout << endl;
}
int main() {
    n = 7;
    a[1].push_back(2);
    inDegree[2]++;
    a[1].push_back(5);
    inDegree[5]++;
    a[2].push_back(3);
    inDegree[3]++;
    a[3].push_back(4);
    inDegree[4]++;
    a[4].push_back(6);
    inDegree[6]++;
    a[5].push_back(6);
    inDegree[6]++;
    a[6].push_back(7);
    inDegree[7]++;

    topologySort();


    return 0;
}
