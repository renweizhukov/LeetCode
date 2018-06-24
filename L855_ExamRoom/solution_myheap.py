# This solution is similar to https://leetcode.com/problems/exam-room/discuss/139941/Python-O(log-n)-time-for-both-seat()-and-leave()-with-heapq-and-dicts-Detailed-explanation/147981. The main difference is that we will delete the segments from the heap when they become invalid due to the leave.

class IndexedHeap:
    """This is a simple implementation of a min/max-heap.
    Note that we assume that each item of the heap is a list
    where its last element indicates the index of the item
    in the heap.
    """
    def __init__(self, reverse=False):
        # By default this heap is a min-heap. But if the flag 
        # reverse is True, it will be a max-heap.
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
        """Percolate the last item up to the appropriate 
        position of the heap.
        """
        curr_index = len(heap) - 1
        while curr_index > 0:
            parent_index = (curr_index - 1) // 2
            if self._le(heap[parent_index], heap[curr_index]):
                break
            else:
                tmp = heap[parent_index]
                heap[parent_index] = heap[curr_index]
                heap[curr_index] = tmp        
                # Swap back the indexes of the elements in the heap.
                heap[parent_index][-1] = parent_index
                heap[curr_index][-1] = curr_index
                
                curr_index = parent_index
                
    
    def _get_min_child(self, heap, item_index):
        """Get the index of the minimum child of an item.
        If the item doesn't have any child, we will return -1.
        """
        left_child = 2*item_index + 1
        if left_child > len(heap) - 1:
            return -1
        
        ret_index = left_child
        right_child = 2*item_index + 2
        if right_child < len(heap) and self._lt(heap[right_child], heap[left_child]):
            ret_index = right_child
            
        return ret_index
   
        
    def _percolate_down(self, heap, item_index):
        """Percolate the element at item_index down to the appropriate 
        position of the heap.
        """
        curr_index = item_index
        min_child_index = self._get_min_child(heap, curr_index)
        while min_child_index != -1:
            if self._lt(heap[curr_index], heap[min_child_index]):
                break
            else:
                tmp = heap[min_child_index]
                heap[min_child_index] = heap[curr_index]
                heap[curr_index] = tmp
                # Swap back the indexes of the elements in the heap.
                heap[min_child_index][-1] = min_child_index
                heap[curr_index][-1] = curr_index
                
                curr_index = min_child_index
                min_child_index = self._get_min_child(heap, curr_index)
   
        
    def heaplify(self, heap_to_be):
        """Create a heap in-place from a list."""
        # Initialize the indexes of the elements in the heap.
        for index in range(len(heap_to_be)):
            heap_to_be[index][-1] = index 
        
        curr_index = len(heap_to_be) // 2 - 1
        while curr_index >= 0:
            self._percolate_down(heap_to_be, curr_index)
            curr_index -= 1
        
        
    def heappush(self, heap, item):
        """Push one item into the heap."""
        item[-1] = len(heap)
        heap.append(item)
        # Percolate up the item from the end of the heap.
        self._percolate_up(heap)
        
        
    def heappop(self, heap):
        """Pop the root (i.e., the minimum/maximum item) out of the heap."""
        if not heap:
            raise IndexError('empty heap')
        
        ret = heap[0]
        heap[0] = heap[-1]
        # Reset the index of the root.
        heap[0][-1] = 0
        heap.pop()
        
        self._percolate_down(heap, 0)
        
        return ret
        
        
    def heapdelete(self, heap, item_index):
        """Delete the item at item_index from the heap."""
        if item_index < 0 or item_index >= len(heap):
            return
        
        # Move the last item to item_index.
        heap[item_index] = heap[-1]
        # Reset the index of the item at item_index.
        heap[item_index][-1] = item_index
        # Remove the last item from the heap.
        heap.pop()
        
        self._percolate_down(heap, item_index)
        
        return


class ExamRoom(object):
    def __init__(self, N):
        """
        :type N: int
        """
        self.N = N
        # This max-heap keeps a list of empty segments where the segments
        # are compared firstly with their lengths and then with its start indice
        # if their lengths are the same.
        self.heap = []
        # A dict from the segment start index to the segment
        self.avail_first = {}
        # A dict from the segment end index to the segment
        self.avail_last = {}
        # Create the min-heap helper.
        self.min_h = IndexedHeap()
        # Initially we have one big empty segment [0, N - 1].
        self.put_segment(0, self.N - 1)
        

    def put_segment(self, first, last):
        # Calculate the priority of the segment where the priority is the maximum 
        # closest distance if the new student sits at one seat in the segment.
        if first == 0 or last == self.N - 1:
            # If the empty segment includes either 0 or N - 1
            priority = last - first
        else:
            priority = (last - first) // 2

        # segment[0] = priority;
        # segment[1] = the starting seat of the segment
        # segment[2] = the ending seat of the segment
        # segment[3] = the index of this segment in the heap.
        # Note that:
        # (1) Take the negative of priority because we want to use a min-heap.
        # (2) The segment index will be set in IndexedHeap.heappush().
        segment = [-priority, first, last, -1]

        self.avail_first[first] = segment
        self.avail_last[last] = segment

        self.min_h.heappush(self.heap, segment)

    def seat(self):
        """
        :rtype: int
        """
        # Get the segment with the maximum length.
        _, first, last, _ = self.min_h.heappop(self.heap)
        self.avail_first.pop(first)
        self.avail_last.pop(last)

        if first == 0:
            # Seat the student at 0.
            ret = 0
            if first != last:
                self.put_segment(first + 1, last)
        elif last == self.N - 1:
            # Seat the student at N - 1.
            ret = last
            if first != last:
                self.put_segment(first, last - 1)
        else:
            # Seat the student in the middle of the segment.
            ret = first + (last - first) // 2
            
            if ret > first:
                self.put_segment(first, ret - 1)
            if ret < last:
                self.put_segment(ret + 1, last)

        return ret

    def leave(self, p):
        """
        :type p: int
        :rtype: void
        """
        # Removing p at least leads to a hole at p.
        first = p
        last = p

        # Check if we need to delete the left and right segments 
        # neighboring p.
        left = p - 1
        right = p + 1

        if left >= 0 and left in self.avail_last:
            # Delete the left segment if it exists. Note that we don't 
            # delete the segment from the map self.avail_first since 
            # its value will be overwritten in self.put_segment().
            segment_left = self.avail_last.pop(left)
            first = segment_left[1]
            # Instead of marking the segment as invalid, we delete 
            # the segment from the heap.
            self.min_h.heapdelete(self.heap, segment_left[3])
            
        if right < self.N and right in self.avail_first:
            # Delete the right segment if it exists. Note that we don't 
            # delete the segment from the map self.avail_last since 
            # its value will be overwritten in self.put_segment(). 
            segment_right = self.avail_first.pop(right)
            last = segment_right[2]
            # Instead of marking the segment as invalid, we delete 
            # the segment from the heap.
            self.min_h.heapdelete(self.heap, segment_right[3])

        # Push the new segment into the heap.
        self.put_segment(first, last)
