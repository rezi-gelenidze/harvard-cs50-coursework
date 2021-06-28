from cs50 import get_string


def main():
    # Get text
    text = get_string("Text: ")
    determine_grade(text)


def determine_grade(text):
    letters = 0
    sentences = 0
    # iterating over the text and determining
    # number of letters and sentences
    for char in text:
        if char.isalpha():
            letters += 1
        elif char in {'.', '!', '?'}:
            sentences += 1

    # determining number of words by split() function
    words = len(text.split())

    # Calculate and print Coleman–Liau index
    Grade = calculate_index(letters, words, sentences)
    print(Grade)


def calculate_index(letters, words, sentences):
    # Calculation
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Determine grade
    if index > 16:
        return 'Grade 16+'
    elif index < 1:
        return 'Before Grade 1'
    else:
        return f"Grade {index}"


if __name__ == "__main__":
    main()