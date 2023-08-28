import pygame
import sys
from pygame.locals import *

from grid import Grid

pygame.init()

xy = 42
squere_size = 15
window_size = (xy*squere_size, xy*squere_size)

c_black = (0, 0, 0) # 0-wall
c_white = (255, 255, 255) # 1-space
c_green = (0, 255, 0) # 2-start
c_yellow = (255, 255, 0) # 4-path
c_red = (255, 0, 0) # 3-target
c_gray = (128, 128, 128) # background

DISPLAY = pygame.display.set_mode(window_size)
DISPLAY.fill(c_white)
pygame.display.set_caption("ASpathfinding")

def draw(window, operation_grid, solvable):
    window.fill(c_gray)
    for y in range(operation_grid.size_y):
        for x in range(operation_grid.size_x):
            pygame.draw.rect(DISPLAY, operation_grid.grid[y][x].color, (x*squere_size, y*squere_size, squere_size, squere_size), border_radius=5)
    if not solvable:
        pygame.draw.line(DISPLAY, c_red, (0, 0), window_size, 20)
        pygame.draw.line(DISPLAY, c_red, (window_size[0], 0), (0, window_size[1]), 20)
    pygame.display.update()

def get_grid_position(click_pos):
    x, y = click_pos
    pos = y // squere_size, x // squere_size
    return pos


operation_grid = Grid(xy, xy, c_black, c_white, c_green, c_red, c_yellow)
ready = True
solvable = True
while True:
    draw(DISPLAY, operation_grid, solvable)
    for event in pygame.event.get():
        if ready:
            if pygame.mouse.get_pressed()[0]: # left mouse / morph into xyz
                click_pos = pygame.mouse.get_pos()
                pos = get_grid_position(click_pos)
                if operation_grid.start_node == False:
                    operation_grid.make_tile(pos, 2, operation_grid.c_start)
                elif operation_grid.target_node == False:
                    operation_grid.make_tile(pos, 3, operation_grid.c_end)
                else:
                    operation_grid.make_tile(pos, 0, operation_grid.c_wall)
        
            if pygame.mouse.get_pressed()[2]: # right mouse / clear
                click_pos = pygame.mouse.get_pos()
                pos = get_grid_position(click_pos)
                operation_grid.make_tile(pos, 1, operation_grid.c_sapce)

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE and operation_grid.start_node and operation_grid.target_node and ready: # sapce / preform A*
                solvable = operation_grid.a_star()
                ready = False
            if event.key == pygame.K_LSHIFT: # Lshift / autogenerate grid
                if operation_grid.grid != []:
                    operation_grid.make_new()
                operation_grid.set()
                solvable = True
                ready = True
            if event.key == pygame.K_LCTRL: # Lctrl / clear
                if operation_grid.grid != []:
                    operation_grid.make_new()
                solvable = True
                ready = True
            if event.key == pygame.K_ESCAPE: # esc / quit key
                pygame.quit()
                sys.exit()
            
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    pygame.display.update()