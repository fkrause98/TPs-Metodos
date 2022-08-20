import os
from typing import List

class Test:
    def __init__(self, test_list: List[str], test_name: str) -> Test:
        n, m, *links = test_list
        tuple_from_pair = lambda string: (int(string[0]), int(string[2]))
        self.n = n
        self.m = m
        self.links = list(map(tuple_from_pair, links))
        self.name = test_name
    def __str__(self) -> str:
        tuple_to_string = lambda tuple: f"{str(tuple[0])} {str(tuple[1])} \n"
        links = " ".join(list(map(tuple_to_string, self.links)))

        return f"Test instance: {self.name} \n"\
               f"Number of pages: {self.n}, Number of links: {self.m} \n"\
               f"Instance values:\n {links} \n"
    def to_input(self) -> str:
        tuple_to_input = lambda tuple: f"{str(tuple[0])} {str(tuple[1])} \n"
        tuples_as_input = list(map(tuple_to_input, self.links))
        links = " ".join(tuples_as_input)
        return f"{self.n} \n"\
               f"{self.m} \n"\
               f"{links}"\

def read_test(test_path: str, test_name: str) -> Test:
    with open(test_path) as test:
        lines: TextIOWrapper = test.readlines()
        lines = [line.rstrip() for line in lines]
    return Test(lines, test_name)
