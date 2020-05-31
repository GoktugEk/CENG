def is_substring(s,s2):
    if len(s2) == 0:
        return False
    elif s2[:len(s)]==s:
        return True
    return is_substring(s,s2[1:])
