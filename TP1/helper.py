import os
from typing import List

def create_pair(pair: str):
    i, j = tuple(pair.split(' '))
    return (float(i), float(j))

class Test:
    def __init__(self, test_list: List[str], test_name: str):
        n, m, *links = test_list
        self.n = n
        self.m = m
        self.links = list(map(create_pair, links))
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
        lines = test.readlines()
        lines = [line.rstrip() for line in lines]
    return Test(lines, test_name)

def page_rank(test_path: str, test_name: str):
       test: Test = read_test(test_path, test_name)
       return 1
