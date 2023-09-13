import pygame
from pygame.locals import *

class GoodPlatform:
    def __init__(self, WIDTH, HEIGHT, color):
        self.surf = pygame.Surface((WIDTH, 20))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (WIDTH/2, HEIGHT-10))