def solution(s):
    answer = len(s)
    # 기준 글자 수 반복문
    for i in range(1, (len(s) // 2) + 1):
        lens = len(s)
        flag_char = s[:i]
        j = i
        cnt = 0
        while j < len(s):
            if flag_char == s[j:j+i]:  # 이전 패턴과 매칭
                cnt += 1
            else:  # 매칭 안됨
                if cnt > 0:
                    lens = lens - (cnt * i) + len(str(cnt+1))
                flag_char = s[j:j + i]
                cnt = 0
            j += i
        if cnt > 0:
            lens = lens - (cnt * i) + len(str(cnt + 1))
        answer = min(answer, lens)

    return answer
print(solution("abcabcabc"))