import random

from node import Node

class Grid:
    def __init__(self, size_x, size_y, set_type, user_grid):
        self.size_x = size_x
        self.size_y = size_y
        self.open = []
        if(set_type == True):
            self.auto_set()
        else:
            self.manual_set(user_grid)

    def auto_set(self):
        self.grid = []
        for y in range(self.size_y):
            row = []
            for x in range(self.size_x):
                if x == 0 or y == 0 or x == self.size_x - 1 or y == self.size_y - 1 or (x % 2 == 0 and y % 2 == 0):
                    mode = 1
                else:
                    mode = 0
                row.append(Node(mode))
            self.grid.append(row)
        self.set_start_and_target()

    def set_start_and_target(self):
        start_x, start_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 1))
        target_x, target_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 1))

        self.grid[start_y][start_x] = Node(2)
        self.grid[target_y][target_x] = Node(3)
        self.grid[target_y][target_x].h_cost = 0

        self.start = [start_x, start_y] # possibily useless
        self.target = [target_x, target_y] # possibily useless
        self.open.append([start_x, start_y])
        
    def manual_set(self, user_grid):
        pass

    def cal_neighbours(self, pos):
        directions = [[1,0],[0,1],[-1,0],[0,-1]]
        for dir_x, dir_y in directions:
            dir_x += pos[0]
            dir_y += pos[1]
            if self.grid[dir_x][dir_y].mode != 1:
                if self.grid[dir_x][dir_y].h_cost is None:
                    self.grid[dir_x][dir_y].find_h([dir_x, dir_y], self.target)
                if self.grid[dir_x][dir_y].g_cost == 0 or self.grid[dir_x][dir_y].g_cost > self.grid[pos[0]][pos[1]].g_cost + 1:
                    self.grid[dir_x][dir_y].g_cost = self.grid[pos[0]][pos[1]].g_cost + 1
                    self.grid[dir_x][dir_y].source = [pos[0], pos[1]]
                    self.grid[dir_x][dir_y].find_f()

                
        pass

    def print_grid(self):
        for row in self.grid:
            print()
            for cell in row:
                print(cell.mode, end=" ")
        print()

test = Grid(10, 10, True, [])
test.print_grid()