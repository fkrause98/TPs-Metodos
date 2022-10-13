#!/usr/bin/env python3
import pandas as pd

class TestMatrix:
    def __init__(eigenvalues, matrix):
      self.eg = eigenvalues
      self.matrix = matrix

def get_matrices():
    url = "https://ece.uwaterloo.ca/~dwharder/Integer_eigenvalues/Symmetric_5_by_5_singular_matrices/"
    dataframes = pd.read_html(url)
