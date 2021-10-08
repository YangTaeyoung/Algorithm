#include <iostream>

// - 다이나믹 프로그래밍(Dynamic Programming)
// > 하나의 문제는 단 한번만 풀도록 하는 알고리즘. 한번 푼 것을 여러분 푸는 것은 비효율적이기 때문.
// - DP의 가정
// 1. 큰 문제를 작은 문제로 나눌 수 있다.
// 2.  작은 문제에서 구한 정답은 그것을 포함하는 큰 문제에서도 동일하다.

// - 메모이제이션(Memoization)
// > 이미 계산한 결과는 배열에 저장하는 것.

// 기존의 피보나치 수열을 구하는 것. (이전에 구했던 것을 계속 호출해야 하기 때문에 낭비가 심하다.)
int fibo(unsigned int x) {
    if (x <= 2) return 1;
    return fibo(x - 1) + fibo(x - 2);
}

// 다이나믹 프로그래밍을 적용 O(n) 번안에 구할 수 있다.
int d[100];
int dp_fibo(int x) {
    if (x <= 2) return 1;
    if (d[x] != 0) return d[x];
    return d[x] = dp_fibo(x - 1) + dp_fibo(x - 2);
}

int main() {
    printf("%d", dp_fibo(40));
    return 0;
}
