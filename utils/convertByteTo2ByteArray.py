import sys

# args: 
#   [1] -> filepath of c array
#   [2] -> final c array name
#   [3] -> final file path/filename (relative or absolute path)

# get c array from file and convert into python format
f = open(sys.argv[1])
for line in f:
    if(line.find("{")):
        start = line.index("{")
        end = line.index("}")
        list8 = [eval(element) for element in line[start+1:end].split(",")] #end not included
        break
f.close()

# convert array from 8bit into 16 bit array (merging two adjacent elements togheter)
list16 = []
for i in range(0, len(list8), 2):
    a = list8[i]
    b = list8[i+1]

    a = a << 8
    #print(f"shift result: {a}")
    a = a + b
    #print(f"and result: {a}")

    list16.append(a)

# convert and save in c format
strArray = sys.argv[2] + " = {"
for i in range(len(list16)):
    if(i<len(list16)-1):
        strArray += str(list16[i]) + ", "
    else:
        strArray += str(list16[i]) + "};"

f = open(sys.argv[3], "w")
f.write(strArray)
f.close()