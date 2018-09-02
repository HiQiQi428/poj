map = {}
with open('input.txt', 'rb') as f:
    f.readline()
    for line in f.readlines():
        line = line.strip()
        if line in map: map[line] += 1
        else: map[line] = 1

with open('output-s-map.txt', 'wb') as f:
    for k, v in map.items():
        f.write(k + '=' + str(v) + '\n')
    f.write(str(len(map)) + '\n')

with open('output-s-result.txt', 'wb') as f:
    newMap = {}
    for k, v in map.items():
        if v > 1:
            newMap[k] = v
    list = sorted(newMap.items(), key=lambda x:x[0], reverse=False)
    for k, v in list:
        f.write(k[:3] + '-' + k[3:] + ' ' + str(v) + '\n')
    f.write(str(len(newMap)) + '\n')