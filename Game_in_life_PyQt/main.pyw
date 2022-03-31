from Application import Application
from PyQt6 import QtWidgets

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Application()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec())
