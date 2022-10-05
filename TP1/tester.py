#!/usr/bin/env python3
import time
import linecache
import os
import subprocess
class OurTest:
    def __init__(self, path, n, m, sparsiness, number, p, name):
        self.n = n
        self.m = m
        self.sparsiness = sparsiness
        self.number = number
        self.p = p
        self.time = 0
        self.path = os.path.abspath(path)
        self.name = name

    def run(self):
       print(f"Corriendo test: {self.path}")
       tp_bin: str = "./tp1"
       start = time.time()
       bin_process = subprocess.run([tp_bin, self.path, str(self.p)], capture_output=True, text=True)
       end = time.time()
       output = bin_process.stdout
       # Check the file exists after running.
       assert(os.path.isfile(self.path + ".out"))
       print(f"Tiempo tardado en correr {self.path}: {end-start}")
       self.time = end-start
       self.to_csv()
       return

    def to_csv(self):
        to_write = f"{self.n},{self.m},{self.sparsiness},{self.number},{self.p},{self.time},{self.name}\n"
        with open("./results.csv", 'a') as csv:
            csv.write(to_write)
        return

def create_test(path, p):
    assert(path.endswith('txt'))
    assert(os.path.exists(path))
    assert(p in [.3, .5, .7, .9])
    file_name = path.split('/')[-1]
    print(file_name)
    [n, sparsiness, number, name] = file_name[:-4].split('_')
    m = int(linecache.getline(path, 2))
    assert(n in ['50', '100', '200', '300', '500', '1000', '3000'])
    assert(int(number) in range(10))
    # assert(check_m_is_right(m, int(n), int(sparsiness)))
    return OurTest(path, int(n), m, int(sparsiness), int(number), p, name)

def check_m_is_right(m, n, sparsiness):
    print(m)
    links = (((n**2)*(100-sparsiness))//100)
    return (m == (links + 15*n)) or (m == links) or (m == (links + 30*n))


def test_p_point_x(x):
    assert(x in [0.3, 0.5, 0.7, 0.9])
    path = os.getcwd()+f'/our_tests/{x}/'
    for file in os.listdir(path):
        if file.endswith('txt'):
            test = create_test(path + file, x)
            test.run()

def run_our_tests():
    p_values = [0.3, 0.5, 0.7, 0.9]
    for p in p_values:
        test_p_point_x(p)
