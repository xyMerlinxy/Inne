import sys

from gui_file.Main_Window import Ui_MainWindow
from other_windows import SizeChangeWindow, DataExportWindow, DataImportWindow, import_error_window
from Point import Point
from PyQt6 import QtCore, QtWidgets


class Application(Ui_MainWindow):
    def __init__(self):
        self.width = 43
        self.height = 20
        self.buttons = []
        self.button_size = 12

        self.memory_of_move = []
        self.game_table_size = [0, 0]
        self.timer = QtCore.QTimer()
        self.timer_interval = 200

        self.statusBarInterval = None
        self.statusBarLabel = None
        self.dead_checkbox = None
        self.alive_checkbox = None
        self.main_window = None

    def setupUi(self, main_window):
        super().setupUi(main_window)
        main_window.resize(451, 200)
        self.main_window = main_window
        self.init_statusbar_interval()
        self.init_statusbar_label()
        # Generation game
        self.init_game()
        # navigation button
        self.set_default_button()
        self.button_backward.setEnabled(False)
        self.action_backward.setEnabled(False)
        # action
        self.action_backward.triggered.connect(self.reverse_move)
        self.action_forward.triggered.connect(self.one_turn)
        self.action_reset.triggered.connect(self.reset)
        self.action_change_size.triggered.connect(self.init_size_change_window)
        # checkbox
        self.init_checkbox()
        # timer
        self.set_timer()

        self.action_data_export.triggered.connect(self.init_data_export_window)
        self.action_data_import.triggered.connect(self.init_data_import_window)

    def init_game(self):
        Point.counter = 0
        self.gen_buttons()
        self.adding_neighbors()
        self.centralwidget.adjustSize()
        self.main_window.adjustSize()


    def gen_buttons(self):
        self.buttons = list([] for _ in range(self.height))
        self.centralwidget.hide()
        for i in range(self.height):
            for j in range(self.width):
                new_button = Point(self, self.centralwidget, self.button_size, False)
                self.buttons[i].append(new_button)
                self.game_table.addWidget(new_button, i, j)

        # set margin if needed
        if self.button_size * self.width < 440:
            size = (440 - self.button_size * self.width) // 2
            self.game_table.setContentsMargins(size, 0, size, 0)
        else:
            self.game_table.setContentsMargins(0, 0, 0, 0)
        self.centralwidget.show()
        self.game_table_size = [self.width * self.button_size, self.height * self.button_size]

    def init_checkbox(self):
        self.dead_checkbox = [self.d0, self.d1, self.d2, self.d3, self.d4, self.d5, self.d6, self.d7, self.d8]
        self.alive_checkbox = [self.l0, self.l1, self.l2, self.l3, self.l4, self.l5, self.l6, self.l7, self.l8]
        self.set_default_checkbox()

    def set_default_checkbox(self):
        for c in self.dead_checkbox + self.alive_checkbox:
            c.setChecked(False)
        self.l2.setChecked(True)
        self.l3.setChecked(True)
        self.d3.setChecked(True)

    def init_statusbar_label(self):
        self.statusBarLabel = QtWidgets.QLabel("StatusBarLabel")
        self.statusBarLabel.setAlignment(QtCore.Qt.AlignmentFlag.AlignLeft)
        self.statusBarLabel.setMaximumWidth(70)
        self.statusBarLabel.setMinimumWidth(70)
        self.statusbar.addPermanentWidget(self.statusBarLabel)
        self.update_live_counter()

    def update_live_counter(self):
        self.statusBarLabel.setText(f'Żywych: {Point.count_live}')
        pass

    def init_statusbar_interval(self):
        self.statusBarInterval = QtWidgets.QLabel("StatusBarInterval")
        self.statusBarInterval.setAlignment(QtCore.Qt.AlignmentFlag.AlignLeft)
        self.statusBarInterval.setMaximumWidth(80)
        self.statusBarInterval.setMinimumWidth(80)
        self.statusbar.addPermanentWidget(self.statusBarInterval)
        self.update_interval_on_statusbar()

    def update_interval_on_statusbar(self):
        self.statusBarInterval.setText(f'Interwał: {self.timer_interval}')

    def set_timer(self):
        self.timer.setInterval(self.timer_interval)
        self.timer.setSingleShot(True)
        self.timer.timeout.connect(self.timer_function)
        self.button_start.clicked.connect(self.start_timer)
        self.button_stop.clicked.connect(self.stop_timer)
        self.button_stop.setEnabled(False)

    def start_timer(self):
        self.set_interval_button()
        self.button_stop.setEnabled(True)
        self.button_start.setEnabled(False)
        self.timer.start()

    def stop_timer(self):
        self.set_default_button()
        self.button_stop.setEnabled(False)
        self.button_start.setEnabled(True)
        self.timer.stop()

    def timer_function(self):
        self.one_turn()
        self.timer.start()

    def set_timer_interval(self, direction):
        self.timer_interval = self.timer_interval + 50 if direction else self.timer_interval - 50
        if self.timer_interval < 0: self.timer_interval = 0
        self.timer.setInterval(self.timer_interval)
        self.update_interval_on_statusbar()

    def set_interval_button(self):
        self.button_forward.disconnect()
        self.button_forward.setText("+")
        self.button_forward.clicked.connect(lambda: self.set_timer_interval(True))
        self.button_forward.setShortcut("Right")
        self.button_forward.setStatusTip("Zwiększ interwał (->)")
        self.button_forward.setEnabled(True)
        self.button_forward.setEnabled(True)

        self.button_backward.disconnect()
        self.button_backward.setText("-")
        self.button_backward.clicked.connect(lambda: self.set_timer_interval(False))
        self.button_backward.setShortcut("Left")
        self.button_backward.setStatusTip("Zmniejsz interwał (<-)")
        self.button_backward.setEnabled(True)
        self.action_backward.setEnabled(True)

    def set_default_button(self):
        self.button_forward.disconnect()
        self.button_forward.setStatusTip("Do przodu (->,Ctrl+Y)")
        self.button_forward.setText(">")
        self.button_forward.clicked.connect(self.one_turn)
        self.button_forward.setShortcut("Right")
        self.button_forward.setEnabled(True)

        self.button_backward.disconnect()
        self.button_backward.setStatusTip("Do tyłu (<-,Ctrl+Z)")
        self.button_backward.setText("<")
        self.button_backward.clicked.connect(self.reverse_move)
        self.button_backward.setShortcut("Left")
        self.button_backward.setEnabled(len(self.memory_of_move) != 0)
        self.action_backward.setEnabled(len(self.memory_of_move) != 0)

    def init_size_change_window(self):
        dialog = QtWidgets.QDialog()
        window = SizeChangeWindow()
        window.setupUi(dialog)
        window.setValue(self.height, self.width)
        dialog.exec()
        if dialog.result():
            self.height, self.width = window.getValue()
            self.delete_buttons()
            self.reset()
            self.init_game()

    def delete_buttons(self):
        for bb in self.buttons:
            for b in bb:
                self.game_table.removeWidget(b)
                b.deleteLater()
                # del (b)

    def reset(self):
        for bb in self.buttons:
            for b in bb:
                b.reset()
        Point.count_live = 0
        self.update_live_counter()
        self.set_default_checkbox()
        self.memory_of_move = []
        self.timer.stop()
        self.timer.setInterval(200)
        self.timer_interval = 200
        self.update_interval_on_statusbar()
        self.button_start.setEnabled(True)
        self.button_stop.setEnabled(False)
        self.set_default_button()

    def adding_neighbors(self):
        for i in range(self.height):
            for j in range(self.width):
                h1, h2, w1, w2 = i > 0, i+1 < self.height, j > 0, j+1 < self.width
                if h1:
                    self.buttons[i][j].add_neighbors(self.buttons[i - 1][j])
                    if w2: self.buttons[i][j].add_neighbors(self.buttons[i - 1][j + 1])
                    if w1: self.buttons[i][j].add_neighbors(self.buttons[i - 1][j - 1])
                if w1:
                    self.buttons[i][j].add_neighbors(self.buttons[i][j - 1])
                    if h2: self.buttons[i][j].add_neighbors(self.buttons[i + 1][j - 1])
                if h2: self.buttons[i][j].add_neighbors(self.buttons[i + 1][j])
                if w2:
                    self.buttons[i][j].add_neighbors(self.buttons[i][j + 1])
                    if h2: self.buttons[i][j].add_neighbors(self.buttons[i + 1][j + 1])

    def one_turn(self):
        alive = list(map(lambda x: x.isChecked(), self.alive_checkbox))
        dead = list(map(lambda x: x.isChecked(), self.dead_checkbox))
        # count neighbors
        for i in range(self.height):
            for j in range(self.width):
                self.buttons[i][j].preparation()
        # change state
        self.centralwidget.hide()
        for i in range(self.height):
            for j in range(self.width):
                self.buttons[i][j].next_turn(alive, dead)
        self.centralwidget.show()
        self.update_live_counter()
        self.add_move(Point.moves)
        Point.moves = []

    def add_move(self, moves):
        if len(moves): self.memory_of_move.append(moves)
        if len(self.memory_of_move):
            self.button_backward.setEnabled(True)
            self.action_backward.setEnabled(True)

    # self.statusBarLabel.setText(f'w: {len(self.memory_of_move)} {len(self.memory_of_move[-1])}')

    def reverse_move(self):
        if len(self.memory_of_move):
            self.centralwidget.hide()
            for b in self.memory_of_move[-1]:
                b.reverse_state()
            self.centralwidget.show()
            # self.statusBarLabel.setText(f'w: {len(self.memory_of_move)} {len(self.memory_of_move[-1])}')
            self.update_live_counter()
            self.remove_move()
        else:
            self.button_backward.setEnabled(False)

    def remove_move(self):
        self.memory_of_move = self.memory_of_move[:-1]
        if len(self.memory_of_move) == 0:
            self.button_backward.setEnabled(False)
            self.action_backward.setEnabled(False)

    def init_data_export_window(self):
        data_export_dialog = QtWidgets.QDialog()
        export_window = DataExportWindow()
        export_window.setupUi(data_export_dialog)
        export_window.textEdit.setPlainText(self.prepare_data_to_export())
        export_window.textEdit.setReadOnly(True)
        data_export_dialog.show()
        data_export_dialog.exec()

    def prepare_data_to_export(self):
        data = ''
        data += f'{self.width} {self.height}\n'
        for bb in self.buttons:
            for b in bb:
                data += "1" if b.state else "0"
            data += "\n"
        for i in map(lambda x: x.isChecked(), self.alive_checkbox):
            data += "1" if i else "0"
        data += "\n"
        for i in map(lambda x: x.isChecked(), self.dead_checkbox):
            data += "1" if i else "0"
        data += "\n"
        for m in self.memory_of_move:
            data += " ".join(map(lambda x: str(x.number), m)) + "\n"
        return data[:-1]

    def init_data_import_window(self):
        data_import_dialog = QtWidgets.QDialog()
        import_window = DataImportWindow()
        import_window.setupUi(data_import_dialog)
        import_window.button_ok.clicked.connect(lambda: self.data_import(import_window, data_import_dialog))
        data_import_dialog.show()
        data_import_dialog.exec()

    def data_import(self, import_window, window):

        data = import_window.textEdit.toPlainText()
        try:
            self.check_integrity_data(data)
        except ImportError as ex:
            import_error_window(ex.name)
            return
        else:
            data = data.split("\n")
            while (data[:-1]) == "": data = data[:-1]

            self.data_import_size(data[0].split(" "))

            self.delete_buttons()
            self.reset()
            self.init_game()
            self.data_import_button_state(data[1:1 + self.height])
            self.data_import_checkbox(data[1 + self.height:3 + self.height])
            self.data_import_memory_moves(data[3 + self.height:])
            self.set_default_button()
        window.close()

    def check_integrity_data(self, data):
        data = data.split("\n")
        while (data[:-1]) == "": data = data[:-1]

        if len(data) == 0: raise ImportError(name="Puste dane")
        size = data[0].split(" ")
        try:
            if len(size) != 2: raise IndexError()
            width = int(size[0])
            height = int(size[1])
        except IndexError:
            raise ImportError(name=f'Niepoprawna ilość argumentów w pierwszej lini:\n{data[0]}')
        except Exception:
            raise ImportError(name=f'Niepoprawna pierwsza linia:\n{data[0]}')
        if width > 100 or width < 1: raise ImportError(name="Szerokość poza zakresem")
        if height > 50 or height < 1: raise ImportError(name="Wysokość poza zakresem")
        if len(data) < 3 + height: raise ImportError(name="Zbyt mało lini danych")
        for i, line in enumerate(data[1:1 + height]):
            length = len(line)
            if length > width: raise ImportError(name=f'Linia danych numer {i} jest zbyt długa:\n{line}')
            if length < width: raise ImportError(name=f'Linia danych numer {i} jest zbyt krótka:\n{line}')
            if line.count("1") + line.count("0") != width: raise ImportError(
                name=f'Linia danych numer {i} posiada niepoprawne znaki:\n{line}')
        for i, checkbox in enumerate(data[1 + height:3 + height]):
            length = len(checkbox)
            if length > 9: raise ImportError(name=f'Linia pól wyboru numer {i} jest zbyt długa:\n{checkbox}')
            if length < 9: raise ImportError(name=f'Linia pól wyboru numer {i} jest zbyt krótka:\n{checkbox}')
            if checkbox.count("1") + checkbox.count("0") != 9: raise ImportError(
                name=f'Linia pól wyboru numer {i} posiada niepoprawne znaki:\n{checkbox}')

        for i, memory_line in enumerate(data[3 + height:]):
            d = memory_line.split(" ")
            length = len(d)
            if length == 0: raise ImportError(name=f'Linia pamięci numer {i} jest pusta')
            try:
                for n in d:
                    var = int(n)
                    if var < 0: raise ValueError
            except ValueError:
                raise ImportError(name=f'Linia pamięci numer {i} posiada niepoprawne wartości:\n{memory_line}')

    def data_import_button_state(self, button_state):
        self.centralwidget.hide()
        for line, bb in zip(button_state, self.buttons):
            for state, button in zip(line, bb):
                if state == "1": button.reverse_state()

        self.centralwidget.show()

    def data_import_size(self, size):
        self.width = int(size[0])
        self.height = int(size[1])
        self.statusBarInterval.setText(f'{self.width} {self.height}')

    def data_import_checkbox(self, data):
        for state, checkbox in zip(data[0], self.alive_checkbox):
            checkbox.setChecked(state == "1")
        for state, checkbox in zip(data[1], self.dead_checkbox):
            checkbox.setChecked(state == "1")

    def data_import_memory_moves(self, data):
        for memory_line in data:
            moves = []
            for point in map(int, memory_line.split(" ")):
                moves.append(self.buttons[point // self.width][point % self.width])
            self.memory_of_move.append(moves)

    def get_first_button_position(self): return self.buttons[0][0].pos()
    def mouse_tracking_change_button(self, x, y): self.buttons[x][y].mouse_tracking_change()
    def get_button_size(self): return self.button_size
