a = raw_input()
r1 = a.find("<reverse>") + 8
r2 = a.find("</reverse>")-1
b = a[:a.find("<reverse>")]
c = a[r2+11:]
ters = a[r1+1:r2+1]
sol = b + ters[::-1] + c
print sol