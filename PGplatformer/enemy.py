import pygame
import random
from pygame.locals import *

class Enemy:
    def __init__(self, WIDTH, prep):
        self.border = WIDTH
        self.surf = pygame.image.load("sprites/enemy.png")
        self.rect = self.surf.get_rect(center = (WIDTH/2, 66))
        self.dif = [-1, 1]
        self.speed = random.choice(self.dif)
        self.score = prep
    def move(self):
        self.rect.move_ip(self.speed, 0)
        if self.speed > 0 and self.rect.right > self.border:
            self.speed *= -1
            self.rect.move_ip(self.speed, 0)
        if self.speed < 0 and self.rect.left < 0:
            self.speed *= -1
            self.rect.move_ip(self.speed, 0)
    def up_dif(self):
        if self.speed > 0: self.speed += 1
        else: self.speed -= 1