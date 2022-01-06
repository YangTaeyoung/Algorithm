LEAVE = False
ENTER = True


def solution(record):
    answer = list()
    user_dict = dict()
    logs = []
    for r in record:
        operations = r.split(" ")
        if operations[0] == "Enter":
            user_dict[operations[1]] = operations[2]
            logs.append([ENTER, operations[1]])
        elif operations[0] == "Change":
            user_dict[operations[1]] = operations[2]
        elif operations[0] == "Leave":
            logs.append([LEAVE, operations[1]])
    for log in logs:
        if log[0]:
            answer.append(f"{user_dict[log[1]]}님이 들어왔습니다.")
        else:
            answer.append(f"{user_dict[log[1]]}님이 나갔습니다.")
    return answer
