import heapq as hq


# 프로그래머스 - LEVEL 2 - 더 맵게 문제
# https://programmers.co.kr/learn/courses/30/lessons/42626
def solution(scoville, K):
    scoville.sort()  # 힙의 형태로 만들기 위한 초기 정렬
    count = 0
    len_list = len(scoville)
    while True:
        if scoville[0] >= K:
            return count
        elif len(scoville) <= 1:
            return -1
        else:
            # 위에서 두개의 요소를 뽑아 스코빌 식에 맞게 대응
            hq.heappush(scoville, hq.heappop(scoville) + (2 * hq.heappop(scoville)))
            # K에 도달하기 전까지의 횟수
            count += 1
