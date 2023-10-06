import sys

# args: 
#   [1] -> filepath of c color array
#   [2] -> filepath of c alpha array
#   [3] -> transparency value
#   [4] -> final c array name
#   [5] -> final file path/filename (relative or absolute path)

# get c color array from file and convert into python format
f = open(sys.argv[1])
for line in f:
    if(line.find("{")):
        start = line.index("{")
        end = line.index("}")
        list8 = [eval(element) for element in line[start+1:end].split(",")] #end not included
        break
f.close()

# get c alpha array from file and convert into python format
f = open(sys.argv[2])
for line in f:
    if(line.find("{")):
        start = line.index("{")
        end = line.index("}")
        alpha = [eval(element) for element in line[start+1:end].split(",")] #end not included
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

# convert transparent pixels in transparent color value
finalArray = []
transparencyVal = sys.argv[3]
for i in range(len(list16)):
    if(alpha[i]==0):
        finalArray.append(transparencyVal)
    else:
        finalArray.append(list16[i])

# convert and save in c format
strArray = sys.argv[4] + " = {"
for i in range(len(finalArray)):
    if(i<len(finalArray)-1):
        strArray += str(finalArray[i]) + ", "
    else:
        strArray += str(finalArray[i]) + "};"

f = open(sys.argv[5], "w")
f.write(strArray)
f.close()