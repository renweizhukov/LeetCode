class ExamRoom:

    def __init__(self, N):
        """
        :type N: int
        """
        self._cnt_seats = N
        # A dict where key is the index of the taken seat and
        # the value is a list of left and right neighbors.
        self._seated = {}
        
    def _set_selected_seat(self, seat, left_neighbor, right_neighbor, dist):
        return seat, [left_neighbor, right_neighbor], dist

    def seat(self):
        """
        :rtype: int
        """
        if not self._seated:
            # No seat has been taken, so take seat 0.
            self._seated[0] = [-1, -1]
            return 0
        
        # Initialize the selected seat and its neighbors to -1.
        selected_seat = -1
        selected_seat_neighbors = [-1, -1]
        max_dist = 0
        
        # Check the right-hand side of every taken seat and find
        # the seat which can maximize the closest distance.
        for seat, neighbors in self._seated.items():
            if neighbors[0] == -1:
                # This is the left-most taken seat, so also check its
                # left-hand side.
                if seat >= max_dist:
                    selected_seat, selected_seat_neighbors, max_dist = \
                        self._set_selected_seat(0, -1, seat, seat)
            
            # Check the right-hand side.
            if neighbors[1] == -1:
                # This is the right-most taken seat.
                dist = self._cnt_seats - 1 - seat
                if dist > max_dist:
                    selected_seat, selected_seat_neighbors, max_dist = \
                        self._set_selected_seat(self._cnt_seats - 1, 
                                                seat, 
                                                -1, 
                                                dist)
            else:
                dist = (neighbors[1] - seat)//2
                if dist > max_dist or (dist == max_dist and seat + dist < selected_seat):
                    selected_seat, selected_seat_neighbors, max_dist = \
                        self._set_selected_seat(seat + dist, 
                                                seat, 
                                                neighbors[1], 
                                                dist)
        
        # In case that all the seats have been taken, return -1.
        if selected_seat != self._cnt_seats:
            self._seated[selected_seat] = selected_seat_neighbors
            
            # Update the right neighbor of the left neighboring taken seat 
            # if it exists.
            if selected_seat_neighbors[0] != -1:
                self._seated[selected_seat_neighbors[0]][1] = selected_seat
            # Update the left neighbor of the right neighboring taken seat 
            # if it exists.
            if selected_seat_neighbors[1] != -1:
                self._seated[selected_seat_neighbors[1]][0] = selected_seat
            
        return selected_seat
        

    def leave(self, p):
        """
        :type p: int
        :rtype: void
        """
        left_neighbor = self._seated[p][0]
        right_neighbor = self._seated[p][1]
        
        # Update the right neighbor of the left neighboring taken seat 
        # if it exists.
        if left_neighbor != -1:
            self._seated[left_neighbor][1] = right_neighbor
        # Update the left neighbor of the right neighboring taken seat 
        # if it exists.
        if right_neighbor != -1:
            self._seated[right_neighbor][0] = left_neighbor
            
        self._seated.pop(p, None)
        

# Your ExamRoom object will be instantiated and called as such:
# obj = ExamRoom(N)
# param_1 = obj.seat()
# obj.leave(p)
