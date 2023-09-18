import pygame
from pygame.locals import *

class Item:
    def __init__(self, pos_x, pos_y, sprite_width, sprite_height, color):
        self.surf = pygame.Surface((sprite_width, sprite_height))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))