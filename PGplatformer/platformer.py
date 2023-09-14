import pygame
import sys
import random
from pygame.locals import *

from player import Player
from tile import Tile

pygame.init()

WIDTH = 500
HEIGHT = 500
window_size = (WIDTH, HEIGHT)

c_black = (0, 0, 0) # 0-wall
c_white = (255, 255, 255) # 1-space
c_green = (0, 255, 0) # 2-start
c_yellow = (255, 255, 0) # 4-path
c_red = (255, 0, 0) # 3-target
c_gray = (128, 128, 128) # background

ACC = 0.5
FRIC = -0.12
FPS = 60
FramePerSec = pygame.time.Clock()

DISPLAY = pygame.display.set_mode(window_size)
pygame.display.set_caption("PGplatformer")


def generate_platform(color):
    return Tile(random.randint(50,100), 12, random.randint(0,WIDTH-10), random.randint(0, HEIGHT-50), color)


def generate_level(entities, amount, color):
    while len(entities) < amount:
        entities.append(generate_platform(color))
    return entities


def draw(g_entities, b_entities, player):
    DISPLAY.fill(c_black)
    DISPLAY.blit(player.surf, player.rect)
    for entity in g_entities:
        DISPLAY.blit(entity.surf, entity.rect)
    for entity in b_entities:
        DISPLAY.blit(entity.surf, entity.rect)


def draw_cross():
    pygame.draw.line(DISPLAY, c_red, (0, 0), window_size, 20)
    pygame.draw.line(DISPLAY, c_red, (window_size[0], 0), (0, window_size[1]), 20)


def update(entities, player):
    hit = pygame.sprite.spritecollide(player, entities, False)
    if hit and player.vel.y > 0:
        player.player_hit(hit[0])


def if_collision(entities, target):
    hit = pygame.sprite.spritecollide(target, entities, False)
    if hit:
        return True
    return False


def update_ent(entities, target, color, amount):
    new_ent = []
    for entity in entities:
        entity.rect.y += abs(target.vel.y)
        if entity.rect.top < HEIGHT:
            new_ent.append(entity)
    return generate_level(new_ent, amount, color)

player = Player(WIDTH, HEIGHT, c_white, ACC, FRIC)
start_plat = Tile(WIDTH, 20, WIDTH/2, HEIGHT-10, c_green)
g_plat = Tile(WIDTH/4, 20, WIDTH/2, HEIGHT-100, c_green)
good_entities = []
good_entities.append(start_plat)
good_entities.append(g_plat)

for x in range(random.randint(4,6)):
    good_entities.append(generate_platform(c_green))

bad_entities = []
for x in range(random.randint(1,3)):
    bad_entities.append(generate_platform(c_red))

while True:
    draw(good_entities, bad_entities, player)
    update(good_entities, player)

    player.move()
    if if_collision(bad_entities, player):
        draw_cross()

    if player.rect.top <= HEIGHT/3:
        player.pos.y += abs(player.vel.y)
        good_entities = update_ent(good_entities, player, c_green, 7)
        bad_entities = update_ent(bad_entities, player, c_red, 4)
        

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE: # esc / quit key
                pygame.quit()
                sys.exit()
            if event.key == pygame.K_UP and if_collision(good_entities, player): # space / jump key
                player.jump()
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()
    FramePerSec.tick(FPS)
