#include <iostream>

using namespace std;
#define INF 10000000

// - 다익스트라 알고리즘
// 하나의 정점에서 모든 정점으로의 최단 경로를 구하는 알고리즘.

// - 플로이드 와샬 알고리즘
// 모든 정점에서 모든 정점으로의 최단경로를 구하는 알고리즘.
// 거처가는 정점을 기준으로 최단거리를 구하는 것.
// 어떤 정점을 거쳐가는지를 기준으로 비용을 계속해서 갱신해주는 알고리즘


int **graphMatrix = nullptr;

// 그래프 초기화 함수
int** graphInit(int N) {
    int** matrix = new int* [N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = INF;
        }
    }
    return matrix;
}

// 그래프 복사 함수
int **deepCopy(int **targetMatrix, int N) {
    int **result = new int *[N];
    for (int i = 0; i < N; i++) {
        result[i] = new int[N];
        for (int j = 0; j < N; j++) {
            result[i][j] = targetMatrix[i][j];
        }
    }
    return result;
}

// 플로이드 와샬 알고리즘 함수
int** floydWarshall(int **graphMatrix, int N) {
    int **result = deepCopy(graphMatrix, N);
    // k = 거쳐가는 노드
    for (int k = 0; k < N; k++) {
        // i = 출발 노드
        for (int i = 0; i < N; i++) {
            // j = 도착노드
            for (int j = 0; j < N; j++) {
                if(result[i][k] + result[k][j] < result[i][j]){
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }
    return result;
}

// 그래프 출력 함수
void printGraph(int** matrix, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int N, M; // Vertex Size, Edge Size;
    cin >> N >> M;
    // 그래프 초기화 부분
    int** graphMatrix = graphInit(N);
    // 엣지 초기화 부분
    for (int i = 0; i < M; i++) {
        int src, dst, weight;
        cin >> src >> dst >> weight;
        graphMatrix[src][dst] = weight;
    }

    printGraph(floydWarshall(graphMatrix, N), N);

    return 0;
}
