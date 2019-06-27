#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun 26 17:46:01 2019

@author: arcturus
"""
import numpy as np

def euc_dist(a, b):
    x = np.sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2)
    return x

def get_coords(c):
    c_coords = []
    
    if (c=='.'):
        c_coords.append(3)
        c_coords.append(0)
    elif (c=='0'):
        c_coords.append(3)
        c_coords.append(1)
    else: 
        c_coords.append(np.floor((int(c) - 1)/3))
        c_coords.append((int(c) - 1)%3)
        
    return c_coords

def compute_distance(str):
    x = 0
    prev_pos = 0
    curr_pos = 1
    le = len(str)
    
    while(curr_pos<le):
        prev = str[prev_pos]
        curr = str[curr_pos]
        
        prev_coords = get_coords(prev)    
        curr_coords = get_coords(curr)
                
        x = x + euc_dist(prev_coords, curr_coords)
        
        curr_pos = curr_pos + 1
        prev_pos = prev_pos + 1
        
    return x

def main():
    ip_add = input("Enter the IP address: ")
    dist = compute_distance(ip_add)
    print("The total distance his fingers travel is (in cms):", dist)
    return 

if __name__ == '__main__':
    main()