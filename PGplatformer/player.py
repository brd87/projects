import pygame
from pygame.locals import *

vec = pygame.math.Vector2

class Player:
    def __init__(self, WIDTH, HEIGHT, color, ACC, FRIC, health):
        self.border = WIDTH
        self.f_acc = ACC
        self.f_fric = FRIC
        self.surf = pygame.Surface((40, 40))
        self.surf.fill(color)
        self.rect = self.surf.get_rect(center = (WIDTH/2, HEIGHT-40))

        self.pos = vec((WIDTH/2, HEIGHT-40))
        self.vel = vec(0,0)
        self.acc = vec(0,0)
        self.if_jump = False
        self.health = health
        self.score = 0


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

        if self.pos.x > self.border or self.pos.x < 0:
            self.vel.x = -self.vel.x*2
            
        self.rect.midbottom = self.pos


    def jump(self, power):
        self.if_jump = True
        self.vel.y = -power

    def kill_jump(self, power):
        self.if_jump = False
        self.vel.y += power

    def player_hit(self, hit):
        if self.pos.y < hit.rect.bottom:
            self.if_jump = False
            self.pos.y = hit.rect.top + 1
            self.vel.y = 0
        else:
            self.vel.y = -6