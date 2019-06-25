#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 24 19:58:33 2019

@author: arcturus
"""
def main():
    x1, x2, x3 = map(int, input("Enter the decimal values of your colours ").split())
    h1 = format(x1, '02x').upper()
    h2 = format(x2, '02x').upper()
    h3 = format(x3, '02x').upper()
    hex_colour = '#'+h1+h2+h3
    print("The hex version is:", hex_colour)
    
if __name__ == '__main__': 
    main()