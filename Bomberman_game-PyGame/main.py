import pygame
from Level import Level
from Menu import Menu
from Events import *


# TODO ?? Remove from fields object[] and add (wall, power_up,bomb)(solved ??)
# TODO add more powerups (+- fire range, ...)
# PROPOSITION - add destroy wall animation

class Game:

    def __init__(self):
        self.size = 45
        self.fields_size = (19, 13)
        self.display_size = (self.fields_size[0] * self.size, self.fields_size[1] * self.size)

        pygame.init()
        pygame.display.set_caption("Bombowy człowiek")
        self.display = pygame.display.set_mode(self.display_size)

        self.to_update = []

        # frames per second setting
        self.FPS = 60
        self.fpsClock = pygame.time.Clock()
        self.delta_time = 0

        pygame.display.update()

        # 0 - menu, 1 - level
        self.state = 0

        self.level = None
        self.menu = None

    def start_lvl(self):
        self.level = Level(self, "lvl_1")
        print(self.level)
        self.state = 1

    def end_lvl(self):
        print("Ent level")
        self.state = 0
        self.menu.draw()
        # TODO add deleting level
        self.level = None

    def start_game(self):
        self.state = 0
        self.menu = Menu(self)

        while True:
            if self.state == 0: self.menu.next_frame(self.delta_time)
            elif self.state == 1: self.level.next_frame(self.delta_time)

            pygame.display.update(self.to_update)
            self.to_update = []

            self.delta_time = self.fpsClock.tick_busy_loop(self.FPS)
            # self.fpsClock.tick(self.FPS)
            # pygame.time.wait(100)


if __name__ == "__main__":
    new_game = Game()
    new_game.start_game()
