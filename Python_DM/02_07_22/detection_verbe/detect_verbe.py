verbe_etre = ['suis', 'es', 'est', 'sommes', 'etes', 'sont']
verbe_avoir = ['ai', 'as', 'a', 'avons', 'avez', 'ont']

phrase = input('Saissisez une phrase : ')

def get_verb(splited_phrase: list) -> list:
    """Get verbe position"""
    verbe_position = []
    position_value = 0
    for each_char in splited_phrase:
        if each_char in verbe_etre or each_char in verbe_avoir:
            verbe_position.append(position_value)
        position_value += 1
    return verbe_position

splited_phrase = phrase.split()

print(get_verb(splited_phrase))
