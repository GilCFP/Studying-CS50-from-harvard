from cs50 import get_int


def main():
    card_number = get_card_number_from_user()
    # Inicia o nome do cartão como INVALID para depois buscar o nome válido se for o caso
    card_name = "INVALID"

    if is_valid_checksum(card_number):
        # Busca o nome válido do cartão
        card_name = get_card_name(len(card_number), int(card_number[0:2]))
    # imprime o nome do cartão
    print(f'{card_name}')


# Solicita ao usuário o número do cartão (int) e aceita somente números.
# Retorna o numero do cartão no tipo str para conseguir manipular depois
def get_card_number_from_user():
    while True:
        card = get_int("Number: ")

        if card > 0:
            break

    return str(card)


# Verifica se o checksum do número do cartão é válido. Returna true ou false
def is_valid_checksum(card_number):
    checksum = get_checksum(list(card_number[::-1]))
    return  ((checksum % 10) == 0) # Se o checksum terminar com zero é válido (true)


# Calcula o checksum e retorna o valor do cálculo
def get_checksum(reverse_number):
    result = 0
    for key, value in enumerate(reverse_number):
        if key % 2 != 0:
            mult = str(int(value) * 2)

            if len(mult) > 1:
                result += int(mult[0]) + int(mult[1])
            else:
                result += int(mult)
        else:
            result += int(value)

    return result


# Retorna o nome do cartão de crédito
def get_card_name(card_size, prefix):
    if (40 <= prefix <= 49) and (card_size in [13, 16]):
        return "VISA"
    elif (51 <= prefix <= 55) and (card_size == 16):
        return "MASTERCARD"
    elif (prefix in [34, 37]) and (card_size == 15):
        return "AMEX"

    return "INVALID"


if __name__ == '__main__':
    main()