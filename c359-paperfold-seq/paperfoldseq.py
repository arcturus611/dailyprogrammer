#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May  1 15:39:33 2018

@author: arcturus
"""

    #%% 
    def str_rev(inp_str):
        rev_str = inp_str[::-1]
        return rev_str
    
    #%%
    def str_neg(inp_str):
        neg_str = ''.join('1' if x=='0' else '0' for x in inp_str)
        return neg_str
    
    #%%
    def paperfolding_seq(user_input):
        curr_str = '1'
        for i in range(user_input-1):
            curr_str = ''.join([curr_str, '1', str_rev(str_neg(curr_str))])
        return curr_str
    
    #%%
    if __name__=='__main__':
        user_input = 8
        print(paperfolding_seq(user_input))