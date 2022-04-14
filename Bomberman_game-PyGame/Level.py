import pygame
from Field import Field
from Player import Player
from Bomb import Bomb
from Events import *
from PowerUp import PowerUp
from Wall import Wall


class Level:

    def __init__(self, game, lvl_name):
        self.game=game

        # load lvl
        self.lvl_name = lvl_name
        self.background = []
        self.walls_list = []
        self.load_map(self.lvl_name)

        # bomb
        self.bomb_images = []
        self.load_bomb_images()
        self.bomb_list: list[Bomb] = []

        # powerup
        self.powerUp_images = []
        self.load_powerup_images()
        self.powerUp_list: list[PowerUp] = []

        # player start position
        psc = [[1, 1], [17, 1], [1, 11], [17, 11]]
        # creating player
        self.all_players: list[Player] = list(
            Player(self.game, self, [psc[i][0] * self.game.size, psc[i][1] * self.game.size], i) for i in range(4)
        )
        self.alive_players: list[Player] = list(self.all_players)
        self.dead_players: list[Player] = []

        # game param
        self.change_direction = 0

        # ending
        self.ending_scane = None
        self.is_end = False

        # frames per second setting

        pygame.display.update()

        # 0 - normal play, 1 - last standing, 2 ending scene
        self.state = 0

    def load_map(self, lvl_name):
        self.background = []

        for i in range(self.game.fields_size[0]):
            self.background.append([])
            for j in range(self.game.fields_size[1]):
                self.background[i].append(0)

        # TODO make validation opened file
        file_map = open(f"map/{lvl_name}", "r")
        graphic_type = file_map.readline()[:-1]
        numbers_of_images = int(file_map.readline()[:-1])
        number_of_map_lines = int(file_map.readline()[:-1])

        loaded_images = []
        for i in range(numbers_of_images):
            print(f'map/{graphic_type}/{i}')
            loaded_images.append(pygame.image.load(f'map/{graphic_type}/{i}.bmp'))

        # TODO check if there is that folder
        for i in range(number_of_map_lines):
            line = file_map.readline()
            for j, field in enumerate(line.split()):
                self.background[j][i] = Field(self.game, self, int(field), [self.game.size * j, self.game.size * i],
                                              loaded_images[int(field)])

        wall_image = pygame.image.load(f'map/{graphic_type}/w0.bmp')
        # load wall cords
        walls_cord = file_map.readline().split(";")
        for cords in walls_cord:
            self.walls_list.append(Wall(self.game, self, list(map(int, cords.split(","))), wall_image))

    def load_bomb_images(self):
        # TODO make rotate image
        self.bomb_images = [
            [pygame.image.load("img/bomb/bomb_0.png"),
             pygame.image.load("img/bomb/bomb_1.png"),
             pygame.image.load("img/bomb/bomb_2.png"),
             pygame.image.load("img/bomb/bomb_3.png"),
             pygame.image.load("img/bomb/bomb_4.png"),
             ],
            [pygame.image.load("img/bomb/explosion_0.png"),
             [pygame.image.load("img/bomb/explosion_10.png"),
              pygame.image.load("img/bomb/explosion_11.png"),
              pygame.image.load("img/bomb/explosion_12.png"),
              pygame.image.load("img/bomb/explosion_13.png")],
             [pygame.image.load("img/bomb/explosion_20.png"),
              pygame.image.load("img/bomb/explosion_21.png"),
              pygame.image.load("img/bomb/explosion_22.png"),
              pygame.image.load("img/bomb/explosion_23.png")]
             ]
        ]

    def load_powerup_images(self):
        number_of_powerups = PowerUp.number_of_powerups
        for i in range(number_of_powerups):
            self.powerUp_images.append(
                pygame.image.load(f"img/powerup/p{i}.png")
            )
        print(self.powerUp_images)

    def remove_player(self, player):
        self.alive_players.remove(player)
        self.dead_players.append(player)

    def end(self):
        # TODO dodać jakisś font z obramówkąm bo na razie to to tak srednio widać
        f = pygame.font.SysFont("Arial", 60, True)
        if len(self.alive_players) == 1:
            text = f"Player {self.alive_players[0].id} wins"
        else:
            text = f"Draw"
        img = f.render(text, False, (0, 0, 0))
        rect = pygame.Rect((0, 0), img.get_size())

        rect.center = (self.game.display_size[0] // 2, self.game.display_size[1] // 2)
        self.game.to_update.append(rect)
        self.game.display.blit(img, rect)

        rise_event(LEVEL_BACK_TO_MENU, 5000)

    def next_frame(self, delta_time):

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN:
                print(event.key)
                for p in self.alive_players:
                    p.press_key(event.key)
            elif event.type == pygame.KEYUP:
                for p in self.alive_players:
                    p.release_key(event.key)
            elif event.type == EVENT_POWERUP_CHANGE_DIRECTION:
                print("Change direction reset")
                self.change_direction = 0
            elif event.type == EVENT_LAST_PLAYER and self.state == 1:
                self.end()
                self.state = 2
            elif event.type == LEVEL_BACK_TO_MENU and self.state == 2:
                self.game.end_lvl()
                return
        if not self.is_end:
            for p in self.alive_players: p.start_move()
            for p in self.alive_players: p.hide()
            for b in self.bomb_list: b.hide()

            for p in self.alive_players: p.move_object()
            for b in self.bomb_list: b.move_object()

            for b in self.bomb_list: b.change_timer(delta_time)
            for p in self.alive_players: p.change_timer(delta_time)
            # for w in self.walls_list: w.draw()
            for u in self.powerUp_list: u.draw()
            for b in self.bomb_list: b.draw()
            for p in self.alive_players: p.draw()

            if len(self.alive_players) == 1 and self.state == 0:
                print("LAST STANDING")
                self.state = 1
                rise_event(EVENT_LAST_PLAYER, 2000)

    def get_background(self, position):  # type: (tuple[int, int])-> Field
        return self.background[position[0]][position[1]]
