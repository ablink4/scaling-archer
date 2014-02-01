"""
    Author: ablink4
    Date: 30 Dec 2013
    Description: Daily programming challenge.  See:
        http://www.reddit.com/r/dailyprogrammer/comments/1dx3wj/050813_challenge_123_intermediate_synchronizing/

        This program determines if the number of days in a given number of julian years and lunar months are the same
        The problem defines a leap year as being every 4 years only, and a lunar month as being 29.53059 days.
"""

import math

def calendar_sync(M, N):

    lunar_days = int(math.floor(29.53059 * N))

    # problem defines a leap year as every four years only
    julian_days = (M - (M/4))*365 + (M/4)*366

    if lunar_days == julian_days:
        print lunar_days
    else:
        print '0'
    
    

calendar_sync(38, 470)
calendar_sync(114, 2664)
calendar_sync(30, 82)
