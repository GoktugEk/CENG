def translate(x):
    if not x.startswith("AUG"):
        return 'start codon not recognized'
    elif not (x.endswith('UAA') or  x.endswith('UGA') or x.endswith('UAG')):
        return "stop codon not recognized"
    f = x[3:6]
    s = x[6:9]
    t = x[9:12]
    dic = {'UUU':'Phenylalanine', 'UUA':'Leucine','AUU':'Isoleucine'\
           ,'GUU':'Valine','UCU':'Serine'}
    return [dic[f],dic[s],dic[t]]
