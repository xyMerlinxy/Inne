from Field import Field
from Object import Object

FIRE_TYPE_CENTER = 0
FIRE_TYPE_HORIZONTAL = 1
FIRE_TYPE_VERTICAL = 2


class FireSegment(Object):
    def __init__(self, game, level, cords, image, possibility_of_entry, fire_type):
        rect_offset = (10 if fire_type == 2 else 0, 10 if fire_type == 1 else 0)
        rect_size = (game.size - (20 if fire_type == 2 else 0), game.size - (20 if fire_type == 1 else 0))
        super().__init__(game, level, cords, image, possibility_of_entry, rect_offset, rect_size)


class Fire:
    def __init__(self, game, level, bomb, begin_position: list[int, int], direction: int = 0, power: int = 0):
        self.owner = bomb
        self.game = game
        self.level = level
        self.begin_position: list[int, int] = list(begin_position)

        self.my_background: list[Field] = []

        self.type = FIRE_TYPE_CENTER if direction == 4 else (
            FIRE_TYPE_VERTICAL if direction == 0 or direction == 2 else FIRE_TYPE_HORIZONTAL)

        self.destroyed_object = []

        # center of fire
        if direction == 4:
            pos = begin_position
            img = self.level.bomb_images[1][0]
            field = self.level.get_background(pos)
            self.my_background.append(field)
            self.fire_segments = [
                FireSegment(self.game, self.level, [self.game.size * pos[0], self.game.size * pos[1]], img, True, self.type)]
            self.my_background.append(field)

            # destroy object under fire
            self.destroyed_object += field.destroy()


            field.add_object(self.fire_segments[0])

        else:
            self.images = [self.level.bomb_images[1][1][direction],
                           self.level.bomb_images[1][2][direction]]
            self.fire_segments: list[FireSegment] = []

        self.direction = direction
        self.power = power

        self.type = [1, 2][direction % 2] if direction != 4 else 0

        self.next()

    def next(self):
        if self.power > 0:
            self.power -= 1
            if self.direction == 0:
                self.begin_position[0] -= 1
            elif self.direction == 1:
                self.begin_position[1] -= 1
            elif self.direction == 2:
                self.begin_position[0] += 1
            elif self.direction == 3:
                self.begin_position[1] += 1

            pos = self.begin_position
            if len(self.fire_segments): self.fire_segments[-1].set_image(self.images[0])

            field = self.level.get_background(pos)

            temp_list = field.destroy()
            is_destroyed = len(temp_list) > 0
            self.destroyed_object += temp_list
            if is_destroyed: self.power = 0

            if field.can_entry() or is_destroyed:
                print("New segment:",pos)
                fire_segment = FireSegment(self.game, self.level, [self.game.size * pos[0], self.game.size * pos[1]],
                                           self.images[1],
                                           True, self.type)
                self.fire_segments.append(fire_segment)
                self.my_background.append(field)
                field.add_object(fire_segment)
            else:
                self.power = 0

    def draw(self):
        for o in self.destroyed_object: o.draw()
        for f in self.fire_segments: f.draw()


    def hide(self):
        for f in self.my_background: f.draw()

    def delete(self):
        self.hide()
        for fire, field in zip(self.fire_segments, self.my_background):
            field.remove_object(fire)

        self.fire_segments = []
        self.my_background = []
        self.owner = None
        for o in self.destroyed_object: o.delete()
