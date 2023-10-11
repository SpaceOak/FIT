#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Version 0.1

Cílem je vykreslit v "UTF16-artu" strom definovaný listem hodnot. Každý vnitřní uzel stromu obsahuje vždy dvě položky: název uzlu a seznam potomků (nemusí být nutně v tomto pořadí). Názvem může být jakýkoli objekt kromě typu list (seznam). Příklad triviálního stromu o 1 uzlu: [1, []]

Strom bude vykreslen podle následujících pravidel:
    - Vykresluje se shora dolů, zleva doprava.
    - Uzel je reprezentován jménem, které je stringovou serializací objektu daného v definici uzlu.
    - Uzel v hloubce N bude odsazen zlava o N×{indent} znaků, přičemž hodnota {indent} bude vždy kladné celé číslo > 1.
    - Má-li uzel K potomků, povede:
        - k 1. až K-1. uzlu šipka začínající znakem ├ (UTF16: 0x251C)
        - ke K. uzlu šipka začínající znakem └ (UTF16: 0x2514)
    - Šipka k potomku uzlu je vždy zakončena znakem > (UTF16: 0x003E; klasické "větší než").
    - Celková délka šipky (včetně úvodního znaku a koncového ">") je vždy {indent}, výplňovým znakem je zopakovaný znak ─ (UTF16: 0x2500).
    - Všichni potomci uzlu jsou spojeni na úrovni počátku šipek svislou čarou │ (UTF16: 0x2502); tedy tam, kde není jako úvodní znak ├ nebo └.
    - Pokud název uzlu obsahuje znak `\n` neodsazujte nijak zbytek názvu po tomto znaku.
    - Každý řádek je ukončen znakem `\n`.

Další požadavky na vypracovní:
    - Pro nevalidní vstup musí implementace vyhodit výjimku `raise Exception('Invalid tree')`.
    - Mít codestyle v souladu s PEP8 (můžete ignorovat požadavek na délku řádků - C0301 a používat v odůvodněných případech i jednopísmenné proměnné - C0103)
        - otestujte si pomocí `pylint --disable=C0301,C0103 trees.py`
    - Vystačit si s buildins metodami, tj. žádné importy dalších modulů.


Příklady vstupu a výstupu:
INPUT:
[[[1, [True, ['abc', 'def']]], [2, [3.14159, 6.023e23]]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...└──>True
│.......├──>abc
│.......└──>def
└──>2
....├──>3.14159
....└──>6.023e+23

INPUT:
[[[1, [[True, ['abc', 'def']], [False, [1, 2]]]], [2, [3.14159, 6.023e23, 2.718281828]], [3, ['x', 'y']], [4, []]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...├──>True
│...│...├──>abc
│...│...└──>def
│...└──>False
│.......├──>1
│.......└──>2
├──>2
│...├──>3.14159
│...├──>6.023e+23
│...└──>2.718281828
├──>3
│...├──>x
│...└──>y
└──>4

INPUT:
[6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>4
    ├>1
    │ ├>2
    │ └>3
    └>42
      ├>-43
      └>44

INPUT:
[6, [5, ['dva\nradky']]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>dva
radky

Potřebné UTF16-art znaky:
└ ├ ─ │

Odkazy:
https://en.wikipedia.org/wiki/Box_Drawing
"""


def control_input(recursive_list):
    '''
#   validate tree
#       check input according to tree rules
#       format input to deterministic condition
#           ( elem, list )

    :param
        recursive_list: list representing tree

    :return:
        sorted source tree
        exception ll be thrown in case of incorrect input
    '''

    if not recursive_list:
        return None
    if not recursive_list[0] and recursive_list[1]:
        recursive_list[0], recursive_list[1] = recursive_list[1], recursive_list[0]
        return recursive_list
    if isinstance(recursive_list[0], list) and not isinstance(recursive_list[1], list):
        recursive_list[0], recursive_list[1] = recursive_list[1], recursive_list[0]
        return recursive_list

    return recursive_list


def parse_input(recursive_list):
    '''
    pass throw the entire list and control input according to required rules
    :param recursive_list:
        source tree representation
    :return:
        sorted tree and throw an exception in case of invalidate
    '''


    if recursive_list:
        recursive_list = control_input(recursive_list)

        for elem in recursive_list:
            if isinstance(elem, list):
                elem = control_input(elem)
                parse_input(elem)

def single_object_case(rec_list, symbols, is_last, depth):
    '''
    final instance of recursion calculating len of string of current stroke
    :param rec_list:
        source tree representation
    :param symbols:
        default preset of graphic symbols
    :param is_last:
        representation of location in a parent list
    :param depth:
        depth of layer location in recursion
    :return:
        solution for a single item ( vertex )
    '''

    tmp_str = []
    res_graph = []


    for _ in range((symbols[0] + 2) * (depth - 1)):
        tmp_str.append(symbols[1])

    if is_last:
        tmp_str.append(symbols[2])
    else:
        tmp_str.append(symbols[3])
    for _ in range(symbols[0]):
        tmp_str.append(symbols[4])
    tmp_str.append(symbols[6])
    res_graph.extend(tmp_str)
    res_graph.append(rec_list)
    res_graph.append('\n')
    return res_graph


def list_case(rec_list, active_line, symbols, is_last, depth):
    '''
    solution for the case the input containts lists only
        via cycle call common solution and append to a single container
    :param rec_list:
        source tree representation
    :param active_line:
        previous line
    :param symbols:
        default graphic symbols
    :param is_last:
        bool representing location in the list of parent
    :param depth:
        depth of the current layer of recursion
    :return:
        appended list of single case solution for each elem of arr
    '''
    local_list = []

    if isinstance(rec_list[0], list):
        for each in rec_list:
            local_list.extend(study_case(each, active_line, symbols, is_last, depth))
    else:
        local_list.extend(single_object_case(rec_list[0], symbols, is_last, depth))
        if isinstance(rec_list[1], list):
            local_list.extend(study_case(rec_list[1], active_line, symbols, is_last, depth + 1))

    return local_list



def non_list_case(rec_list, active_line, symbols, depth):
    '''
    solution for the case when input do not containt any lists
    :param rec_list:
        source tree representation
    :param active_line:
        preveious string
    :param symbols:
        default preset of symbols
    :param depth:
        depth of current recursion layer
    :return:
        list representing correct draw for this input
    '''
    local_list = []

    if not isinstance(rec_list, list):
        return single_object_case(rec_list, symbols, True, depth + 1)

    for elem in rec_list[:-1]:
        local_list.extend(study_case(elem, active_line, symbols, False, depth + 1))

    local_list.extend(study_case(rec_list[-1], active_line, symbols, True, depth + 1))

    return local_list


def default_case(rec_list, active_line, symbols, is_last, depth):
    '''
    default case means combination [ non list, list ]
        handle this case
    :param rec_list:
        source tree representation by recursive list
    :param active_line:
        previous string
    :param symbols:
        default preset of symbols
    :param is_last:
        bool representing location in the list of parent
    :param depth:
        int representing layer depth of recursion
    :return:
        returns list representing correct drawing for this part of list
    '''
    loc_solution = []
    loc_solution.extend(single_object_case(rec_list[0], symbols, is_last, depth))
    loc_solution.extend(study_case(rec_list[1], active_line, symbols, is_last, depth + 1))
    return loc_solution


def study_case(rec_list, active_line, symbols, is_last, depth):
    '''
    foo that suppoused to find out what king of preset it got ( { var, list }, { list, list},
    { var, Null }, etc) and call relative case solution
    :param rec_list:
        source tree representation by recursive list
    :param active_line:
        previous string
    :param symbols:
        default preset of symbols
    :param is_last:
        bool representing location in the list of parent
    :param depth:
        int representing layer depth of recursion
    :return:
        returns list representing correct drawing for this part of list
    '''
    res_graph = []

    if isinstance(rec_list, list):
        if len(rec_list) == 0:
            return []

    if isinstance(rec_list, list) and not isinstance(rec_list[0], list) and len(rec_list) == 1:
        res_graph = single_object_case(rec_list[0], symbols, is_last, depth)
    elif not isinstance(rec_list, list):
        res_graph.extend(single_object_case(rec_list, symbols, is_last, depth))
    elif all(isinstance(elem, list) for elem in rec_list):
        for elem in rec_list:
            res_graph.extend(list_case(elem, active_line, symbols, is_last, depth))
    elif not isinstance(rec_list[0], list) and isinstance(rec_list[1], list):
        res_graph.extend(default_case(rec_list, active_line, symbols, is_last, depth))
    elif not all(isinstance(elem, list) for elem in rec_list):
        for elem in rec_list:
            res_graph.extend(single_object_case(elem, symbols, symbols, depth))

    return res_graph



def fix_result_output(result, symbols):
    '''
    this function change output of recursive draw by changing symbols according to
    global rules and preset of symbols
    :param result:
        result of main recursion that containt only correct location of vertexes ( according to 2d map ),
        but content incorrect symbols
    :param symbols:
        default preset of psudo graphic symbols
    :return:
        correct pseudo graphic tree representation
    '''
    last = False
    # index = 4

    max_len = 0
    for each in result:
        if len(each) > max_len:
            max_len = len(each)

    for index in range(max_len):
        for elem in reversed(range(len(result))):

            if isinstance(result[elem], list) and index < len(result[elem]):

                if last and result[elem][index] in symbols and result[elem][index] != symbols[0]:
                    if result[elem][index] == symbols[1]:
                        result[elem][index] = symbols[5]
                    elif result[elem][index] == symbols[2]:
                        result[elem][index] = symbols[3]
                elif last and (result[elem][index] not in symbols or result[elem][index] == symbols[0]):
                    last = False
                elif result[elem][index] == symbols[3] and not last:
                    result[elem][index] = symbols[2]

                if result[elem][index] == symbols[2]:
                    last = True


def main_rec(rec_list: list, symbols: list, depth: bool):
    '''
    root of recursion
        draw tree root at start
        then start recursion of his children
    :param rec_list:
        source tree representation
    :param symbols:
        source symbols that used to draw pseudographic
    :param depth:
        depth of the current layer of recursion
    :return:
        returns string representing the drawn tree
    '''
    res_graph = []
    if rec_list[0]:
        res_graph.append(rec_list[0])
        res_graph.append('\n')
    else:
        res_graph.append(symbols[4])
        res_graph.append(str(symbols[1]) * symbols[0])

    if len(rec_list) > 1:
        res_graph.extend(study_case(rec_list[1], [], symbols, False, depth + 1))




    alpha = []
    inc = 0
    tmp = []
    for a in res_graph:
        if a != '\n':
            tmp.append(a)
        else:
            alpha.append(tmp)
            alpha[-1].append('\n')
            inc += 1
            tmp = []

    fix_result_output(alpha, symbols)

    qwe = ''
    for i in alpha:
        for b in i:
            qwe = qwe + str(b)

    print(qwe)

    return qwe


def render_tree(tree: list = None,
                indent: int = 3, separator: str = ' ') -> str:
    '''
    pseudo graphic rendering of tree

    :param tree:
        source tree represented by recursive list
    :param indent:
        default param representing distance between vertexes
    :param separator:
        default param char that is suppoused to be used as separator
    :return:
        string representing tree
    '''

    symbols = [indent - 2, separator, '└', '├', '─', '│', '>']
    tree = control_input(tree)
    parse_input(tree)
    if len(tree) != 2 or ( isinstance(tree[0], list) and isinstance(tree[1], list) ):
        raise Exception('Invalid tree')

    return main_rec(tree, symbols, 0)
