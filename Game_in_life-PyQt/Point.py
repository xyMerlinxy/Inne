from PyQt6 import QtCore, QtGui, QtWidgets

mouse_button_dictionary = {
    QtCore.Qt.MouseButton.LeftButton: 1,
    QtCore.Qt.MouseButton.RightButton: 2,
    QtCore.Qt.MouseButton.MiddleButton: 3
}


class Point(QtWidgets.QLabel):
    text_live = "Jestem żywy"
    text_dead = "Jestem martwy"
    background_live = "background-color: rgb(0, 255, 0);"
    background_dead = "background-color: rgb(255, 0, 0);"

    count_live = 0
    moves = []
    mouse_button_pressed = []
    # 0-nothing, 1-left button,2-right button, 3-middle button
    # left-change to live, right-change to death, middle-change to not
    counter = 0

    def __init__(self, main_application_class, widget, size, state=True):
        super().__init__(widget)
        self.setMinimumSize(size, size)
        self.setMaximumSize(size, size)
        self.setFrameShape(QtWidgets.QFrame.Shape.Panel)

        self.number = self.counter
        Point.counter += 1
        self.app = main_application_class
        self.state = state
        self.update_gui_state()
        self.neighbors = []
        self.sum_live_neighbors = 0
        # click
        self.mousePressEvent = self.mouse_press
        # mouse move
        self.mouseMoveEvent = self.mouse_move
        self.move_mouse_change = False
        # mouse release
        self.mouseReleaseEvent = self.mouse_release

    def update_gui_state(self):
        if self.state:
            self.setStyleSheet(self.background_live)
            self.setStatusTip(self.text_live)
        else:
            self.setStyleSheet(self.background_dead)
            self.setStatusTip(self.text_dead)

    # TODO temp debug
    def change_color(self, event=""):
        if "background-color: rgb(255, 0, 0);" in self.styleSheet():
            self.setStyleSheet("background-color: rgb(0, 255, 0);")
            self.setStatusTip("Jestem żywy")
        else:
            self.setStyleSheet("background-color: rgb(255, 0, 0);")
            self.setStatusTip("Jestem martwy")

    def reset(self):
        self.state = False
        self.update_gui_state()
        self.move_mouse_change = False

    def add_neighbors(self, n):
        self.neighbors.append(n)

    def preparation(self):
        self.sum_live_neighbors = sum(1 for n in self.neighbors if n.state)

    # alive, dead - 8 booleans in array
    def next_turn(self, alive, dead):
        if self.state:
            next_state = alive[self.sum_live_neighbors]
        else:
            next_state = dead[self.sum_live_neighbors]
        if next_state != self.state:
            if next_state:
                Point.count_live += 1
            else:
                Point.count_live -= 1
            self.state = next_state
            self.update_gui_state()
            self.moves.append(self)

    def reverse_state(self):
        if self.state:
            Point.count_live -= 1
        else:
            Point.count_live += 1
        self.state = not self.state
        self.update_gui_state()

    def mouse_press(self, event):
        if len(Point.moves) > 0:
            self.app.add_move(Point.moves)
            for b in Point.moves:
                b.move_mouse_change = False
        Point.moves = []
        Point.mouse_button_pressed.append(mouse_button_dictionary.setdefault(event.button(), 0))
        self.mouse_move(event, self.mapFromGlobal(QtGui.QCursor().pos()))

    def mouse_move(self, event, mouse_position=None):
        if mouse_position is None:
            mouse_position = QtGui.QMouseEvent.position(event)
        button_pos = self.pos()
        first_button_pos = self.app.get_first_button_position()
        x = mouse_position.x() + button_pos.x() - first_button_pos.x()
        y = mouse_position.y() + button_pos.y() - first_button_pos.y()
        size = self.app.get_button_size()
        if 0 < x < self.app.game_table_size[0] and 0 < y < self.app.game_table_size[1]:
            self.app.mouse_tracking_change_button(int(y / size), int(x / size))

    def mouse_tracking_change(self):
        # self.app.statusBarLabel.setText(str(Point.mouse_button_pressed))#temp
        b = Point.mouse_button_pressed[-1]
        if (not self.move_mouse_change) and ((self.state and b == 2) or (not self.state and b == 1) or b == 3):
            if self.state:
                Point.count_live -= 1
            else:
                Point.count_live += 1
            self.move_mouse_change = True
            self.state = not self.state
            self.update_gui_state()
            Point.moves.append(self)
            self.app.update_live_counter()

    def mouse_release(self, event):
        if mouse_button_dictionary.setdefault(event.button(), 0) == Point.mouse_button_pressed[-1]:
            self.app.add_move(Point.moves)
            # self.app.statusBarLabel.setText("End"+str(len(Point.moves)))
            for b in Point.moves:
                b.move_mouse_change = False
            Point.moves = []
        Point.mouse_button_pressed.remove(mouse_button_dictionary.setdefault(event.button(), 0))
