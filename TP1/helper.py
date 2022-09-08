import os, subprocess
import numpy as np
import time
from scipy.sparse import coo_matrix
from typing import List

def create_pair(pair: str):
    i, j = tuple(pair.split(' '))
    return (float(i), float(j))

class Test:
    def __init__(self, test_list: List[str], test_name: str, test_path: str):
        n, m, *links = test_list
        self.n = n
        self.m = m
        self.links = list(map(create_pair, links))
        self.name = test_name
        self.test_path = test_path
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

    def to_sparse_matrix(self):
        rows = []
        columns = []
        vals = []
        for (i, j) in self.links:
            rows.append(j-1)
            columns.append(i-1)
            vals.append(1.0)
        matrix = coo_matrix((vals, (rows, columns)), shape=(int(self.n), int(self.n))).toarray()
        return matrix

    def solve_with_python(self, p: float):
        n = int(self.n)
        W = self.to_sparse_matrix()
        cj_values = [1/sum(col) if sum(col)!=0 else 0 for col in W.T ]
        D = np.diag(cj_values)
        WD = np.matmul(W,D)
        Id = np.identity(n)
        final_matrix = (Id - (p*WD))
        solution = np.linalg.solve(final_matrix, np.ones(n))
        normalized_solution = solution / np.sum(solution)
        return normalized_solution

    def solve_with_cpp(self, p: float):
       tp_bin: str = os.getcwd() + "/src/tp1"
       bin_process = subprocess.run([tp_bin, self.test_path, str(p)], input=self.to_input(), capture_output=True, text=True)
       output = bin_process.stdout
       return [float(x) for x in output.split('\n') if x != '']

    def time_it_cpp(self):
        p, _ = self.solution_file()
        start = time.time()
        output = self.solve_with_cpp(p)
        end = time.time()
        print(f"Time elapsed for {self.test_path}: {end-start}")
        return output

    def solution_file(self):
       with open(self.test_path + ".out") as out:
           lines = out.readlines()
           p, *x_i = [float(line.rstrip()) for line in lines]
           return (p, x_i)


def read_test(test_path: str, test_name: str) -> Test:
    with open(test_path) as test:
        lines = test.readlines()
        lines = [line.rstrip() for line in lines]
    return Test(lines, test_name, test_path)

def page_rank(test_path: str, test_name: str, p: float):
       test: Test = read_test(test_path, test_name)
       tp_bin: str = os.getcwd() + "/src/tp1"
       bin_process = subprocess.run([tp_bin, test_path, str(p)], input=test.to_input(), capture_output=True, text=True)
       output = bin_process.stdout
       return output
def time_each():
    tests_path = os.getcwd() + "/tests"
    files = os.listdir(tests_path)
    files.remove('tp1.pdf')
    files.remove('README.txt')
    files.remove('test_nuestro.txt')
    files = [file for file in files if file.endswith(".txt")]
    for file in files:
        test = read_test(tests_path + "/" + file, file)
        output = test.time_it_cpp()
        print(output)
    return None
