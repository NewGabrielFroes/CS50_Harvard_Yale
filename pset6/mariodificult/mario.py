from cs50 import get_int

 
def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break
    return n
    
    
def main():
    height = get_positive_int()
    for i in range(1, height + 1):
        for j in range(height, i, -1): 
            print(" ",  end="")  # create the spacing 1
        for x in range(0, i):
            print("#",  end="")  # create the pyramids 1
        for y in range(0, 2):
            print(" ",  end="")  # create the spacing 2
        for z in range(0, i):
            print("#",  end="")  # create the pyramids 2
        
        print("")
        

if __name__ == "__main__":
    main()