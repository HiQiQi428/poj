
def strequ(a, b):
    s = min(len(a), len(b))
    for i in range(s):
        if a[i] != b[i]:
            return False
    return True

def combine(f1, f2):
    try:
        a = f1.readlines().__iter__()
        b = f2.readlines().__iter__()
        while True:
            yield (a.next(), b.next())
    except:
        pass

with open('output-s-result.txt', 'rb') as fs:
    with open('output-result.txt', 'rb') as f:
        lineNum = 0
        errNum = 0
        for a, b in combine(fs, f):
            lineNum += 1
            if not strequ(a, b):
                print('[%d] a: %s b: %s' % (lineNum, a, b))
                errNum += 1
            a = fs.readline()
            b = f.readline()
        print('total: %d err: %d' % (lineNum, errNum))