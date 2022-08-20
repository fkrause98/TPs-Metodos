import os

class Test:
    def __init__(self, test_list, test_name):
        n, m, *links = test_list
        tuple_from_pair = lambda string: (int(string[0]), int(string[2]))
        self.n = n
        self.m = m
        self.links = list(map(tuple_from_pair, links))
        self.name = test_name
    def __str__(self):
        return f"Test instance: {self.name} \n"\
               f"Number of pages: {self.n}, Number of links: {self.m} \n"\
               f"Instance values:\n {(self.links)} \n"\

def read_test(test_path, test_name) -> Test:
    with open(test_path) as test:
        lines: TextIOWrapper = test.readlines()
        lines = [line.rstrip() for line in lines]
    return Test(lines, test_name)
