#!/usr/bin/env python3

paper_quotations = {
    'A': 1,
    'B': 4,
    'C': 1,
    'D': 4,
    'E': 2,
    'F': 1,
    'G': 3,
    'H': 5,
    'I': 6,
}

# h papers published at least h times
# 8: 1
# 6: 2
# 5: 3
# 4: 4
# 2: 5
# 1: 6

# naive approach: successive filtering
def h_index(pqs):
    h = 0
    while len(pqs) > h:
        pqs = {p: q for p, q in pqs.items() if q > h}
        h += 1
    return h

print(h_index(paper_quotations))

# optimized: expecting sorted array
def h_index_sorted(quotations):
    h, i = 0, 0
    while len(quotations) - i >= quotations[i]:
        h = quotations[i]
        i += 1
    return h

print(h_index_sorted(sorted([q for q in paper_quotations.values()])))
