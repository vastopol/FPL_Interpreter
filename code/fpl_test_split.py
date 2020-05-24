#!/usr/bin/python3

# ad hoc FPL parser

#-------------------------------

def main():

    # word = input()
    word = "f.g.h{a.b.c{q;w.x;e;r}.d;t}.l.m{n;p;t}.k:<1,2,3>"

    print(word)

    a = word.split(':')
    b = a[0].split('.')
    arg = a[1]

    print(a)
    print(b)
    print(arg)

    funs = list()
    joins = list()
    flag = False
    stk = 0

    for f in b:
        if not flag and not '{' in f and not '}' in f:
            funs.append(f)
        else:
            flag = True
            for c in f:
                if c == '{':
                    stk += 1
                if c == '}':
                    stk -= 1
            joins.append(f)
            if stk != 0:
                joins.append(".")
            if stk == 0:
                flag = False
                fstr = str()
                for j in joins:
                    fstr += str(j)
                funs.append(fstr)
                joins = list()

    print(funs)

    close = list()

    for fun in funs:
        if '{' in fun:
            f = fun.split('{',1)
            close.append((f[0],f[1][:-1]))
        else:
            close.append((fun,None))

    for c in close:
        print(c)

#-------------------------------

if __name__ == '__main__':
    main()
