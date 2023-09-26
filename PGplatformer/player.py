import pygame
from pygame.locals import *

vec = pygame.math.Vector2

class Player:
    def __init__(self, WIDTH, HEIGHT, ACC, FRIC, health):
        self.border = WIDTH
        self.f_acc = ACC
        self.f_fric = FRIC
        self.surf = pygame.image.load("sprites/player_idle/player_idle_0.png").convert()
        self.surf.set_colorkey((0,0,0))
        self.rect = self.surf.get_rect(center = (WIDTH/2, HEIGHT-40))

        self.animation_now = "idle"
        self.animation_prev = "idle"
        self.animation_flip = False
        self.frame_now = 0
        self.frame_time = 2
        self.animation_db = {}
        self.animation_db["walk"] = [self.load_animation("sprites/player_walk/player_walk_", 9), 2]
        self.animation_db["idle"] = [self.load_animation("sprites/player_idle/player_idle_", 3), 8]

        self.pos = vec((WIDTH/2, HEIGHT-40))
        self.vel = vec(0,0)
        self.acc = vec(0,0)
        self.if_jump = False
        self.health = health
        self.score = 0
        self.ammo = 0


    def load_animation(self, path, frames):
        animation = []
        for x in range(frames):
            animation.append(path+str(x)+".png")
        return animation


    def update_sprite(self):
        if self.animation_now != self.animation_prev:
            self.frame_now = 0
        self.animation_prev = self.animation_now
        self.frame_time = self.animation_db[self.animation_now][1]

        self.frame_now += 1
        if self.frame_now == len(self.animation_db[self.animation_now][0]):
            self.frame_now = 0
        
        self.surf = pygame.image.load(self.animation_db[self.animation_now][0][self.frame_now]).convert()
        if self.animation_flip == True:
            self.surf = pygame.transform.flip(self.surf, True, False)
        self.surf.set_colorkey((0,0,0))


    def move(self):
        self.acc = vec(0,0.5)
        pressed_keys = pygame.key.get_pressed()
        if pressed_keys[K_LEFT]:
            self.acc.x = -self.f_acc
            self.animation_now = "walk"
            self.animation_flip = True
        if pressed_keys[K_RIGHT]:
            self.acc.x = self.f_acc
            self.animation_now = "walk"
            self.animation_flip = False
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
        if hit.if_move:
            self.pos += (hit.speed, 0)
        if self.pos.y < hit.rect.bottom:
            self.if_jump = False
            self.pos.y = hit.rect.top + 1
            self.vel.y = 0
        else:
            self.vel.y = -6