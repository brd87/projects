import pygame
import pygame_menu
from pygame_menu import themes

class config:
    def __init__(self):
        self.SE_DIR = "soundef/"
        self.SP_DIR = "sprites/"
        self.GAME_SOUNDTRACK = "soundtrack.wav"
        self.GAME_VOL = 0.05
        self.GAME_BG_SP = pygame.image.load(self.SP_DIR + "background.png")

        self.TILE_G = 10
        self.TILE_B = 2
        self.TILE_J = 2
        self.TILE_G_SP = self.SP_DIR + "good_tile.png"
        self.TILE_B_SP = self.SP_DIR + "bad_tile.png"
        self.TILE_J_SP = self.SP_DIR + "jump_tile.png"
        self.TILE_B_DAMAGE = 1
        self.TILE_J_MULTI = 2

        self.PLAYER_HEALTH = 100
        self.PLAYER_SCORE = 0
        self.PLAYER_ACC = 0.5
        self.PLAYER_FRIC = -0.12
        self.PLAYER_JUMP_P = 15
        self.PLAYER_JUMP_K = 5
        self.PLAYER_MISSILE_SP = self.SP_DIR + "player_missile.png"
        self.PLAYER_MISSILE_SE = pygame.mixer.Sound(self.SE_DIR + "player_laser.wav")
        self.PLAYER_MISSILE_LIMIT = 3
        self.PLAYER_MISSILE_SPEED = 10
        self.PLAYER_FORCE_SP = self.SP_DIR + "force.png"
        self.PLAYER_FORCE_SE = pygame.mixer.Sound(self.SE_DIR + "force.wav")
        self.PLAYER_FORCE_MULTI = 1.5
        self.PLAYER_FORCE_COOL = 3000
        self.PLAYER_FORCE_SPEED = 20
        self.PLAYER_HEALTH_GAIN_COLOR = (0, 255, 0)
        self.PLAYER_HEALTH_GAIN = 10
        self.PLAYER_DAMAGE_COLOR = (255, 0, 0, 128)
        self.PLAYER_DAMAGE_COOL = 2000
        self.PLAYER_DAMAGE_SE = pygame.mixer.Sound(self.SE_DIR + "damage.wav")
        self.PLAYER_DEATH_SE = pygame.mixer.Sound(self.SE_DIR + "death.wav")
        self.PLAYER_PJUMP_SE = pygame.mixer.Sound(self.SE_DIR + "power_jump.wav")

        self.ENEMY_HIT_SE = pygame.mixer.Sound(self.SE_DIR + "enemy_hit.wav")
        self.ENEMY_SCALING = 500
        self.ENEMY_MISSILE_SP = self.SP_DIR + "enemy_missile.png"
        self.ENEMY_MISSILE_SE = pygame.mixer.Sound(self.SE_DIR + "enemy_laser.wav")
        self.ENEMY_MISSILE_COOL = 2000
        self.ENEMY_MISSILE_DAMAGE = 10
        self.ENEMY_MISSILE_SPEED = 10

        self.AMMO_AV = 1
        self.AMMO_SP = self.SP_DIR + "ammo_bag.png"
        self.AMMO_SE = pygame.mixer.Sound(self.SE_DIR + "reload.wav")
        self.AMMO_COUNT = 1

        self.PLAYER_MISSILE_SE.set_volume(self.GAME_VOL)
        self.PLAYER_FORCE_SE.set_volume(self.GAME_VOL)
        self.PLAYER_DAMAGE_SE.set_volume(self.GAME_VOL)
        self.PLAYER_DEATH_SE.set_volume(self.GAME_VOL)
        self.PLAYER_PJUMP_SE.set_volume(self.GAME_VOL)
        self.ENEMY_HIT_SE.set_volume(self.GAME_VOL)
        self.ENEMY_MISSILE_SE.set_volume(self.GAME_VOL)
        self.AMMO_SE.set_volume(self.GAME_VOL)

        self.mainmenu = pygame_menu.Menu("PGplatformer", 600, 400, theme=themes.THEME_DARK)
        self.mainmenu.add.text_input("Playername: ", default='Platbot9000', maxchar=20)
        self.mainmenu.add.button("CLIMB", self.climb)
        self.mainmenu.add.button("Options", self.options)
        self.mainmenu.add.button("Quit", pygame_menu.events.EXIT)


    def climb(self):
        pass


    def options(self):
        #regen, damage, jumping, speed, volume
        pass
