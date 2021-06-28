def main():
    # get credit card number
    number = get_num()
    # calculate checksum and validate type
    check(number)


def get_num():
    # get valid card number
    while True:
        num = input("Card Number: ")
        if int(num) >= 0 and num.isdigit():
            break
    return num


def check(num):
    # calculating checksum
    checksum = sum1(num) + sum2(num)

    # check if checksum value is true
    if checksum % 10 == 0:
        # determine and print card type
        card_type = check_card_type(num)
        print(card_type)
    else:
        print("INVALID")


def check_card_type(num):
    # boolean expressions. Validates card type by its specifications
    amex = len(num) == 15 and num[0] == '3' and (num[1] == '4' or num[1] == '7')
    visa = (len(num) == 13 or len(num) == 16) and num[0] == '4'
    mastercard = len(num) == 16 and num[0] == '5' and int(num[1]) in range(1, 6)

    # Check card type
    if amex:
        card_type = "AMEX"
    elif mastercard:
        card_type = "MASTERCARD"
    elif visa:
        card_type = "VISA"
    else:
        card_type = "INVALID"

    return card_type


def sum1(num):
    # Multiply every other digit by 2, starting with the number’s
    # second-to-last digit, and then add those products’ digits together.
    numbers = num[::-1]
    numbers = numbers[1::2]
    numbers = list(numbers)

    for i in range(0, len(numbers)):
        numbers[i] = str(int(numbers[i]) * 2)
    numbers = "".join(numbers)

    sum_of_digits = 0

    for digit in numbers:
        sum_of_digits += int(digit)

    return sum_of_digits


def sum2(num):
    # calculate the sum of the digits that weren’t multiplied by 2
    nums = num[::-2]
    nums = list(nums)

    for i in range(0, len(nums)):
        nums[i] = int(nums[i])

    return sum(nums)


if __name__ == "__main__":
    main()