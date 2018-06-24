#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from heap import Heap

## min-heap

minh = Heap()
heap = [9, 5, 6, 2, 3, 4]

minh.heaplify(heap)

print(heap)
minh.heapdelete(heap, 2)
print(heap)

print(minh.heappop(heap))
print(minh.heappop(heap))

minh.heappush(heap, 7)

print(minh.heappop(heap))
print(minh.heappop(heap))
print(minh.heappop(heap))
print(minh.heappop(heap))

try:
    print(minh.heappop(heap))
except IndexError as e:
    print(str(e))
    
## min-heap but each item is a two-element list

heap = [[9, 0], [5, 1], [6, 1], [2, 3], [3, 2]]

minh.heaplify(heap)

print(minh.heappop(heap))
print(minh.heappop(heap))

minh.heappush(heap, [5, 0])

print(minh.heappop(heap))
print(minh.heappop(heap))
print(minh.heappop(heap))
print(minh.heappop(heap))

try:
    print(minh.heappop(heap))
except IndexError as e:
    print(str(e))

# max-heap

maxh = Heap(reverse=True)
heap = [9, 5, 6, 2, 3]

maxh.heaplify(heap)

print(maxh.heappop(heap))
print(maxh.heappop(heap))

maxh.heappush(heap, 7)

print(maxh.heappop(heap))
print(maxh.heappop(heap))
print(maxh.heappop(heap))
print(maxh.heappop(heap))

try:
    print(maxh.heappop(heap))
except IndexError as e:
    print(str(e))

## max-heap but each item is a two-element list

heap = [[9, 0], [5, 1], [6, 1], [2, 3], [3, 2]]

maxh.heaplify(heap)

print(maxh.heappop(heap))
print(maxh.heappop(heap))

maxh.heappush(heap, [5, 0])

print(maxh.heappop(heap))
print(maxh.heappop(heap))
print(maxh.heappop(heap))
print(maxh.heappop(heap))

try:
    print(maxh.heappop(heap))
except IndexError as e:
    print(str(e))
