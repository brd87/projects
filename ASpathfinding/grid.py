import random

from node import Node

# todo:
# better_maze + better_spawning? :: inprogress
# pos[]pos[] :: done
# manual_set + gui :: inprogress

class Grid:
    def __init__(self, size_x, size_y, c_wall, c_sapce, c_start, c_end, c_path):
        self.directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        self.size_x = size_x
        self.size_y = size_y
        self.open = []
        self.grid = []

        self.c_wall = c_wall
        self.c_sapce = c_sapce
        self.c_start = c_start
        self.c_end = c_end
        self.c_path = c_path

        self.make_new()

    def make_new(self):
        self.open.clear()
        self.grid.clear()
        for y in range(self.size_y):
            row = []
            for x in range(self.size_x):
                if x == 0 or y == 0 or x == self.size_x - 1 or y == self.size_y - 1:
                    mode, color = 0, self.c_wall
                else:
                    mode, color = 1, self.c_sapce
                row.append(Node(mode, color))
            self.grid.append(row)

    def setting(self, set_type, user_grid ):
        if(set_type == True):
            self.auto_set(1, 1)
            self.set_start_and_target()
        else:
            self.manual_set(user_grid)


    def auto_set(self, x, y):
        self.grid[y][x].mode = 1
        self.grid[y][x].color = self.c_sapce

        rand_directions = self.directions
        random.shuffle(rand_directions)

        for dir_x, dir_y in rand_directions:
            new_x, new_y = x + dir_x * 2, y + dir_y * 2
            if 0 < new_x < self.size_x - 1 and 0 < new_y < self.size_y - 1 and self.grid[new_y][new_x].mode == 1:
                up_x, up_y = x + (dir_x // 2)*(-1), y + (dir_y // 2)*(-1)
                self.grid[up_y][up_x].mode = 0
                self.grid[up_y][up_x].color = self.c_wall
                self.auto_set(new_x, new_y)
        

    def set_start_and_target(self):
        start_x, start_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 2))
        target_x, target_y = random.choice(range(1, self.size_x - 1, 2)), random.choice(range(1, self.size_y - 2))

        self.target = [target_x, target_y]

        self.grid[start_y][start_x] = Node(2, self.c_start)
        self.grid[target_y][target_x] = Node(3, self.c_end)
        self.grid[start_y][start_x].find_h([start_y, start_x], [target_y, target_x])
        self.grid[start_y][start_x].find_f()
        self.open.append([[start_y, start_x], self.grid[start_y][start_x].f_cost])

        for dir_x, dir_y in self.directions:
            if 0 < start_y + dir_y < self.size_y - 1 and 0 < start_x + dir_x < self.size_x - 1:
                self.grid[start_y + dir_y][start_x + dir_x].mode = 1
                self.grid[start_y + dir_y][start_x + dir_x].color = self.c_sapce
            if 0 < target_y + dir_y < self.size_y - 1 and 0 < target_x + dir_x < self.size_x - 1:
                self.grid[target_y + dir_y][target_x + dir_x].mode = 1
                self.grid[target_y + dir_y][target_x + dir_x].color = self.c_sapce
        

    def manual_set(self, user_grid):
        pass


    def a_star(self):
        while True:
            self.evaluate(self.open[0][0])
            self.open.sort(key = lambda list : list[-1])
            if len(self.open) == 0:
                return print("unsolvable")
            if self.grid[self.open[0][0][0]][self.open[0][0][1]].h_cost == 0:
                return self.backtrack()
            

    def evaluate(self, pos):
        for dir_x, dir_y in self.directions:
            dir_x += pos[1]
            dir_y += pos[0]
            if self.grid[dir_y][dir_x].mode != 0: #here
                if self.grid[dir_y][dir_x].h_cost is None:
                    self.grid[dir_y][dir_x].find_h([dir_x, dir_y], self.target)
                if self.grid[dir_y][dir_x].g_cost == 0 or self.grid[dir_y][dir_x].g_cost > self.grid[pos[0]][pos[1]].g_cost + 1:
                    self.grid[dir_y][dir_x].g_cost = self.grid[pos[0]][pos[1]].g_cost + 1
                    self.grid[dir_y][dir_x].source = pos
                    self.grid[dir_y][dir_x].find_f()
                if [dir_y, dir_x] not in self.open and self.grid[dir_y][dir_x].done == False:
                    self.open.append([[dir_y, dir_x], self.grid[dir_y][dir_x].f_cost])
        self.open.pop(0)
        self.grid[pos[0]][pos[1]].done = True


    def backtrack(self):
        y, x = self.open[0][0]
        y, x = self.grid[y][x].source
        while True:
            if self.grid[y][x].mode == 2:
                break
            self.grid[y][x].mode = 4
            self.grid[y][x].color = self.c_path
            #self.print_grid()
            y, x = self.grid[y][x].source


    def make_tile(self, pos, mode, color):
        if 0 < pos[0] < self.size_y - 1 and 0 < pos[1] < self.size_x - 1:
            self.grid[pos[0]][pos[1]].mode = mode
            self.grid[pos[0]][pos[1]].solor = color
            print("tile changed")


    def print_grid(self):
        for row in self.grid:
            print()
            for cell in row:
                print(cell.mode, end=" ")
        print()

# c_black = (0, 0, 0) # 0-wall
# c_white = (255, 255, 255) # 1-space
# c_green = (0, 255, 0) # 2-start
# c_red = (255, 0, 0) # 3-target
# c_yellow = (255, 255, 0) # 4-path
# test = Grid(22, 22, c_black, c_white, c_green, c_red, c_yellow)
# test.setting(True, None)
# test.print_grid()
# test.a_star()
# test.print_grid()