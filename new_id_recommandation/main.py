# 정규식을 활용한 풀이
# 프로그래머스 - 신규 아이디 추천
# https://programmers.co.kr/learn/courses/30/lessons/72410



import re


def step_1(new_id: str):
    return new_id.lower()


def step_2(new_id: str):
    return re.sub(r'[^a-z.\-_0-9]', "", new_id)


def step_3(new_id: str):
    result = re.sub(r"\.+", '.', new_id)
    return result


def step_4(new_id: str):
    result = re.sub(r"^\.", "", new_id)
    result = re.sub(r"\.$", "", result)
    return result


def step_5(new_id: str):
    if len(new_id) == 0:
        return 'a'
    return new_id


def step_6(new_id: str):
    return new_id[:15]


def step_7(new_id: str):
    result = list(new_id)
    if len(new_id) <= 2:
        last_char = new_id[len(new_id) - 1]
        while len(result) != 3:
            result.append(last_char)
    return ''.join(result)


def solution(new_id: str):
    answer = new_id
    answer = step_1(answer)
    answer = step_2(answer)
    answer = step_3(answer)
    answer = step_4(answer)
    answer = step_5(answer)
    answer = step_6(answer)
    answer = step_4(answer)
    answer = step_7(answer)

    return answer
