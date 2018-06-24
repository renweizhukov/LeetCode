# Copied from https://leetcode.com/problems/exam-room/discuss/139941/Python-O(log-n)-time-for-both-seat()-and-leave()-with-heapq-and-dicts-Detailed-explanation/147981

from heapq import heappop, heappush

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
        # Initially we have one big empty segment [0, N - 1].
        self.put_segment(0, self.N - 1)

    def put_segment(self, first, last):
        # Calculate the priority of the segment.
        if first == 0 or last == self.N - 1:
            # If the empty segment includes either 0 or N - 1
            priority = last - first
        else:
            priority = (last - first) // 2

        # Take the negative of priority because heapq only supports min-heap.
        segment = [-priority, first, last, True]

        self.avail_first[first] = segment
        self.avail_last[last] = segment

        heappush(self.heap, segment)

    def seat(self):
        """
        :rtype: int
        """
        # Get the first valid segment with the maximum length.
        while True:
            _, first, last, is_valid = heappop(self.heap)

            if is_valid:
                self.avail_first.pop(first)
                self.avail_last.pop(last)
                break

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

        # Check if we need to mark the left and right segments 
        # neighboring p as invalid.
        left = p - 1
        right = p + 1

        if left >= 0 and left in self.avail_last:
            # Mark the left segment as invalid if it exists.
            segment_left = self.avail_last.pop(left)
            segment_left[3] = False
            first = segment_left[1]

        if right < self.N and right in self.avail_first:
            # Mark the right segment as invalid if it exists.
            segment_right = self.avail_first.pop(right)
            segment_right[3] = False
            last = segment_right[2]

        # Push the new segment into the heap.
        self.put_segment(first, last)
