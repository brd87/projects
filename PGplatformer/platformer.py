import pygame
import sys
from pygame.locals import *

from player import Player
from goodplatform import GoodPlatform


pygame.init()

window_size = (500, 500)

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

player = Player(500, 500, c_white, ACC, FRIC)
g_plat = GoodPlatform(500, 500, c_green)
entities = []
entities.append(player)
entities.append(g_plat)

def draw(entities):
    DISPLAY.fill(c_black)
    for entity in entities:
        DISPLAY.blit(entity.surf, entity.rect)

while True:
    draw(entities)
    player.move()
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE: # esc / quit key
                pygame.quit()
                sys.exit()
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()
    FramePerSec.tick(FPS)
