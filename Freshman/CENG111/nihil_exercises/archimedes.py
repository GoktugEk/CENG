a = raw_input()
b = raw_input()
i1 = a.count("i")
i2 = b.count("i")
o1 = a.count("o")
o2 = b.count("o")
d1 = i1/ float(len(a))
d2 = float(i2) / len(b)
print d1/d2
