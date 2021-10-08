#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 노드당 들렸는지 체크;
bool c[7];
// 인접 벡터 구현
vector<int> a[8];

// 너비 우선 탐색 알고리즘
void bfs(int start){
    queue<int> q;
    q.push(start);
    c[start] = true;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        printf("%d ", x);
        for(int i = 0; i < a[x].size(); i++)
        {
            int y = a[x][i];
            if(!c[y]){
                q.push(y);
                c[y] = true;
            }
        }
    }
}

int main() {
    // 인접 한 노드 및 에지 설정
    a[1].push_back(2);
    a[2].push_back(1);
    a[1].push_back(3);
    a[3].push_back(1);

    a[2].push_back(3);
    a[3].push_back(2);

    a[2].push_back(4);
    a[4].push_back(2);
    a[2].push_back(5);
    a[5].push_back(2);

    a[4].push_back(5);
    a[5].push_back(4);

    a[3].push_back(6);
    a[6].push_back(3);
    a[3].push_back(7);
    a[7].push_back(3);

    a[6].push_back(7);
    a[7].push_back(6);

    bfs(3);
    return 0;
}
