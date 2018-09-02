from random import randint

list = []

def gen():
    ret = ''
    if len(list) > 0 and randint(0, 100) > 50:
        ret = list[randint(0, len(list) - 1)]
    else:
        for _ in range(7):
            ret += str(randint(0, 9))
        ret += '\n'
        list.append(ret)
    return ret

with open('inputExample.txt', 'wb') as f:
    f.write('100000\n')
    for _ in range(100000):
        f.write(gen())