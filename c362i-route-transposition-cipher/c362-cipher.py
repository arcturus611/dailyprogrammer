#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May 30 16:56:19 2018

@author: arcturus
"""

import numpy as np

#%% 
def create_matrix(input_str, r, c):
    input_list_str = list(input_str.upper())
    input_matrix = np.ndarray((r, c))
    for i in np.arange(r): 
        for j in np.arange(c):
            input_matrix[i][j] = ord('X')
    k = 0
    for i in np.arange(r): 
        for j in np.arange(c):
            if (k < len(input_list_str)):
                while (input_list_str[k].isalpha()==0):
                    k = k+1
                    if (k == len(input_list_str)):
                        return input_matrix
                input_matrix[i][j] = ord(input_list_str[k].upper())
                k = k+1          
            
    return input_matrix

#%% test created matrix
def test_created_matrix(input_mat, r, c):
    for i in np.arange(r):
        print('\n')
        for j in np.arange(c):
            print([chr(int(input_mat[i][j])), ])


#%% 
def spiralizer(mat, r, c):
    num_layers = int(np.ceil(r/2))
    encoded_numbers = []
    for i in np.arange(num_layers):
        for j in np.arange(4):
            if (mat.size!=0):
                mat = np.rot90(mat)
                encoded_numbers = np.concatenate((encoded_numbers, mat[0, :]))
                mat = np.delete(mat, 0, 0)
    return encoded_numbers

#%% 
def alphabetize(arr):
    mycode = ''.join(chr(int(arr[i])) for i in np.arange(len(arr)))
    return mycode
#%% 
if __name__ == '__main__':
    r = 3
    c = 9
    created_matrix = create_matrix("We are discovered. Flee at once!!", r, c)
    encoded_numbers = spiralizer(created_matrix, r, c)
    final_code = alphabetize(encoded_numbers)
    print(final_code)