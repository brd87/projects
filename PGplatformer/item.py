import pygame
from pygame.locals import *

class Item:
    def __init__(self, pos_x, pos_y, sprite_width, sprite_height, image):
        self.img = pygame.image.load(image).convert()
        self.img.set_colorkey((0,0,0))
        self.surf = pygame.transform.scale(self.img, (sprite_width, sprite_height))
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))