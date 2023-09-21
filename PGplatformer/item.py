import pygame
from pygame.locals import *

class Item:
    def __init__(self, pos_x, pos_y, sprite_width, sprite_height, image):
        self.surf = pygame.transform.scale(pygame.image.load(image), (sprite_width, sprite_height))
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))