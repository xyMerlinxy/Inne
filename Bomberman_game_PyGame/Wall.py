import pygame
from Object import Object
from PowerUp import PowerUp


class Wall(Object):

    def __init__(self, game, level, position: list[int, int],
                 image: pygame.Surface):
        super().__init__(game, level,  [game.size * position[0], game.size * position[1]], image)
        self.background = self.level.get_background(position)
        self.background.add_object(self)
        self.pos = position
        self.is_deleted = False

    def destroy(self):
        #self.game.to_update.append(self.background)
        # self.background.remove_object(self)
        # self.level.walls_list.remove(self)
        #self.background.draw()
        #
        # PowerUp(self.game, self.level, self.pos)

        return True

    def delete(self):
        if not self.is_deleted:
            self.is_deleted = True
            self.background.remove_object(self)
            self.level.walls_list.remove(self)
            self.background.draw()
            PowerUp(self.game, self.level, self.pos)