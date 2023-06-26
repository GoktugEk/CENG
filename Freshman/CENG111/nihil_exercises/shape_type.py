def shape_type(x):
    if len(x) == 3:
        a = x[0]
        b = x[1]
        c = x[2]
        if not c<abs(a-b) and b<abs(c-a) and a< abs(b-c):
            return "not a triangle"
        elif a==b and b==c:
            return 'equilateral triangle'
        elif a==b or b==c or a==c:
            return "isosceles triangle"
        else:
            return "triangle"
    elif len(x) == 4:
        
        a = x[0]
        b = x[1]
        c = x[2]
        d = x[3]
        if a == b and a==c and a==d:
            return "square"
        elif a==c and b==d:
            return "rectangle"
        else:
            return "quad"
    else:
        return "not a shape"