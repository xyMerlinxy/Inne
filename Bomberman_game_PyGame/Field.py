import pygame

from Object import Object

class Field(Object):
    def __init__(self, game, level, name, cords, image):
        self.name = name
        super().__init__(game, level, cords, image, self.name == 0)

        self.object = []
        self.number_of_player = 0

    def __str__(self):
        return f"Cords: {self.cords} Name: {self.name} Entry: {self.possibility_of_entry}"

    def can_entry(self):
        return self.possibility_of_entry and sum(obj.can_entry() for obj in self.object) == len(self.object)

    def can_entry_bomb(self): return self.can_entry() and self.number_of_player == 0

    def can_kick(self):
        return 0 < len(self.object) == sum(obj.can_kick() for obj in self.object)

    def kick(self, direction):
        for o in self.object:
            if o.kick(direction): return True
        return False

    def add_object(self, obj: Object):
        self.object.append(obj)

    def remove_object(self, obj: Object):
        if obj in self.object: self.object.remove(obj)

    def destroy(self):
        return list(o for o in self.object if o.destroy())
