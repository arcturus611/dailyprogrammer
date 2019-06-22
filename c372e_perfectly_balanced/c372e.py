#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jun 21 21:04:33 2019

@author: arcturus
"""
# DailyProgrammer Challenge 372 [Easy] Output whether a string of x's and y's is perfectly balanced or not
# Caveat: be sure to take care of the empty string case! 

#%% 
from collections import Counter

#%% 
if __name__ == '__main__':
    user_input = input("Please enter the string: ")
    count_compare = Counter(user_input)
    print(count_compare['x']==count_compare['y'])
