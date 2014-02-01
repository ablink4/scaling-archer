"""
    Author: ablink4
    Date: 23 Dec 2013
    Description: Daily programming challenge.  See:
        http://www.reddit.com/r/dailyprogrammer/comments/1t0r09/121613_challenge_145_easy_tree_generation/

        This program generates an ASCII-text christmas tree, with centered output.
"""


import sys

def christmas_tree_gen():
    param_str = raw_input("Enter parameters (format: \"n t l\" where n is the width of the base of the tree, t is the character for the tree's trunk, and l is the character for the tree's leaves:  ")
    params = param_str.split()

    if len(params) != 3:
        print("Wrong number of parameters, format: \"n t l\" where n is the width of the base of the tree, t is the character for the tree base, and l is the character for the tree's leaves")
        sys.exit()

    n = int(params[0])    
    t = params[1]
    l = params[2]

    # sanity check parameters

    # problem defines n having range of 3-21
    if n < 3 or n > 21:
        print("Parameter n out of range.  Valid range is 3-21, inclusive.")
        sys.exit()
    if n % 2 <> 1:
        print("Error: parameter n must be odd.")
        sys.exit()
    if len(t) <> 1:
        print("Error: Parameter t must be 1 character long.")
        sys.exit()
    if len(l) <> 1:
        print("Error: Parameter l must be 1 character long.")
        sys.exit()

    i = 1
    while i <= n:
        # pad with whitespace on the left to center the characters for each tree level
        print ' '*((n-i)/2) + l*i

        # each new tree level is 2 characters longer than the previous
        i = i + 2
        
    #print the tree trunk - always length 3 by problem definition
    print ' '*((n-3)/2) + t*3

christmas_tree_gen()
    
    
        
