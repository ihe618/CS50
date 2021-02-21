from cs50 import get_string

number = get_string("Number: ")


l = len(number)
e = 0
o = 0
for i in range(1,l+1,2):                                                                                       
    print(f"{i}, ", end="")
print()
for i in range(1,l+1,2):
    if i < l:
        print(f"{number[l-1-i]}, ", end="")
        n = 2*int(number[l-1-i])
        s = str(n)
        for x in range(0,len(s)):
            e = e + int(s[x])
    else: 
        e = e
print(e)
for i in range(1,l+1,2):
    if i <= l: 
        print(f"{number[l-i]}, ", end="")
        n = int(number[l-i])
        o = o + n   
    else:
        o = o
print(o)
print(e +  o)
  
