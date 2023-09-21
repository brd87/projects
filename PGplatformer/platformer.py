import pygame
import sys
import random
import time
from pygame.locals import *

from config import Config
from player import Player
from tile import Tile
from enemy import Enemy
from missile import Missile
from item import Item

pygame.init()
WIDTH = 500
HEIGHT = 842
window_size = (WIDTH, HEIGHT)
FPS = 60
FramePerSec = pygame.time.Clock()
DISPLAY = pygame.display.set_mode(window_size)
pygame.display.set_caption("PGplatformer")
config = Config(WIDTH, HEIGHT)

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


def draw(entities_group, items_group, player, enemy, game_bg, missile_limit):
    DISPLAY.blit(game_bg, (0, 0))
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
    draw_stats(player, missile_limit)


def draw_stats(player, missile_limit):
    text = pygame.font.SysFont("impact", 20)
    text_health = text.render(f"Heath: {player.health}%", True, c_light_blue)
    text_ammo = text.render(f"Ammo: {player.ammo}/{missile_limit}", True, c_orange)
    text_score = text.render(str(player.score), True, c_gray)
    stat_bar = pygame.image.load("sprites/stat_bar.png")
    DISPLAY.blit(stat_bar, (0, 0))
    DISPLAY.blit(text_health, (7, 8))
    DISPLAY.blit(text_ammo, (WIDTH/4+8, 8))
    DISPLAY.blit(text_score, (WIDTH/4*3, 7))


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


player = Player(WIDTH, HEIGHT, config.PLAYER_ACC, config.PLAYER_FRIC, config.PLAYER_HEALTH)
enemy = Enemy(WIDTH, config.ENEMY_SCALING)

player_missiles = []
enemy_missiles = []

player_force = []

ammo_bags = []
start_ammo = Item(WIDTH/2, HEIGHT-150, 30, 30, config.AMMO_SP)
ammo_bags.append(start_ammo)
ammo_bags = generate_level(ammo_bags, config.AMMO_AV+1, config.AMMO_SP, True, False)
shield_bags = []

start_tile = Tile(WIDTH, 20, WIDTH/2, HEIGHT-10, config.TILE_G_SP, WIDTH)
start_tile.if_move = False
g_tile = Tile(WIDTH/4, 20, WIDTH/2, HEIGHT-100, config.TILE_G_SP, WIDTH)

good_entities = []
good_entities.append(start_tile)
good_entities.append(g_tile)
good_entities = generate_level(good_entities, config.TILE_G+1, config.TILE_G_SP, True, True)
bad_entities = []
bad_entities = generate_level(bad_entities, config.TILE_B+1, config.TILE_B_SP, True, True)
jump_entities = []
jump_entities = generate_level(jump_entities, config.TILE_J+1, config.TILE_J_SP, True, True)

enemy_fired_time = 0
player_force_time = 0
player_hit_time = 0


config.main_menu.mainloop(DISPLAY)
pygame.mixer.music.load(config.SE_DIR + config.GAME_SOUNDTRACK)
pygame.mixer.music.set_volume(config.MUSIC_VOL)
pygame.mixer.music.play(-1)
while True:
    current_time = pygame.time.get_ticks()
    draw((good_entities, bad_entities, jump_entities, player_missiles, enemy_missiles, player_force), (ammo_bags, shield_bags), player, enemy, config.GAME_BG_SP, config.PLAYER_MISSILE_LIMIT)
    update(good_entities, player)

    player.move()
    hit = if_collision(enemy_missiles, player)          # damage
    if (if_collision(bad_entities, player) or hit) and current_time - player_hit_time >= config.PLAYER_DAMAGE_COOL:
        draw_fog(config.PLAYER_DAMAGE_COLOR)
        config.PLAYER_DAMAGE_SE.play()
        player_hit_time = current_time
        if hit:
            player.health -= config.ENEMY_MISSILE_DAMAGE
            enemy_missiles.remove(hit)
            hit = False
        else:
            player.health -= config.TILE_B_DAMAGE
        if player.health < 0:
            player.health = 0
    hit = if_collision(player_missiles, enemy)          # player hit
    if hit:
        draw_fog(config.PLAYER_HEALTH_GAIN_COLOR)
        config.ENEMY_HIT_SE.play()
        player.health += config.PLAYER_HEALTH_GAIN
        player_missiles.remove(hit)
        hit = False
        if player.health > config.PLAYER_HEALTH:
            player.health = config.PLAYER_HEALTH
    hit = if_collision(ammo_bags, player)               # ammo gain
    if hit:
        config.AMMO_SE.play()
        ammo_bags.remove(hit)
        hit = False
        if player.ammo < config.PLAYER_MISSILE_LIMIT:
            player.ammo += config.AMMO_COUNT
    if if_collision(jump_entities, player):             # turbo jump
        config.PLAYER_PJUMP_SE.play()
        player.jump(config.PLAYER_JUMP_P*config.TILE_J_MULTI)
    if if_collision(player_force, enemy):               # force jump
        player.jump(config.PLAYER_JUMP_P*config.PLAYER_FORCE_MULTI)
    if player.rect.top > HEIGHT or player.health <= 0:  # game over
        DISPLAY.blit(config.GAME_BG_SP, (0, 0))
        config.PLAYER_DEATH_SE.play()
        draw_stats(player, config.PLAYER_MISSILE_LIMIT)
        draw_fog(config.PLAYER_DAMAGE_COLOR)
        pygame.display.update()
        time.sleep(2)
        pygame.quit()
        sys.exit()


    if player.rect.top <= HEIGHT/2:
        player.score += 1
        enemy.score -= 1
        if enemy.score == 0:
            enemy.score = config.ENEMY_SCALING
            enemy.up_dif()
        player.pos.y += abs(player.vel.y)
        good_entities = update_entities(good_entities, player, config.TILE_G_SP, config.TILE_G+1, True)
        bad_entities = update_entities(bad_entities, player, config.TILE_B_SP, config.TILE_B+1, True)
        jump_entities = update_entities(jump_entities, player, config.TILE_J_SP, config.TILE_J+1, True)
        ammo_bags = update_entities(ammo_bags, player, config.AMMO_SP, config.AMMO_AV+1, False)
    
    if current_time - enemy_fired_time >= config.ENEMY_MISSILE_COOL:
        config.ENEMY_MISSILE_SE.play()
        enemy_missiles.append(Missile(enemy.rect.left+25, enemy.rect.bottom+15, 7, 30, config.ENEMY_MISSILE_SP, config.ENEMY_MISSILE_SPEED))
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
                config.PLAYER_PJUMP_SE.play()
                player.jump(config.PLAYER_JUMP_P)
            if event.key == pygame.K_SPACE and player.ammo > 0:                                                             # space / fire missile key
                config.PLAYER_MISSILE_SE.play()
                player_missiles.append(Missile(player.pos.x, player.pos.y-52.5, 5, 25, config.PLAYER_MISSILE_SP, -config.PLAYER_MISSILE_SPEED))
                player.ammo -= 1
            if event.key == pygame.K_LCTRL and current_time - player_force_time >= config.PLAYER_FORCE_COOL:                # left ctrl / fire force key
                config.PLAYER_FORCE_SE.play()
                player_force.append(Missile(player.pos.x, player.pos.y-45, 10, 10, config.PLAYER_FORCE_SP, -config.PLAYER_FORCE_SPEED))
                player_force_time = current_time
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_UP and player.if_jump:                                                                 # up / kill jump key
                player.kill_jump(config.PLAYER_JUMP_K)
        if event.type == QUIT:
            pygame.quit()
            sys.exit()


    pygame.display.update()
    FramePerSec.tick(FPS)