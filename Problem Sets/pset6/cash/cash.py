from cs50 import get_float

def main():
    i = get_change_amount()
    calculate(i)

def get_change_amount():
    while (True):
        change = get_float("Change owed: $")
        if change >= 0:
            break
    return change

def calculate(change):
    change *= 100
    coins = 0

    while change >= 25:
        change -= 25
        coins += 1

    while change >= 10:
        change -= 10
        coins += 1

    while change >= 5:
        change -= 5
        coins += 1

    while change >= 1:
        change -= 1
        coins += 1

    print(coins)
if __name__ == "__main__":
    main()
