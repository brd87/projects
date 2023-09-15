import pygame
import sys
import random
from pygame.locals import *

from player import Player
from tile import Tile

pygame.init()

WIDTH = 500
HEIGHT = 800
window_size = (WIDTH, HEIGHT)

c_black = (0, 0, 0)
c_white = (255, 255, 255)
c_green = (0, 255, 0)
c_yellow = (255, 255, 0)
c_red = (255, 0, 0)
c_gray = (128, 128, 128)


ACC = 0.5
FRIC = -0.12
PLAT_G = 10
PLAT_B = 3
PLAT_J = 2
JUMP_P = 15
JUMP_K = 5
PLAT_G_color = c_white
PLAT_B_color = c_red
PLAT_J_color = c_yellow
PLAYER_color = c_gray



FPS = 60
FramePerSec = pygame.time.Clock()

DISPLAY = pygame.display.set_mode(window_size)
pygame.display.set_caption("PGplatformer")


def generate_tile(color):
    return Tile(random.randint(50,100), 12, random.randint(0,WIDTH-10), random.randint(0, HEIGHT-50), color)

def check_tile(entities, target):
    if pygame.sprite.spritecollide(target, entities, False):
        return True
    for entity in entities:
        if entity == target:
            continue
        if abs(target.rect.top - entity.rect.bottom) < 50 and abs(target.rect.bottom - entity.rect.top) < 50:
            return True
    return False

def generate_level(entities, amount, color, if_first_gen):
    while len(entities) < amount:
        tile = generate_tile(color)
        if not if_first_gen: tile.rect.y -= HEIGHT
        while check_tile(entities, tile):
            tile = generate_tile(color)
            if not if_first_gen: tile.rect.y -= HEIGHT
        entities.append(tile)
    return entities


def draw(entities_group, player):
    DISPLAY.fill(c_black)
    DISPLAY.blit(player.surf, player.rect)
    for entities in entities_group:
        for entity in entities:
            DISPLAY.blit(entity.surf, entity.rect)
    
def draw_cross():
    pygame.draw.line(DISPLAY, PLAT_B_color, (0, 0), window_size, 20)
    pygame.draw.line(DISPLAY, PLAT_B_color, (window_size[0], 0), (0, window_size[1]), 20)


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
    return generate_level(new_ent, amount, color, False)


player = Player(WIDTH, HEIGHT, PLAYER_color, ACC, FRIC)
start_plat = Tile(WIDTH, 20, WIDTH/2, HEIGHT-10, PLAT_G_color)
g_plat = Tile(WIDTH/4, 20, WIDTH/2, HEIGHT-100, PLAT_G_color)

good_entities = []
good_entities.append(start_plat)
good_entities.append(g_plat)
good_entities = generate_level(good_entities, PLAT_G+1, PLAT_G_color, True)
bad_entities = []
bad_entities = generate_level(bad_entities, PLAT_B+1, PLAT_B_color, True)
jump_entities = []
jump_entities = generate_level(jump_entities, PLAT_J+1, PLAT_J_color, True)

while True:
    draw((good_entities, bad_entities, jump_entities), player)
    update(good_entities, player)

    player.move()
    if if_collision(bad_entities, player): # damage
        draw_cross()
    if if_collision(jump_entities, player): # turbo jump
        player.jump(JUMP_P*2)

    if player.rect.top <= HEIGHT/3:
        player.pos.y += abs(player.vel.y)
        good_entities = update_ent(good_entities, player, PLAT_G_color, PLAT_G+1)
        bad_entities = update_ent(bad_entities, player, PLAT_B_color, PLAT_B+1)
        jump_entities = update_ent(jump_entities, player, PLAT_J_color, PLAT_J+1)
        

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE: # esc / quit key
                pygame.quit()
                sys.exit()
            if event.key == pygame.K_UP and if_collision(good_entities, player): # space / jump key
                player.jump(JUMP_P)
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_UP and player.if_jump: # space / kill jump key
                player.kill_jump(JUMP_K)
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()
    FramePerSec.tick(FPS)
