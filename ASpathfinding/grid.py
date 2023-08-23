import random

from node import Node

# todo:
# better maze?
# pos[]pos[]
# better spawning
# manual set

class Grid:
    def __init__(self, size_x, size_y, set_type, user_grid):
        self.size_x = size_x
        self.size_y = size_y
        self.open = []
        self.done = []
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
        start_x, start_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 1, 2)) # cross only atm
        target_x, target_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 1, 2)) # cross only atm

        self.start = [start_x, start_y] # possibily useless
        self.target = [target_x, target_y] # possibily useless

        self.grid[start_y][start_x] = Node(2)
        self.grid[target_y][target_x] = Node(3)
        self.grid[start_y][start_x].find_h([start_x, start_y], [target_x, target_y])
        self.grid[start_y][start_x].find_f()
        self.open.append([[start_x, start_y], self.grid[start_y][start_x].f_cost])
        
    def manual_set(self, user_grid):
        pass

    def a_star(self):
        while True:
            self.evaluate(self.open[0][0])
            self.open.sort(key = lambda list : list[-1])
            if self.grid[self.open[0][0][0]][self.open[0][0][1]].h_cost == 0:
                return self.backtrack()

    def evaluate(self, pos):
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
                if [dir_x, dir_y] not in self.open and self.grid[dir_x][dir_y].done == False:
                    self.open.append([[dir_x, dir_y], self.grid[dir_x][dir_y].f_cost])
        self.open.remove([pos[0], pos[1]])
        self.grid[pos[0]][pos[1]].done = True

    def backtrack(self):
        pass

    def print_grid(self):
        for row in self.grid:
            print()
            for cell in row:
                print(cell.mode, end=" ")
        print()

test = Grid(10, 10, True, [])
test.print_grid()