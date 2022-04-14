import random

import pygame

import Player
from Object import Object
import Events


class PowerUp(Object):
    number_of_powerups = 8

    def __init__(self, game, level, position: list[int, int]):
        # id [bomb +1, bomb -1, insensitivity,speed +, speed -, kick, change direction]
        # TODO balance drop rate
        # self.id = random.randint(0, 7)
        # self.id=random.randint(3,4)
        self.id = 5
        super().__init__(game, level,
                         [game.size * position[0], game.size * position[1]],
                         level.powerUp_images[self.id],
                         True, (5, 5),
                         (game.size - 10, game.size - 10)
                         )
        self.level.powerUp_list.append(self)
        self.background = self.level.get_background(position)
        self.background.add_object(self)

        self.is_deleted = False

        print(self.background.object)

    def destroy(self):
        return True

    def delete(self):
        if not self.is_deleted:
            self.is_deleted = True
            self.background.remove_object(self)
            self.level.powerUp_list.remove(self)
            self.background.draw()

    def collect(self, player: Player):
        self.is_deleted = True
        self.background.remove_object(self)
        self.level.powerUp_list.remove(self)
        self.background.draw()

        if self.id == 0:
            player.bomb_max += 1
            # TODO move check player max_bomb to setter
        elif self.id == 1 and player.bomb_max > 1:
            player.bomb_max -= 1
        elif self.id == 2:
            player.insensitivity_on()
        elif self.id == 3:
            player.speed *= 1.5
            print("Speed:", player.speed)
            # TODO move check player max_bomb to setter
        elif self.id == 4 and player.speed > 1.5:
            player.speed = player.speed / 150 * 100
            if player.speed < 1.5: player.speed = 1.5
            print("Speed:", player.speed)
        elif self.id == 5:
            player.ability_to_kick = True
        elif self.id == 6:
            self.level.change_direction=random.randint(1,3)
            print(f"Direction changed by {self.level.change_direction}")
            Events.rise_event(Events.EVENT_POWERUP_CHANGE_DIRECTION, 8000)
        elif self.id == 7:
            player.bomb_power += 1
