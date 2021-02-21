from cs50 import get_int



while True:
    n = get_int("Enter int between 1 and 8: ")                 #prompt user for number
    if 0 < n < 9:
        break

for i in range(n):                                              #for each row n rows
    for j in range(n-1-i):
        print(" ", end="")
    for j in range(i+1):                                        #for number of times as row number, print j times followed by 2 spaces
        print("#", end="")
    print("  ", end="")
    for j in range(i+1):                                         #for number of times as row number, print j times
        print("#", end="")
    print()
