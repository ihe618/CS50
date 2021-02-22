from cs50 import get_string


def main():
    text = get_string("Text: ")
    # text.split separates words in text- len counts those words
    wc = len(text.split())
    
    l = 0
    # for counting letters, count when letter fall within lowercase and uppercase alphabet range
    for i in range(0, len(text)):
        if (64 < ord(text[i]) and ord(text[i]) < 91) or (96 < ord(text[i]) and ord(text[i]) < 123):
            l = l + 1
    L = (l / wc) * 100
    
    s = 0
    # for counting sentences, count when there is . ! or ?
    for i in range(0, len(text)): 
        if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
            s = s + 1
    S = (s / wc) * 100
    
    # Coleman-Liau index
    C = 0.0588 * L - 0.296 * S - 15.8
    
    if C < 1:
        print("Before Grade 1")
    elif C >= 1 and C <= 16:
        print(f"Grade {round(C)}")
    else:
        print("Grade 16+")
    
        
main()