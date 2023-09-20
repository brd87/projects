import pygame
import sys
import random
import time
from pygame.locals import *

from player import Player
from tile import Tile
from enemy import Enemy
from missile import Missile
from item import Item

pygame.init()

WIDTH = 500
HEIGHT = 842
window_size = (WIDTH, HEIGHT)

c_black = (0, 0, 0)
c_white = (255, 255, 255)
c_green = (0, 255, 0)
c_yellow = (255, 255, 0)
c_red = (255, 0, 0)
c_red_a = (255, 0, 0, 128)
c_gray = (128, 128, 128)
c_blue = (0, 0, 255)
c_light_blue = (0, 153, 153)
c_orange = (155, 128, 0)

# config
##########################
SE_DIR = "soundef/"
SP_DIR = "sprites/"
GAME_SOUNDTRACK = "soundtrack.wav"
GAME_VOL = 0.05
GAME_BG_SP = pygame.image.load(SP_DIR + "background.png")

TILE_G = 10
TILE_B = 2
TILE_J = 2
TILE_G_SP = SP_DIR + "good_tile.png"
TILE_B_SP = SP_DIR + "bad_tile.png"
TILE_J_SP = SP_DIR + "jump_tile.png"
TILE_B_DAMAGE = 1
TILE_J_MULTI = 2

PLAYER_HEALTH = 100
PLAYER_SCORE = 0
PLAYER_ACC = 0.5
PLAYER_FRIC = -0.12
PLAYER_JUMP_P = 15
PLAYER_JUMP_K = 5
PLAYER_MISSILE_SP = SP_DIR + "player_missile.png"
PLAYER_MISSILE_SE = pygame.mixer.Sound(SE_DIR + "player_laser.wav")
PLAYER_MISSILE_LIMIT = 3
PLAYER_MISSILE_SPEED = 10
PLAYER_FORCE_SP = SP_DIR + "force.png"
PLAYER_FORCE_SE = pygame.mixer.Sound(SE_DIR + "force.wav")
PLAYER_FORCE_MULTI = 1.5
PLAYER_FORCE_COOL = 3000
PLAYER_FORCE_SPEED = 20
PLAYER_HEALTH_GAIN_COLOR = c_green
PLAYER_HEALTH_GAIN = 10
PLAYER_DAMAGE_COLOR = c_red_a
PLAYER_DAMAGE_COOL = 2000
PLAYER_DAMAGE_SE = pygame.mixer.Sound(SE_DIR + "damage.wav")
PLAYER_DEATH_SE = pygame.mixer.Sound(SE_DIR + "death.wav")
PLAYER_PJUMP_SE = pygame.mixer.Sound(SE_DIR + "power_jump.wav")

ENEMY_HIT_SE = pygame.mixer.Sound(SE_DIR + "enemy_hit.wav")
ENEMY_SCALING = 500
ENEMY_MISSILE_SP = SP_DIR + "enemy_missile.png"
ENEMY_MISSILE_SE = pygame.mixer.Sound(SE_DIR + "enemy_laser.wav")
ENEMY_MISSILE_COOL = 2000
ENEMY_MISSILE_DAMAGE = 10
ENEMY_MISSILE_SPEED = 10

AMMO_AV = 1
AMMO_SP = SP_DIR + "ammo_bag.png"
AMMO_SE = pygame.mixer.Sound(SE_DIR + "reload.wav")
AMMO_COUNT = 1

PLAYER_MISSILE_SE.set_volume(GAME_VOL)
PLAYER_FORCE_SE.set_volume(GAME_VOL)
PLAYER_DAMAGE_SE.set_volume(GAME_VOL)
PLAYER_DEATH_SE.set_volume(GAME_VOL)
PLAYER_PJUMP_SE.set_volume(GAME_VOL)
ENEMY_HIT_SE.set_volume(GAME_VOL)
ENEMY_MISSILE_SE.set_volume(GAME_VOL)
AMMO_SE.set_volume(GAME_VOL)
##########################

FPS = 60
FramePerSec = pygame.time.Clock()

DISPLAY = pygame.display.set_mode(window_size)
pygame.display.set_caption("PGplatformer")


def generate_tile(image):
    return Tile(random.randint(50,100), 12, random.randint(0,WIDTH-10), random.randint(0, HEIGHT-50), image, WIDTH)


def generate_item(image):
    return Item(random.randint(0,WIDTH-10), random.randint(0, HEIGHT-50), 30, 30, image)


def check_tile(entities, target):
    if pygame.sprite.spritecollide(target, entities, False):
        return True
    for entity in entities:
        if entity == target:
            continue
        if abs(target.rect.top - entity.rect.bottom) < 50 and abs(target.rect.bottom - entity.rect.top) < 50:
            return True
    return False


def generate_level(entities, amount, image, if_first_gen, if_tile):
    while len(entities) < amount:
        if if_tile: object = generate_tile(image)
        else: object = generate_item(image)
        if not if_first_gen: object.rect.y -= HEIGHT
        while check_tile(entities, object):
            if if_tile: object = generate_tile(image)
            else: object = generate_item(image)
            if not if_first_gen: object.rect.y -= HEIGHT
        entities.append(object)
    return entities


def draw(entities_group, items_group, player, enemy):
    #DISPLAY.fill(c_black)
    DISPLAY.blit(GAME_BG_SP, (0, 0))
    DISPLAY.blit(player.surf, player.rect)
    DISPLAY.blit(enemy.surf, enemy.rect)
    enemy.move()
    for entities in entities_group:
        for entity in entities:
            DISPLAY.blit(entity.surf, entity.rect)
            entity.move()
    for items in items_group:
        for item in items:
            DISPLAY.blit(item.surf, item.rect)
    draw_stats()


def draw_stats():
    text = pygame.font.SysFont("impact", 20)
    text_health = text.render(f"Heath: {player.health}%", True, c_light_blue)
    text_ammo = text.render(f"Ammo: {player.ammo}/{PLAYER_MISSILE_LIMIT}", True, c_orange)
    text_score = text.render(str(player.score), True, c_gray)
    # pygame.draw.line(DISPLAY, c_white, (0, 20), (WIDTH, 20), 40)
    # pygame.draw.line(DISPLAY, c_gray, (0, 41), (WIDTH, 41), 1)
    # pygame.draw.line(DISPLAY, c_gray, (0, 0), (WIDTH, 0), 1)
    stat_bar = pygame.image.load("sprites/stat_bar.png")
    DISPLAY.blit(stat_bar, (0, 0))
    DISPLAY.blit(text_health, (7, 8))
    DISPLAY.blit(text_ammo, (WIDTH/4+8, 8))
    DISPLAY.blit(text_score, (WIDTH/4*3, 7))
    
    
def draw_cross():
    pygame.draw.line(DISPLAY, TILE_B_SP, (0, 42), window_size, 20)
    pygame.draw.line(DISPLAY, TILE_B_SP, (window_size[0], 42), (0, window_size[1]), 20)


def draw_fog(color):
    fog = pygame.Surface((WIDTH, HEIGHT-41), pygame.SRCALPHA)
    fog.fill(color)
    DISPLAY.blit(fog, (0, 42))


def update(entities, player):
    hit = pygame.sprite.spritecollide(player, entities, False)
    if hit and player.vel.y > 0:
        player.player_hit(hit[0])


def if_collision(entities, target):
    hit = pygame.sprite.spritecollide(target, entities, False)
    if hit:
        return hit[0]
    return False


def update_entities(entities, target, image, amount, if_tile):
    new_ent = []
    for entity in entities:
        entity.rect.y += abs(target.vel.y)
        if entity.rect.top < HEIGHT:
            new_ent.append(entity)
    return generate_level(new_ent, amount, image, False, if_tile)


def update_missiles(missiles):
    new_missiles = []
    for missile in missiles:
        if missile.rect.bottom > 0 and missile.rect.top < HEIGHT:
            new_missiles.append(missile)
    return new_missiles


player = Player(WIDTH, HEIGHT, PLAYER_ACC, PLAYER_FRIC, PLAYER_HEALTH)
enemy = Enemy(WIDTH, ENEMY_SCALING)

player_missiles = []
enemy_missiles = []

player_force = []

ammo_bags = []
start_ammo = Item(WIDTH/2, HEIGHT-150, 30, 30, AMMO_SP)
ammo_bags.append(start_ammo)
ammo_bags = generate_level(ammo_bags, AMMO_AV+1, AMMO_SP, True, False)
shield_bags = []

start_tile = Tile(WIDTH, 20, WIDTH/2, HEIGHT-10, TILE_G_SP, WIDTH)
start_tile.if_move = False
g_tile = Tile(WIDTH/4, 20, WIDTH/2, HEIGHT-100, TILE_G_SP, WIDTH)

good_entities = []
good_entities.append(start_tile)
good_entities.append(g_tile)
good_entities = generate_level(good_entities, TILE_G+1, TILE_G_SP, True, True)
bad_entities = []
bad_entities = generate_level(bad_entities, TILE_B+1, TILE_B_SP, True, True)
jump_entities = []
jump_entities = generate_level(jump_entities, TILE_J+1, TILE_J_SP, True, True)

enemy_fired_time = 0
player_force_time = 0
player_hit_time = 0

pygame.mixer.music.load(SE_DIR + GAME_SOUNDTRACK)
pygame.mixer.music.set_volume(GAME_VOL)
pygame.mixer.music.play(-1)
while True:
    current_time = pygame.time.get_ticks()
    draw((good_entities, bad_entities, jump_entities, player_missiles, enemy_missiles, player_force), (ammo_bags, shield_bags), player, enemy)
    update(good_entities, player)

    player.move()
    hit = if_collision(enemy_missiles, player)
    if (if_collision(bad_entities, player) or hit) and current_time - player_hit_time >= PLAYER_DAMAGE_COOL:       # damage
        draw_fog(PLAYER_DAMAGE_COLOR)
        PLAYER_DAMAGE_SE.play()
        player_hit_time = current_time
        if hit:
            player.health -= ENEMY_MISSILE_DAMAGE
            enemy_missiles.remove(hit)
            hit = False
        else:
            player.health -= TILE_B_DAMAGE
    hit = if_collision(player_missiles, enemy)
    if hit:                                             # player hit
        draw_fog(PLAYER_HEALTH_GAIN_COLOR)
        ENEMY_HIT_SE.play()
        player.health += PLAYER_HEALTH_GAIN
        player_missiles.remove(hit)
        hit = False
        if player.health > PLAYER_HEALTH:
            player.health = PLAYER_HEALTH
    hit = if_collision(ammo_bags, player)
    if hit:                                             # ammo gain
        AMMO_SE.play()
        ammo_bags.remove(hit)
        hit = False
        if player.ammo < PLAYER_MISSILE_LIMIT:
            player.ammo += AMMO_COUNT
    if if_collision(jump_entities, player):             # turbo jump
        PLAYER_PJUMP_SE.play()
        player.jump(PLAYER_JUMP_P*TILE_J_MULTI)
    if if_collision(player_force, enemy):               # force jump
        player.jump(PLAYER_JUMP_P*PLAYER_FORCE_MULTI)
    if player.rect.top > HEIGHT or player.health == 0:  # game over
        #DISPLAY.fill(c_black)
        DISPLAY.blit(GAME_BG_SP, (0, 0))
        PLAYER_DEATH_SE.play()
        draw_stats()
        draw_fog(PLAYER_DAMAGE_COLOR)
        pygame.display.update()
        time.sleep(2)
        pygame.quit()
        sys.exit()


    if player.rect.top <= HEIGHT/2:
        player.score += 1
        enemy.score -= 1
        if enemy.score == 0:
            enemy.score = ENEMY_SCALING
            enemy.up_dif()
        player.pos.y += abs(player.vel.y)
        good_entities = update_entities(good_entities, player, TILE_G_SP, TILE_G+1, True)
        bad_entities = update_entities(bad_entities, player, TILE_B_SP, TILE_B+1, True)
        jump_entities = update_entities(jump_entities, player, TILE_J_SP, TILE_J+1, True)
        ammo_bags = update_entities(ammo_bags, player, AMMO_SP, AMMO_AV+1, False)
    
    if current_time - enemy_fired_time >= ENEMY_MISSILE_COOL:
        ENEMY_MISSILE_SE.play()
        enemy_missiles.append(Missile(enemy.rect.left+25, enemy.rect.bottom+15, 7, 30, ENEMY_MISSILE_SP, ENEMY_MISSILE_SPEED))
        enemy_fired_time = current_time

    player_missiles = update_missiles(player_missiles)
    enemy_missiles = update_missiles(enemy_missiles)
    player_force = update_missiles(player_force)


    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:                                                                                # esc / quit key
                pygame.quit()
                sys.exit()
            if event.key == pygame.K_UP and if_collision(good_entities, player):                                            # up / jump key
                PLAYER_PJUMP_SE.play()
                player.jump(PLAYER_JUMP_P)
            if event.key == pygame.K_SPACE and player.ammo > 0:                                                             # space / fire missile key
                PLAYER_MISSILE_SE.play()
                player_missiles.append(Missile(player.pos.x, player.pos.y-52.5, 5, 25, PLAYER_MISSILE_SP, -PLAYER_MISSILE_SPEED))
                player.ammo -= 1
            if event.key == pygame.K_LCTRL and current_time - player_force_time >= PLAYER_FORCE_COOL:                       # left ctrl / fire force key
                PLAYER_FORCE_SE.play()
                player_force.append(Missile(player.pos.x, player.pos.y-45, 10, 10, PLAYER_FORCE_SP, -PLAYER_FORCE_SPEED))
                player_force_time = current_time
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_UP and player.if_jump:                                                                 # up / kill jump key
                player.kill_jump(PLAYER_JUMP_K)
        if event.type == QUIT:
            pygame.quit()
            sys.exit()


    pygame.display.update()
    FramePerSec.tick(FPS)