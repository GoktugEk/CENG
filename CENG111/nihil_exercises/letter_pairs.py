def letter_pairs(s):
    if len(s) <= 1:
        return []
    else:
        return [s[0]+s[1]] + letter_pairs(s[1:])
