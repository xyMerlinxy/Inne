from gui_file.Size_Change_Widget import Ui_Size_change_popup
from gui_file.Data_Export import Ui_Data_export
from gui_file.Data_Import import Ui_Data_import
from gui_file.Import_Error import Ui_Error_import
from PyQt6 import QtWidgets


class SizeChangeWindow(Ui_Size_change_popup):
    def __init__(self): super()

    def setupUi(self, dialog):
        super().setupUi(dialog)

    def setValue(self, height, width):
        self.width.setValue(width)
        self.height.setValue(height)

    def getValue(self):
        return self.height.value(), self.width.value()


class DataExportWindow(Ui_Data_export):
    def __init__(self) -> None:
        super().__init__()

    def setupUi(self, data_export):
        super().setupUi(data_export)
        self.button_copy_to_clipboard.clicked.connect(
            lambda: QtWidgets.QApplication.clipboard().setText(self.textEdit.toPlainText()))


class DataImportWindow(Ui_Data_import):
    def __init__(self) -> None:
        super().__init__()

    def setupUi(self, data_import):
        super().setupUi(data_import)
        self.button_pase_from_clipboard.clicked.connect(self.button_past_clicked)

    def button_past_clicked(self):
        self.textEdit.setText(QtWidgets.QApplication.clipboard().text())


def import_error_window(text):
    error_import = QtWidgets.QDialog()
    ui = Ui_Error_import()
    ui.setupUi(error_import)
    ui.error_text.setText(text)
    error_import.show()
    error_import.exec()
