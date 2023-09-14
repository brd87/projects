import pygame
from pygame.locals import *

class Tile:
    def __init__(self, width, height, pos_x, pos_y, color):
        self.surf = pygame.Surface((width, height))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))