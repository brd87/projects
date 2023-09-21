import pygame
import random
from pygame.locals import *

class Tile:
    def __init__(self, sprite_width, sprite_height, pos_x, pos_y, image, border):
        self.border = border
        self.surf = pygame.transform.scale(pygame.image.load(image), (sprite_width, sprite_height))
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))
        self.speed = random.randint(-2, 2)
        self.if_move = True
    def move(self):
        if self.if_move == True:
            self.rect.move_ip(self.speed, 0)
            if self.speed > 0 and self.rect.left > self.border:
                self.rect.right = 0
            if self.speed < 0 and self.rect.right < 0:
                self.rect.left = self.border