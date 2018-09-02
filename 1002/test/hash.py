
def hash(x):
    hash = 0
    for c in x:
        hash ^= ord(c)
    return hash


with open('inputExample.txt', 'rb') as f:
    map = {}
    for line in f.readlines():
        h = hash(line)
        if h in map:
            map[h] += 1
        else:
            map[h] = 1
    print(map)
    print((sum(map.values()) - len(map)) / 1000.0)