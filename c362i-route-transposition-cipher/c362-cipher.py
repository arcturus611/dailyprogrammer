#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May 30 16:56:19 2018

@author: arcturus
"""

import numpy as np

#%% 
def create_matrix(input_str, r, c):
    input_upper_chars = [char.upper() for char in input_str if char.isalpha()]
    input_matrix = np.ndarray((r, c))
    for i in np.arange(r): 
        for j in np.arange(c):
            input_matrix[i][j] = ord('X')
    
    for k in np.arange(len(input_upper_chars)):
        i = np.floor_divide(k, c)
        j = np.remainder(k, c)
        input_matrix[i][j] = ord(input_upper_chars[k])
           
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
    r = 12
    c = 4
    input_str = "For lunch let's have peanut-butter and bologna sandwiches"
    created_matrix = create_matrix(input_str, r, c)
    encoded_numbers = spiralizer(created_matrix, r, c)
    final_code = alphabetize(encoded_numbers)
    print("The encoded string for \"{}\" is {}".format(input_str, final_code))