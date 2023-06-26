def tictactoe(liste):
    col0 = liste[0][0] + liste[1][0] + liste[2][0]
    col1 = liste[0][1] + liste[1][1] + liste[2][1]
    col2 = liste[0][2] + liste[1][2] + liste[2][2]
    for i in liste:
        if i == "XXX":
            return "X"
        elif i == "OOO":
            return "O"
    if col0 == "XXX" or col1 == "XXX" or col2 == "XXX":
        return "X"
    elif col0 == "OOO" or col1 == "OOO" or col2 == "OOO":
        return "O"
    else:
        return "tie"