from cs50 import get_string


def main():
    
    # prompt for number   
    number = get_string("Number: ")
    
    # define length and first 2 digits
    l = len(number)
    f2 = int(number[0] + number[1])
    
    # first check number of digits
    if l > 16 or l < 13:
        print("INVALID")
        
    # check validity 
    elif luhn(number) is True:
        if f2 == 34 or f2 == 37:
            print("AMEX")
        elif f2 == 51 or f2 == 52 or f2 == 53 or f2 == 54 or f2 == 55:
            print("MASTERCARD")
        elif number[0] == "4":
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
    

def luhn(number):
    
    # define function for luhn's test
    l = len(number)
    e = 0
    o = 0
    for i in range(1, l+1, 2):    
        if i < l:
            n = 2*int(number[l-1-i])
            s = str(n)
            for x in range(0, len(s)):
                e = e + int(s[x])
        else:
            e = e
    for j in range(1, l+1, 2):
        if j <= l:
            o = o + int(number[l-j])
        else:
            o = o
    sum = e + o
    s = str(sum)
    if int(s[len(s)-1]) != 0:
        print("INVALID")
    else:
        return True

        
main()