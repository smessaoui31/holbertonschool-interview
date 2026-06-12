#!/usr/bin/python3
"""Reads stdin line by line and computes log metrics."""
import sys
import re

VALID_CODES = {200, 301, 400, 401, 403, 404, 405, 500}
PATTERN = re.compile(
    r'^\d+\.\d+\.\d+\.\d+ - \[.+\] "GET /projects/260 HTTP/1\.1" (\d+) (\d+)$'
)

def print_stats(total_size, status_counts):
    """Print accumulated metrics to stdout."""
    print("File size: {}".format(total_size))
    for code in sorted(status_counts):
        print("{}: {}".format(code, status_counts[code]))


if __name__ == '__main__':
    total_size = 0
    status_counts = {}
    line_count = 0
    printed_last = False

    try:
        for line in sys.stdin:
            m = PATTERN.match(line.rstrip('\r\n'))
            if m:
                status = int(m.group(1))
                total_size += int(m.group(2))
                if status in VALID_CODES:
                    status_counts[status] = status_counts.get(status, 0) + 1
            line_count += 1
            if line_count % 10 == 0:
                print_stats(total_size, status_counts)
                printed_last = True
            else:
                printed_last = False
    except KeyboardInterrupt:
        print_stats(total_size, status_counts)
        raise

    if not printed_last:
        print_stats(total_size, status_counts)
