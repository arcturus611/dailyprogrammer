#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jun 23 16:29:16 2019

@author: arcturus
"""
def fit2(X, Y, x, y):
    return max(fit1(X, Y, x, y), fit1(X, Y, y, x))

def fit1(X, Y, x, y):
    return (X//x)*(Y//y)

def main():
    X, Y, x, y = map(int, input("Please enter values of X, Y, x, and y: ").split())
    print("The number of crates as per FIT 1 is", fit1(X, Y, x, y))
    print("The number of crates as per FIT 2 is", fit2(X, Y, x, y))
    return 

if __name__=='__main__':
    main()