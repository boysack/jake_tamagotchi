# sereve per convertire un array rgb565 in drawLine
#convertire in un insieme di punti, da/per cui bisogna tracciare una linea di uno stesso colore

# args: 
#   [1] -> filepath of c color array
#   [2] -> filepath of c alpha array
#   [3] -> width image
#   [4] -> height image
#   [5] -> final c array name
#   [6] -> final file path/filename (relative or absolute path)

import sys

class Point:
  def __init__(self, x0=None, y0=None, x1=None, y1=None, color=None):
    self.x0 = x0
    self.y0 = y0
    self.x1 = x1
    self.y1 = y1
    self.color = color

f = open(sys.argv[1])
for line in f:
    if(line.find("{")):
        start = line.index("{")
        end = line.index("}")
        colors = [eval(element) for element in line[start+1:end].split(",")] #end not included
        break
f.close()

f = open(sys.argv[2])
for line in f:
    if(line.find("{")):
        start = line.index("{")
        end = line.index("}")
        alpha = [eval(element) for element in line[start+1:end].split(",")] #end not included
        break
f.close()

xLimit = int(sys.argv[3])
yLimit = int(sys.argv[4])
drawLineArray = [] #si può anche non dichiarare
p = Point()

for y in range(yLimit):
    for x in range(xLimit):
        if(alpha[y*xLimit+x]!=0):
            print(f'x = {x}, y = {y} --> not transparent')
            if(p.x0 is not None and p.y0 is not None and p.color is not None):
                print(f'\t\'--> already a point')
                if(p.color != colors[y*xLimit+x]):
                    print(f'\t\'--> different colors with prev point. Saving prev color {p.color}')
                    p.x1 = x-1
                    p.y1 = y
                    drawLineArray.append(p)
                    p = Point(x0=x, y0=y, color=colors[y*xLimit+x])
                    print(f'\t\'--> new color {p.color}')
                    #gestire ultimo pixel
                    if(x==xLimit-1):
                        print(f'\t\'--> last point. Saving color {p.color}')
                        p.x1 = x
                        p.y1 = y
                        drawLineArray.append(p)
                        p = Point()
                else:
                    print('\t\'--> same color')
                    #gestire ultimo pixel
                    if(x==xLimit-1):
                        print(f'\t\'--> last point. Saving color {p.color}')
                        p.x1 = x
                        p.y1 = y
                        drawLineArray.append(p)
                        p = Point()
            else:
                p.x0 = x
                p.y0 = y
                p.color = colors[y*xLimit+x]
                print(f'\t\'--> new color {p.color}')
                #gestire ultimo pixel
                if(x==xLimit-1):
                        print(f'\t\'--> last point. Saving color {p.color}')
                        p.x1 = x
                        p.y1 = y
                        drawLineArray.append(p)
                        p = Point()
        else:
            print(f'x = {x}, y = {y} --> tranparent')
            if(p.x0 is not None and p.y0 is not None and p.color is not None):
                print(f'\t\'--> already a point. Saving color {p.color}')
                p.x1 = x-1
                p.y1 = y
                drawLineArray.append(p)
                p = Point()

strArray = sys.argv[5] + " = {"
for i in range(len(drawLineArray)):
    if(i<len(drawLineArray)-1):
        strArray += "{" + str(drawLineArray[i].x0) + ", " + str(drawLineArray[i].y0) + ", " + str(drawLineArray[i].x1) + ", " + str(drawLineArray[i].y1) + ", " + str(drawLineArray[i].color) + "}, "
    else:
        strArray += "{" + str(drawLineArray[i].x0) + ", " + str(drawLineArray[i].y0) + ", " + str(drawLineArray[i].x1) + ", " + str(drawLineArray[i].y1) + ", " + str(drawLineArray[i].color) + "}}; "

f = open(sys.argv[6], "w")
f.write(strArray)
f.close()

print(len(drawLineArray))

# PSEUDOCODICE:

# analizza la riga:
#   se non sei a fine riga:
#       se l'elemento è trasparente:
#           se non è il primo elemento (f==1):
#               aggiorna x1 e y1 e salva nell'array
#               f = 0
#               
#       se l'elemento non è trasparente:
#           se è il primo elemento (f==0):
#               aggiorna x0 e y0 e color
#               f = 1
#           se no:
#               se il color non è uguale:
#                   aggiorna x1 e y1 e salva nell'array
#                   f = 0
#               se no:
#                   continua
#               
#   se no:
#       aggiorna x1 e y1 e salva nell'array (a meno che non ci sia una riga completamente trasparente, da gestire??)