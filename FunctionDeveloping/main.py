import math

# 프로그래머스 - LEVEL 2 - 기능개발문제
# https://programmers.co.kr/learn/courses/30/lessons/42586

def solution(progresses, speeds):
    answer = []
    rest_days = []
    for p, s in zip(progresses, speeds):
        rest_days.append(math.ceil((100-p)/s))
    flag_day = rest_days[0]
    count = 1
    for day in rest_days[1:]:
        # 기능이 끝나는 날이 모두 동일할 때 부등호가 이퀄이 포함되어 있지 않으면 에러가 발생한다.
        # 1,1,1 씩 끝나기 때문
        if flag_day >= day:
            count += 1
        else: 
            answer.append(count)
            flag_day = day
            count = 1
    answer.append(count)
    return answer