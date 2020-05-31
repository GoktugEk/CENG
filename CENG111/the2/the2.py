def isCovered(cpbl,cptr,t1bl,t1tr,t2bl,t2tr):
    if (t1bl[0]<= cpbl[0]     \
    and t1tr[1] >= cptr[1]   \
    and t1bl[1]<= cpbl[1]    \
    and t1tr[0] >= cptr[0])   \
    or                       \
    (t2bl[0]<= cpbl[0]     \
    and t2tr[1] >= cptr[1]   \
    and t2bl[1]<= cpbl[1]    \
    and t2tr[0] >= cptr[0]):
        return "COMPLETELY COVERED"
    elif (((t1tr[0] >= cptr[0])\
    and (t1bl[0] >= cptr[0])) \
    or (t2tr[0] >= cptr[0] \
    and t2bl[0] >= cptr[0]) \
    or (t1tr[1] >= cptr[1] \
    and t1bl[1] >= cptr[1]) \
    or (t2tr[1] >= cptr[1] \
    and t2bl[1] >= cptr[1]))\
    or (((t1tr[0] <= cpbl[0])\
    and (t1bl[0] <= cpbl[0])) \
    or (t2tr[0] <= cpbl[0] \
    and t2bl[0] <= cpbl[0]) \
    or (t1tr[1] <= cpbl[1] \
    and t1bl[1] <= cpbl[1]) \
    or (t2tr[1] <= cpbl[1] \
    and t2bl[1] <= cpbl[1])):
        return "NOT COMPLETELY COVERED"
    elif min(t1bl[0],t2bl[0]) <= cpbl[0]      \
        and max(t1tr[0],t2tr[0]) >= cptr[0] \
        and min(t1bl[1],t2bl[1]) <= cpbl[1] \
        and max(t1tr[1],t2tr[1]) >= cptr[1] \
        and min(t2tr[0],t1tr[0]) >= max(t2bl[0],t1bl[0]) \
        and max(t1bl[1],t2bl[1]) <= min(t2tr[1],t1tr[1]):
            if ((cpbl[0] < t1bl[0] and cpbl[1] < t2bl[1]) or (cpbl[0] < t2bl[0] and cpbl[1] < t1bl[1])) :
                return "NOT COMPLETELY COVERED"
            elif ((cptr[0] > t1tr[0] and cptr[1] > t2tr[1]) or (cptr[0] > t2tr[0] and cptr[1] > t1tr[1])):
                return "NOT COMPLETELY COVERED"
            elif ((cptr[0] > t1tr[0] and cpbl[1] < t2bl[1]) or (cptr[0] > t2tr[0] and cpbl[1] < t1bl[1])):
                return "NOT COMPLETELY COVERED" 
            elif ((cpbl[0] < t1bl[0] and cptr[1] > t2tr[1]) or (cpbl[0] < t2bl[0] and cptr[1] > t1tr[1])):
                return "NOT COMPLETELY COVERED"
            return "COMPLETELY COVERED"
    else:
         return "NOT COMPLETELY COVERED"
