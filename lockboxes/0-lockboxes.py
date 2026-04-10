#!/usr/bin/python3
"""Lockboxes challenge"""


def canUnlockAll(boxes):
    """Determines if all boxes can be opened"""
    unlocked = set([0])
    keys = set(boxes[0])

    while keys:
        key = keys.pop()
        if key < len(boxes) and key not in unlocked:
            unlocked.add(key)
            keys.update(boxes[key])

    return len(unlocked) == len(boxes)