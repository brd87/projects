import pygame
from pygame.locals import *

vec = pygame.math.Vector2

class Player:
    def __init__(self, WIDTH, HEIGHT, color, ACC, FRIC):
        self.border = WIDTH
        self.f_acc = ACC
        self.f_fric = FRIC
        self.surf = pygame.Surface((40, 40))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (WIDTH/2, HEIGHT-40))

        self.pos = vec((WIDTH/2, HEIGHT-40))
        self.vel = vec(0,0)
        self.acc = vec(0,0)


    def move(self):
        self.acc = vec(0,0.5)
        pressed_keys = pygame.key.get_pressed()
        if pressed_keys[K_LEFT]:
            self.acc.x = -self.f_acc
        if pressed_keys[K_RIGHT]:
            self.acc.x = self.f_acc

        self.acc.x += self.vel.x * self.f_fric
        self.vel += self.acc
        self.pos += self.vel + 0.5 * self.acc

        if self.pos.x > self.border:
            self.pos.x = 0
        if self.pos.x < 0:
            self.pos.x = self.border
            
        self.rect.midbottom = self.pos

