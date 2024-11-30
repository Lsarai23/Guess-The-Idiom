import pandas as pa
import math

port = pa.read_excel("port.xlsx")
ingles = pa.read_excel("ing.xlsx")
pV = []
iV = []
for i in range(0,26):
    p = port['freq'][i]
    ing = ingles['freq'][i]
    if(p>=ing):
        pV.append(math.ceil(p))
        iV.append(math.floor(ing))
    else:
        pV.append(math.floor(p))
        iV.append(math.ceil(ing))
print("Portugûes",pV)
print("Inglês   ",iV)
