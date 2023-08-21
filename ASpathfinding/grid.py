import random

from node import Node

class Grid:
    def __init__(self, size_x, size_y, set_type, user_grid):
        self.size_x = size_x
        self.size_y = size_y
        if(set_type == True):
            self.auto_set()
        else:
            self.manual_set(user_grid)

    def auto_set(self):
        self.grid = []
        
    def manual_set(self, user_grid):
        pass

    def print_grid(self):
        for row in self.grid:
            print()
            for cell in row:
                print(cell.mode, end=" ")
        print()

test = Grid(10, 10, True, [])
test.print_grid()