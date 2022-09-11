import os, subprocess
import numpy as np
import time
from scipy.sparse import coo_matrix
from typing import List
import random
from pathlib import Path

def create_pair(pair: str):
    i, j = tuple(pair.split(' '))
    return (float(i), float(j))

class Test:
    def __init__(self, test_list: List[str], test_path: str, test_path_original):
        n, m, *links = test_list
        self.n = n
        self.m = m
        self.links = list(map(create_pair, links))
        self.test_path = test_path
        self.test_path_original = test_path_original
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
       tp_bin: str = os.getcwd() + "/tp1"
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

    def solution_file_original(self):
       with open(self.test_path_original + ".out") as out:
           lines = out.readlines()
           p, *x_i = [float(line.rstrip()) for line in lines]
           return (p, x_i)

    def diff(self):
        with open(self.test_path_original + ".out") as out:
           lines = out.readlines()
           p, *x_i = [float(line.rstrip()) for line in lines]
        print(x_i[:10])
        self.solve_with_cpp(p)
        (p_cpp, output) = self.solution_file()
        assert(p == p_cpp)
        diff = [abs(x_i[i] - output[i]) for i in range(len(x_i)) if abs(x_i[i] - output[i]) > 1e-4]
        assert(len(diff) == 0)
        print("Hay diferencia de más de 1e-4 con la catedra? " + str(not(len(diff) == 0)))
        return diff

    def get_A(self, p):
        n = int(self.n)
        W = self.to_sparse_matrix()
        cj_values = [1/sum(col) if sum(col)!=0 else 0 for col in W.T]
        D = np.diag(cj_values)
        WD = np.matmul(W,D)
        z_values = [((1-p)/n)  if sum(col)!=0 else 1/n for col in W.T]
        e_z = np.array([z_values for i in range(n)])
        A = (p*WD) + e_z
        return A

    def diff_solution_with_A_times_x(self):
        p, our_solution = self.solution_file()
        our_solution = np.array(our_solution)
        A = self.get_A(p)
        Ax = np.matmul(A, our_solution)
        return abs(Ax-our_solution)

def read_test(test_path: str, test_path_original) -> Test:
    with open(test_path) as test:
        lines = test.readlines()
        lines = [line.rstrip() for line in lines]
    return Test(lines, test_path, test_path_original)

def time_each():
    tests_path = os.getcwd() + "/tests_catedra_original"
    files = os.listdir(tests_path)
    files.remove('tp1.pdf')
    files.remove('README.txt')
    files.remove('test_nuestro.txt')
    files = [file for file in files if file.endswith(".txt")]
    for file in files:
        print(f"Testing {str(file)}...")
        test = read_test("./tests/" + file, "./tests_catedra_original/" + file)
        test.time_it_cpp()
    return None

def run_each():
    tests_path = os.getcwd() + "/tests_catedra_original"
    files = os.listdir(tests_path)
    files = [file for file in files if file.endswith(".txt")]
    for file in files:
        print(f"Testing {str(file)}...")
        test = read_test("./tests/" + file, "./tests_catedra_original/" + file)
        test.diff()
    return None

def sparse_tests_extra_links():
    random.seed()
    n_list = [50, 100, 200, 300, 500, 1000, 3000]
    sparsiness_list = [95, 97, 99]
    for x in range(5):
        for n in n_list:
            for sparse_percentage in sparsiness_list:
                m = ((100-sparse_percentage)*(n**2))//100
                matrix = [random_ij(n) for _ in range(m)]
                write_test(n, len(matrix), matrix, sparse_percentage, x, "sparse_30")
                for y in range(30*n):
                    matrix.append(random_link_to_important_page(n, 15))
                write_test(n, len(matrix), matrix, sparse_percentage, x, "sparseextra_30")

# def sparse_tests():
#     random.seed()
#     n_list = [50, 100, 200, 300, 500, 1000]
#     sparsiness_list = [95, 97, 99]
#     for x in range(5):
#         for n in n_list:
#             for sparse_percentage in sparsiness_list:
#                 m = ((100-sparse_percentage)*(n**2))//100
#                 matrix = [random_ij(n) for _ in range(m)]
#                 write_test(n, len(matrix), matrix, sparse_percentage, x, "sparse")

def dense_test():
    random.seed()
    n_list = [100, 300]
    sparsiness_list = [50, 75]
    for x in range(5):
        for n in n_list:
            for sparse_percentage in sparsiness_list:
                m = ((100-sparse_percentage)*(n**2))//100
                matrix = [random_ij(n) for _ in range(m)]
                write_test(n, m, matrix, sparse_percentage, x, "density")

def write_test(n, m, matrix, sparse_percentage, test_number, name=""):
    test_path = os.getcwd() + "/our_tests"
    Path(test_path).mkdir(parents=True, exist_ok=True)
    test_file_path = f'{test_path}/{str(n)}_{str(sparse_percentage)}_{str(test_number)}_{str(name)}.txt'
    with open(test_file_path, 'w') as test_file:
        test_file.write(str(n) + '\n')
        test_file.write(str(m) + '\n')
        for (i, j) in matrix:
            test_file.write(f'{str(i)} {str(j)} \n')
    test = read_test(test_file_path, "")
    assert matrix == test.links
    assert n == int(test.n)
    assert m == int(test.m)
    assert test_file_path == test.test_path



def random_ij(n):
    (i, j) = (random.randint(1, n), random.randint(1, n))
    # Try again just in case.
    while i == j:
        (i, j) = (random.randint(1, n), random.randint(1, n))
    return (i, j)

def random_link_to_important_page(n, important_pages_num):
    (i, j) = (random.randint(1, important_pages_num), random.randint(1, n))
    # Try again just in case.
    while i == j:
        (i, j) = (random.randint(1, important_pages_num), random.randint(1, n))
    return (i, j)

def read_test_out(path):
    lines = []
    with open(path) as file:
        for index, line in enumerate(file):
            lines.append((index, float(line)))
    return lines[1:]

def diff_each_with_Ax():
    tests_path = os.getcwd() + "/tests_catedra_original"
    files = os.listdir(tests_path)
    files.remove('tp1.pdf')
    files.remove('README.txt')
    files.remove('test_nuestro.txt')
    files = [file for file in files if file.endswith(".txt")]
    for file in files:
        print(f"Testing {str(file)}...")
        test = read_test("./tests/" + file, "./tests_catedra_original/" + file)
        test.diff()
    return None
