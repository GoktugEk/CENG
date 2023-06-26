import sys
import copy

def reading_map():
    with open("{}".format(sys.argv[1]),"r") as file: #to take terminal arguments
        lenght = len(file.readline()) 
        file.seek(0)
        data = [" "*(lenght+2)] + file.readlines() + [" "*(lenght+2)]
        for i in range(len(data)):
            if data[i][-1] == "\n":
                data[i] = data[i][:-1]
        return data


def reading_rules():
    with open(sys.argv[2],"r") as file2:
        rules = file2.readlines()
        rules_ = []
        rules_star = []
        for i in rules:
            if i[0] == i[3]:
                rules.remove(i)
        for i in rules:
            if i[0] == "-":
                rules_.append(i)
            else:
                rules_star.append(i)
        return rules_,rules_star


def boolean(x, roundings): #Evaluating rules,returns boolean forms
    if x[1] == "=":
        return bool((roundings.count("*") == int(x[2])))
    elif x[1] == ">":
        return bool((roundings.count("*") > int(x[2])))
    elif x[1] == "<":
        return bool((roundings.count("*") < int(x[2])))

def process_map(data,rules_,rules_star):
    fake_data = copy.deepcopy(data)
    for i in range(1,len(data)-1): #to see what we have around
        line = " " + data[i] + " "
        linebelow = " " + data[i+1] + " "
        lineabove = " " + data[i-1] + " "
        fake_line = " " + fake_data[i] + " "
        for j in range(1,len(line)-1):
            roundings = [line[j-1],line[j+1],linebelow[j+1],linebelow[j],linebelow[j-1],lineabove[j+1],lineabove[j],lineabove[j-1]] #what we have around
            if line[j] == "-":
                for k in rules_:
                    if boolean(k,roundings):
                        fake_data[i] = fake_data[i][:j-1] + k[3] + fake_data[i][j:]
            else:
                for k in rules_star:
                    if boolean(k,roundings):
                        fake_data[i] = fake_data[i][:j-1] + k[3] + fake_data[i][j:]
    if data == fake_data:
        return (copy.deepcopy(fake_data),"Not Changed")
    return (copy.deepcopy(fake_data),"Changed")

    
def main():
    data = reading_map()

    rules_,rule_star = reading_rules()

    if len(rules_) == 0 and len(rule_star)== 0:
        print(data)
        return

    generation = int(sys.argv[3])
    

    m = 0
    while m < generation:
        data, state = process_map(data,rules_,rule_star)
        if (state == "Changed"):
            pass
        else:
            break
        m += 1
    data.pop()
    data.pop(0)
    for i in data:
        print i

if __name__ == "__main__":
    main()