# -*- coding: utf-8 -*-


class Heap:
    def __init__(self, reverse=False):
        self._reverse = reverse
        
        
    def _lt(self, x, y):
        if not self._reverse:
            return x < y
        else:
            return x > y
            
         
    def _le(self, x, y):
        if not self._reverse:
            return x <= y
        else:
            return x >= y
                 
    
    def _percolate_up(self, heap):
        curr_index = len(heap) - 1
        while curr_index > 0:
            parent_index = (curr_index - 1) // 2
            if self._le(heap[parent_index], heap[curr_index]):
                break
            else:
                tmp = heap[parent_index]
                heap[parent_index] = heap[curr_index]
                heap[curr_index] = tmp
                curr_index = parent_index
    
    
    def _get_min_child(self, heap, item_index):
        left_child = 2*item_index + 1
        if left_child > len(heap) - 1:
            return -1
        
        ret_index = left_child
        right_child = 2*item_index + 2
        if right_child < len(heap) and self._lt(heap[right_child], heap[left_child]):
            ret_index = right_child
            
        return ret_index
   
        
    def _percolate_down(self, heap, item_index):
        curr_index = item_index
        min_child_index = self._get_min_child(heap, curr_index)
        while min_child_index != -1:
            if self._lt(heap[curr_index], heap[min_child_index]):
                break
            else:
                tmp = heap[min_child_index]
                heap[min_child_index] = heap[curr_index]
                heap[curr_index] = tmp
                curr_index = min_child_index
                min_child_index = self._get_min_child(heap, curr_index)
   
        
    def heaplify(self, heap_to_be):
        curr_index = len(heap_to_be) // 2 - 1
        while curr_index >= 0:
            self._percolate_down(heap_to_be, curr_index)
            curr_index -= 1
        
        
    def heappush(self, heap, item):
        heap.append(item)
        # Percolate up the item from the end of the heap.
        self._percolate_up(heap)
        
        
    def heappop(self, heap):
        if not heap:
            raise IndexError('empty heap')
        
        ret = heap[0]
        heap[0] = heap[-1]
        heap.pop()
        
        self._percolate_down(heap, 0)
        
        return ret
        
        
    def heapdelete(self, heap, item_index):
        if item_index < 0 or item_index > len(heap):
            return
        
        heap[item_index] = heap[-1]
        heap.pop()
        
        self._percolate_down(heap, item_index)
        
        return

