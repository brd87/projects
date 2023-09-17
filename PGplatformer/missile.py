import pygame
from pygame.locals import *

class Missile:
    def __init__(self, pos_x, pos_y, color, prep, speed):
        self.surf = pygame.Surface((5, 30))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (pos_x, pos_y))
        self.speed = speed
        self.score = prep
    def move(self):
        self.rect.move_ip(0, self.speed)
    def up_dif(self):
        if self.speed > 0: self.speed += 1
        else: self.speed -= 1