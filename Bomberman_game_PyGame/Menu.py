import pygame
from Button import Button


class Menu:
    def __init__(self, game):
        self.game = game
        self.background = pygame.image.load("img/menu/background.png")
        self.background_rect = pygame.Rect((0, 0), (855, 585))



        self.object = []
        # start button
        img = pygame.image.load("img/menu/button_start.png")
        self.object.append(
            Button(self.game, self, (427, 300), (84, 50), img,
                   lambda: self.game.start_lvl(),
                   True
                   ))

        self.draw()

    def draw(self):
        self.game.display.blit(self.background, (0, 0))
        self.game.to_update.append(self.background_rect)
        for o in self.object:
            o.draw()

    def next_frame(self, delta_time):

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                for o in self.object:
                    o.click(pos)
