import the4
import time
import copy

start_time = time.time()

wrong_count = 0
with open("the4_data.json","r") as file:
    lines = file.read().splitlines()
    for line in lines:
        data = line.split(":::")
        data[0] = eval(data[0])
        original_data = copy.deepcopy(data[0])
        data[1] = eval(data[1])
        for i in range(len(data[1])) :
            data[1][i].sort()
        result = the4.chalchiuhtlicue(data[0])
        for k in range(len(result)) :
            result[k].sort()
        
        
        if result == data[1] and lines.index(line)%100 == 0:
            print("Succesful ({}/{})".format(lines.index(line),len(lines)))
        elif result != data[1]:
            print("Failed on {}".format(original_data))
            print("Your work found: {}".format(result))
            print("It should have been {}.".format(data[1]))
            wrong_count += 1

            
            
end_time = time.time()

print("Execution time is: {}".format(end_time-start_time))
print("In {} cases, you've failed {} times.".format(len(lines),wrong_count))