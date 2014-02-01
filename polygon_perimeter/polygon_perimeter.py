"""
    Author: ablink4
    Date: 23 Dec 2013
    Description: Daily programming challenge.  See:
        http://www.reddit.com/r/dailyprogrammer/comments/1tixzk/122313_challenge_146_easy_polygon_perimeter/

        This program calculates the perimeter of a polygon with a given number of sides
        and a given circumradius.
"""

import sys
import math

def calc_poly_perim(n, r):            
    if n < 3 or n > 100:
        print("Invalid argument: n must be an integer between 3 and 100.")
        sys.exit()

    if r < 0.01 or r > 100.0:
        print("Invalid argument: r must be an floating point number between 0.01 and 100.0")
        sys.exit()

    # formula for computing side length s in terms of circumradius r
    s = 2 * math.sin(math.pi/n) * r

    perimeter = s * n

    print "{0:.3f}".format(perimeter)

calc_poly_perim(5, 3.7)
calc_poly_perim(100, 1.0)
