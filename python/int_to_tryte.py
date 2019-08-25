# Algorithm check for conversion from unsigned int to tryte


if __name__ == '__main__':
    target_int = 8
    result = target_int

    trits = []
    while(result > 0):
        cur_t = result % 3
        if cur_t == 0:
            trits.append(0)
        elif cur_t == 1:
            trits.append(1)
            result -= 1
        elif cur_t == 2:
            trits.append(-1)
            result += 1

        result = result // 3

for n, t in enumerate(trits):
    print(n, t)
