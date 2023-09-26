import os
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
        self.GAME_MSOUNDTRACK = "soundtrack_menu.wav"
        self.SE_VOL = 0.05
        self.MUSIC_VOL = 0.05
        self.GAME_BG_SP_PATH = self.SP_DIR + "background.png"
        self.GAME_MBG_SP_PATH = self.SP_DIR + "background_menu.png"
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
        # self.PLAYER_UESRNAME defined in #menu
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
        self.PLAYER_PJUMP_SE = pygame.mixer.Sound(self.SE_DIR + "jump.wav")

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


        # menu
        pygame.mixer.music.load(self.SE_DIR + self.GAME_MSOUNDTRACK)
        pygame.mixer.music.set_volume(self.MUSIC_VOL)
        pygame.mixer.music.play(-1)
        self.PLAYER_PJUMP_SE.set_volume(self.SE_VOL)
        PGp_bg = pygame_menu.baseimage.BaseImage(image_path=self.GAME_MBG_SP_PATH, drawing_mode=pygame_menu.baseimage.IMAGE_MODE_CENTER)
        PGp_theme = pygame_menu.themes.Theme(
            background_color=PGp_bg, 
            widget_font=pygame_menu.font.FONT_MUNRO, 
            widget_font_size=25, 
            widget_font_color=(255, 255, 255), 
            title_bar_style=pygame_menu.widgets.MENUBAR_STYLE_NONE, 
            title_font=pygame_menu.font.FONT_8BIT
            )

        self.main_menu = pygame_menu.Menu("PGplatformer", WIDTH, HEIGHT, theme = PGp_theme)
        self.PLAYER_UESRNAME_input = self.main_menu.add.text_input("Playername ", default = "Platbot9000", maxchar = 20)
        self.main_menu.add.button("CLIMB", self.climb)
        self.main_menu.add.button("Scores", self.scores)
        self.main_menu.add.button("Options", self.settings)
        self.main_menu.add.button("Quit", pygame_menu.events.EXIT)

        self.settings_menu = pygame_menu.Menu("Options", WIDTH, HEIGHT, theme = PGp_theme)
        self.settings_menu.add.selector("Difficulty", [("Normal", 10, 10, 15, 10, 1), ("Hard", 5, 20, 15, 8, 2), ("Lethal", 5, 95, 15, 10, 4), ("Easy", 20, 5, 17, 15, 0)], onchange = self.dif_settings)
        self.settings_menu.add.range_slider("Soundtrack", default=self.MUSIC_VOL, range_values=(0, 1), increment=0.05, onchange=self.musicv_settings)
        self.settings_menu.add.range_slider("Sound Effects", default=self.SE_VOL, range_values=(0, 1), increment=0.05, onchange=self.sev_settings)
        self.settings_menu.add.button("Back", self.quit_settings)

        self.scores_menu = pygame_menu.Menu("Scores", WIDTH, HEIGHT, theme = PGp_theme)
        # defined in scores()


    def climb(self):
        self.PLAYER_PJUMP_SE.play()
        
        self.PLAYER_UESRNAME = self.PLAYER_UESRNAME_input.get_value()
        if ";;" in self.PLAYER_UESRNAME:
            self.PLAYER_UESRNAME = self.PLAYER_UESRNAME.strip(";;")
        if self.PLAYER_UESRNAME.strip() == "":
            self.PLAYER_UESRNAME = "Platbot9000"
        self.PLAYER_MISSILE_SE.set_volume(self.SE_VOL)
        self.PLAYER_FORCE_SE.set_volume(self.SE_VOL)
        self.PLAYER_DAMAGE_SE.set_volume(self.SE_VOL)
        self.PLAYER_DEATH_SE.set_volume(self.SE_VOL)
        self.PLAYER_PJUMP_SE.set_volume(self.SE_VOL)
        self.ENEMY_HIT_SE.set_volume(self.SE_VOL)
        self.ENEMY_MISSILE_SE.set_volume(self.SE_VOL)
        self.AMMO_SE.set_volume(self.SE_VOL)

        self.main_menu.disable()


    def scores(self):
        self.PLAYER_PJUMP_SE.play()
        self.scores_menu.clear()
        self.scores_menu.add.label("Player Scores\n--------------------------")
        if os.path.exists("player_scores.txt"):
            score_table = self.scores_menu.add.table()
            score_table.default_cell_padding=5
            score_table.add_row(("Rank", "Username\t\t", "Score"), cell_font_size=20, cell_border_width=0)
            with open("player_scores.txt", "r", encoding="utf-8") as file:
                rank = 1
                for line in file:
                    line = line.split(";;")
                    score_table.add_row((f"{rank}.", f"{line[0]}", line[1].rstrip()), cell_font_size=20, cell_border_width=0)
                    rank += 1
        else:
            self.scores_menu.add.label("No one played yet :(")
        self.scores_menu.add.button("Back", self.quit_scores)
        self.main_menu._open(self.scores_menu)


    def quit_scores(self):
        self.PLAYER_PJUMP_SE.play()
        self.scores_menu.reset(1)
    

    def settings(self):
        self.PLAYER_PJUMP_SE.play()
        self.main_menu._open(self.settings_menu)


    def quit_settings(self):
        self.PLAYER_PJUMP_SE.play()
        self.settings_menu.reset(1)


    def dif_settings(self, selected, PLAYER_HEALTH_GAIN, ENEMY_MISSILE_DAMAGE, PLAYER_JUMP_P, PLAYER_MISSILE_SPEED, SCORE_MULTI):
        self.PLAYER_PJUMP_SE.play()
        self.PLAYER_HEALTH_GAIN = PLAYER_HEALTH_GAIN
        self.ENEMY_MISSILE_DAMAGE = ENEMY_MISSILE_DAMAGE
        self.PLAYER_JUMP_P = PLAYER_JUMP_P
        self.PLAYER_MISSILE_SPEED = PLAYER_MISSILE_SPEED
        self.SCORE_MULTI = SCORE_MULTI
    
    
    def musicv_settings(self, MUSIC_VOL):
        self.MUSIC_VOL = MUSIC_VOL
        pygame.mixer.music.set_volume(self.MUSIC_VOL)
        self.PLAYER_PJUMP_SE.play()


    def sev_settings(self, SE_VOL):
        self.SE_VOL = SE_VOL
        self.PLAYER_PJUMP_SE.set_volume(self.SE_VOL)
        self.PLAYER_PJUMP_SE.play()
