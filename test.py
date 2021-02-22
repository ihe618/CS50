from cs50 import get_string



def main():
    text = get_string("Text: ")
    # text.split separates words in text- len counts those words
    wc = len(text.split())
    print(wc)
    
    l = 0
    for i in range(0, len(text)):
        if (64 < ord(text[i]) and ord(text[i]) < 91) or (96 < ord(text[i]) and ord(text[i]) < 123):
            l = l + 1
    print(l)
    
main()