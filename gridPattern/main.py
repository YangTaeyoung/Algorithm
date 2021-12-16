# 프로그래머스 - LEVEL 2  - 멀쩡한 사각형 문제
# https://programmers.co.kr/learn/courses/30/lessons/62048
# 최소 공배수 찾는 함수
def gcd(num1: int, num2: int):
    result = 1  # 공약수가 없는 경우
    for i in range(2, min(num1, num2) + 1):
        if num1 % i == 0 and num2 % i == 0:
            result = i
    return result

# 제거될 사각형의 개수를 출력하는 함수
def get_remove_rect(w: int, h: int):
    # 최소공배수가 없을 경우 (중간에 모든 사각형이 모서리가 다 겹쳐있는 경우)
    if (num_gcd := gcd(w, h)) == 1:
        return w + h - 1
    # 최소공배수가 있는 경우 (안에 작은 사각형(최대공약수 만큼) 있음)
    else:
        return get_remove_rect(w // num_gcd, h // num_gcd) * num_gcd


def solution(w: int, h: int):
    return w * h - get_remove_rect(w, h)


print(solution(8, 12))