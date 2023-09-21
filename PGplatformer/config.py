import pygame
import pygame_menu
from pygame_menu import themes

class Config:
    def __init__(self, WIDTH, HEIGHT):

        # general
        self.SE_DIR = "soundef/"
        self.SP_DIR = "sprites/"
        self.SCORE_MULTI = 1
        self.GAME_SOUNDTRACK = "soundtrack.wav"
        self.SE_VOL = 0.05
        self.MUSIC_VOL = 0.05
        self.GAME_BG_SP_PATH = self.SP_DIR + "background.png"
        self.GAME_BG_SP = pygame.image.load(self.GAME_BG_SP_PATH)

        # tiles
        self.TILE_G = 10
        self.TILE_B = 2
        self.TILE_J = 2
        self.TILE_G_SP = self.SP_DIR + "good_tile.png"
        self.TILE_B_SP = self.SP_DIR + "bad_tile.png"
        self.TILE_J_SP = self.SP_DIR + "jump_tile.png"
        self.TILE_B_DAMAGE = 5
        self.TILE_J_MULTI = 2

        # player
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

        # enemy
        self.ENEMY_HIT_SE = pygame.mixer.Sound(self.SE_DIR + "enemy_hit.wav")
        self.ENEMY_SCALING = 500
        self.ENEMY_MISSILE_SP = self.SP_DIR + "enemy_missile.png"
        self.ENEMY_MISSILE_SE = pygame.mixer.Sound(self.SE_DIR + "enemy_laser.wav")
        self.ENEMY_MISSILE_COOL = 2000
        self.ENEMY_MISSILE_DAMAGE = 10
        self.ENEMY_MISSILE_SPEED = 10

        # items
        self.AMMO_AV = 1
        self.AMMO_SP = self.SP_DIR + "ammo_bag.png"
        self.AMMO_SE = pygame.mixer.Sound(self.SE_DIR + "reload.wav")
        self.AMMO_COUNT = 1

        self.main_menu = pygame_menu.Menu("PGplatformer", WIDTH, HEIGHT, theme = themes.THEME_DARK)
        self.main_menu.add.text_input("Playername: ", default = 'Platbot9000', maxchar = 20)
        self.main_menu.add.button("CLIMB", self.climb)
        self.main_menu.add.button("Options", self.settings)
        self.main_menu.add.button("Quit", pygame_menu.events.EXIT)

        self.set_menu = pygame_menu.Menu("Options", WIDTH, HEIGHT, theme = themes.THEME_DARK)
        self.set_menu.add.selector("Difficulty:", [("Normal", 10, 10, 15, 10, 1), ("Hard", 5, 20, 15, 8, 2), ("Lethal", 5, 95, 15, 10, 4), ("Easy", 20, 5, 17, 15, 0)], onchange = self.dif_options)
        self.set_menu.add.range_slider("Soundtrack", default=self.MUSIC_VOL, range_values=(0, 1), increment=0.05, onchange=self.musicv_options)
        self.set_menu.add.range_slider("Sound Effects", default=self.SE_VOL, range_values=(0, 1), increment=0.05, onchange=self.sev_options)
        self.set_menu.add.button("Back", self.quit_options)

    def climb(self):
        self.main_menu.disable()

        self.PLAYER_MISSILE_SE.set_volume(self.SE_VOL)
        self.PLAYER_FORCE_SE.set_volume(self.SE_VOL)
        self.PLAYER_DAMAGE_SE.set_volume(self.SE_VOL)
        self.PLAYER_DEATH_SE.set_volume(self.SE_VOL)
        self.PLAYER_PJUMP_SE.set_volume(self.SE_VOL)
        self.ENEMY_HIT_SE.set_volume(self.SE_VOL)
        self.ENEMY_MISSILE_SE.set_volume(self.SE_VOL)
        self.AMMO_SE.set_volume(self.SE_VOL)


    def settings(self):
        self.main_menu._open(self.set_menu)


    def quit_options(self):
        self.set_menu.reset(1)


    def dif_options(self, selected, PLAYER_HEALTH_GAIN, ENEMY_MISSILE_DAMAGE, PLAYER_JUMP_P, PLAYER_MISSILE_SPEED, SCORE_MULTI):
        self.PLAYER_HEALTH_GAIN = PLAYER_HEALTH_GAIN
        self.ENEMY_MISSILE_DAMAGE = ENEMY_MISSILE_DAMAGE
        self.PLAYER_JUMP_P = PLAYER_JUMP_P
        self.PLAYER_MISSILE_SPEED = PLAYER_MISSILE_SPEED
        self.SCORE_MULTI = SCORE_MULTI
    
    
    def musicv_options(self, MUSIC_VOL):
        self.MUSIC_VOL = MUSIC_VOL


    def sev_options(self, SE_VOL):
        self.SE_VOL = SE_VOL
