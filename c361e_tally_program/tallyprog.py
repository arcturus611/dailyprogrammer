#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 29 17:56:48 2018

@author: arcturus
"""
#%% 
import numpy as np

#%% main 
# r/dailyprogrammer #361
if __name__=='__main__': 
    scores = np.zeros(5)
    encoded_scores = input("Enter the encoded scores: ")
    
    for character in encoded_scores:
        if(character.islower()):
            scores[ord(character)-97]+=1
        else:
            scores[ord(character)-65]-=1
    
    print(scores)