def spell(x):
    x = str(x)
    soz = {"0":"","1":"bir","2":"iki","3":"uc","4":"dort","5":"bes",\
           "6":"alti","7":"yedi","8":"sekiz","9":"dokuz"}
    soz1 = {"1":"on","2":"yirmi","3":"otuz","4":"kirk","5":"elli",\
           "6":"altmis","7":"yetmis","8":"seksen","9":"doksan"} 
    res = [soz1[x[0]],soz[x[1]]]
    return res