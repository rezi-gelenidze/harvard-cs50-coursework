from cs50 import get_int

# Main function
def main():
    Height = get_height()
    generate(Height)

# Generate pyramid
def generate(height):
    i, j = 1, height - 1
    while i <= height:
        print(" " * j + "#" * i + "  " + "#" * i)
        i += 1
        j -= 1

# Get correct input from an user
def get_height():
    while (True):
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break
    return n

if __name__ == "__main__":
    main()

