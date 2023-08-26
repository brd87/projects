import pygame
import sys
from pygame.locals import *

from grid import Grid

pygame.init()

FPS = 30
FramePerSec = pygame.time.Clock()

c_black = pygame.Color(0, 0, 0)
c_white = pygame.Color(255, 255, 255)
c_green = pygame.Color(0, 255, 0) # start
c_yellow = pygame.Color(255, 255, 0) # path
c_red = pygame.Color(255, 0, 0) # target

DISPLAYSURF = pygame.display.set_mode((600, 600))
DISPLAYSURF.fill(c_white)
pygame.display.set_caption("ASpathfinding")



class Square:
    def __init__(self):
        self.color = c_white
        pass

class SquareGrid:
    pass

def draw(window, op_Grid):
    pygame.display.update()



operation_grid = None
while True:
    draw(DISPLAYSURF, operation_grid)
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
                operation_grid = Grid(21, 21, True, None)
                #operation_grid.print_grid()
            if event.key == pygame.K_LCTRL: # Lctrl mouse / load user grid
                pass 
            if event.key == pygame.K_ESCAPE: # esc mouse / quit key
                pygame.quit()
                sys.exit()

        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    pygame.display.update()