#!/usr/bin/python3
"""Minimum operations to reach n H characters"""


def minOperations(n):
    """Returns fewest operations to get exactly n H's, or 0 if impossible"""
    if n < 2:
        return 0

    ops = 0
    divisor = 2

    while divisor * divisor <= n:
        while n % divisor == 0:
            ops += divisor
            n //= divisor
        divisor += 1

    if n > 1:
        ops += n

    return ops
