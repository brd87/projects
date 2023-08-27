import pygame
import sys
from pygame.locals import *

from grid import Grid

pygame.init()

xy = 21
squere_size = 25
window_size = (xy*squere_size, xy*squere_size)

FPS = 30
FramePerSec = pygame.time.Clock()

c_black = (0, 0, 0) # 0-wall
c_white = (255, 255, 255) # 1-space
c_green = (0, 255, 0) # 2-start
c_yellow = (255, 255, 0) # 4-path
c_red = (255, 0, 0) # 3-target

DISPLAY = pygame.display.set_mode(window_size)
DISPLAY.fill(c_white)
pygame.display.set_caption("ASpathfinding")

def draw(window, op_grid):
    DISPLAY.fill(c_white)
    for y in range(op_grid.size_y):
        for x in range(op_grid.size_x):
            pygame.draw.rect(DISPLAY, op_grid.grid[y][x].color, (x*squere_size, y*squere_size, squere_size, squere_size))
    pygame.display.update()

def get_grid_position(click_pos):
    x, y = click_pos
    pos = x // squere_size, y // squere_size
    return pos

operation_grid = Grid(xy, xy, c_black, c_white, c_green, c_yellow, c_red)
user_grid = operation_grid.grid
while True:
    draw(DISPLAY, operation_grid)
    for event in pygame.event.get():
        if pygame.mouse.get_pressed()[0]: # left mouse
            click_pos = pygame.mouse.get_pos()
            print(click_pos)
            # morph into xyz
    
        if pygame.mouse.get_pressed()[2]: # right mouse
            click_pos = pygame.mouse.get_pos()
            print(click_pos)
            # clear

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE and operation_grid is not None: # sapce mouse / preform A*
                operation_grid.a_star() 
            if event.key == pygame.K_LSHIFT: # Lshift mouse / autogenerate grid
                operation_grid.setting(True, None)
                #operation_grid.print_grid()
            if event.key == pygame.K_LCTRL: # Lctrl mouse / load user grid
                operation_grid.setting(True, user_grid)
                pass 
            if event.key == pygame.K_ESCAPE: # esc mouse / quit key
                pygame.quit()
                sys.exit()

        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    pygame.display.update()