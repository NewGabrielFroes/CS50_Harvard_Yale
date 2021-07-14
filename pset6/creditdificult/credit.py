from cs50 import get_int
import math


def main():
    card_number = get_int("Number: ")

    if is_card_valid(len(str(card_number))):
        banner(check_sum(card_number), card_number)
    else:
        print("INVALID")


def is_card_valid(len_number):
    if len_number == 13 or len_number == 15 or len_number == 16:
        return True
    return False


def check_sum(card_number):
    sum1 = 0
    sum2 = 0
    result = 0

    while card_number > 0:
        modulus1 = int(card_number % 10)  # Pega do último digito e adiciona
        card_number = int(card_number / 10)  # Resto do cartao faltando
        sum1 += int(modulus1)  # Soma de todos os digitos começando pelo último

        modulus2 = int(card_number % 10)  # Pega do penútimo digito
        card_number = int(card_number / 10)  # Resto do cartao faltando

        modulus2 = int(modulus2 * 2)  # Multiplica pois esta na formula
        digitus1 = int(modulus2 % 10)  # Pega o último digito EX: 18 --> Retira o 8
        digitus2 = int(modulus2 / 10)  # Pega o primeiro digito EX: 18 --> Retira o 1
        sum2 = (sum2 + digitus1 + digitus2)  # Soma todos os digitos começando pelo penúltimo

        result = (sum1 + sum2) % 10

    if result % 10 == 0:
        return True
    return False


def banner(result, card_number):
    if result == True:
        while True:
            card_number = int(card_number / 10)
            if card_number <= 100:
                break
        
        if (int(card_number / 10) == 5) and (0 < int(card_number % 10) and int(card_number % 10) < 6):
            print("MASTERCARD")
        elif (int(card_number / 10) == 3) and (int(card_number % 10) == 4 or int(card_number % 10) == 7):
            print("AMEX")
        elif (int(card_number / 10) == 4):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()