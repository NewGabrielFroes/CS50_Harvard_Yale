import csv
import sys
import random
import math


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    data_base = []

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            data_base.append(row)
    sequence = open(sys.argv[2]).read()
    
    count = 0  # Verifica se todas as str batem com o banco de dados
    
    for person in data_base:
        count = 0  # Reinicia todas as vezes que entra uma pessoa nova
        for i in range(1, len(list(person))):  # percorre todos os str ex: 'AGATC' --> 'TCTG'
            if count_str(sequence, int(person[list(person)[i]]), list(person)[i]):
                count += 1
            if count == len(list(person)) - 1:  # Verifica se todos os str são verdadeiros
                print(person['name'])
                return
    print("No match")


def count_str(sequence, qtd_dna_str, dna_str):
    qtd_letters = len(dna_str)
    i = 0
    j = qtd_letters
    count = 0
    count_copy = 0

    for position in sequence:  # Conta o máximo de str em sequencias
        if dna_str == sequence[i:j]:
            if count > count_copy:
                count_copy = count
            count = 0
            while dna_str == sequence[i:j]:
                count += 1
                i += qtd_letters
                j = i + qtd_letters
        i += 1
        j = i + qtd_letters
        
    if count == qtd_dna_str or count_copy == qtd_dna_str:  # Verifica se o str do banco de dados bate com str da pessoa
        return True
    return False


main()