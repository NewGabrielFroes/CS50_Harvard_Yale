from cs50 import get_string
import math
import string


def main():
    text = get_string("Text: ")  # Pega o texto
 
    l = (countLetters(text) / float(countWords(text))) * 100  # Arredonda
    s = (countSentences(text) / float(countWords(text))) * 100  # Arredonda
    
    l = round(l * 100) / 100  # Formula
    s = round(s * 100) / 100  # Formula
    index = round(0.0588 * l - 0.296 * s - 15.8)  # Calcula Index
    
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade: " + str(index))


def countLetters(text):
    newText = text.translate(str.maketrans('', '', string.punctuation))  # Retira todas as pontuacoes
    qtdLetters = 0

    for letra in newText:
        if not letra.isdigit() and not letra.isspace():
            qtdLetters += 1

    return qtdLetters


def countWords(text):
    qtdWords = 0
    for letra in text:
        if letra.isspace():
            qtdWords += 1

    qtdWords += 1
    return qtdWords


def countSentences(text):
    qtdSentences = 0
    for letra in text:
        if letra == '.' or letra == '?' or letra == '!':
            qtdSentences += 1
            
    return qtdSentences
    
    
main()
