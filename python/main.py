import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QTableWidget, QTableWidgetItem, QPushButton, QLineEdit, QLabel

class POSWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        # Layouts
        main_layout = QVBoxLayout()
        input_layout = QHBoxLayout()
        button_layout = QHBoxLayout()
        
        # Table
        self.table = QTableWidget()
        self.table.setRowCount(0)
        self.table.setColumnCount(3)
        self.table.setHorizontalHeaderLabels(['Item', 'Quantity', 'Price'])

        # Input fields
        self.item_input = QLineEdit()
        self.quantity_input = QLineEdit()
        self.price_input = QLineEdit()

        # Buttons
        add_button = QPushButton('Add Item')
        remove_button = QPushButton('Remove Item')

        add_button.clicked.connect(self.addItem)
        remove_button.clicked.connect(self.removeItem)

        # Assemble layouts
        input_layout.addWidget(QLabel('Item:'))
        input_layout.addWidget(self.item_input)
        input_layout.addWidget(QLabel('Quantity:'))
        input_layout.addWidget(self.quantity_input)
        input_layout.addWidget(QLabel('Price:'))
        input_layout.addWidget(self.price_input)

        button_layout.addWidget(add_button)
        button_layout.addWidget(remove_button)

        main_layout.addLayout(input_layout)
        main_layout.addWidget(self.table)
        main_layout.addLayout(button_layout)

        self.setLayout(main_layout)

        # Window settings
        self.setWindowTitle('POS System')
        self.setGeometry(100, 100, 600, 400)

    def addItem(self):
        item = self.item_input.text()
        quantity = self.quantity_input.text()
        price = self.price_input.text()

        if item and quantity and price:
            row_position = self.table.rowCount()
            self.table.insertRow(row_position)
            self.table.setItem(row_position, 0, QTableWidgetItem(item))
            self.table.setItem(row_position, 1, QTableWidgetItem(quantity))
            self.table.setItem(row_position, 2, QTableWidgetItem(price))

            self.item_input.clear()
            self.quantity_input.clear()
            self.price_input.clear()

    def removeItem(self):
        selected_row = self.table.currentRow()
        if selected_row >= 0:
            self.table.removeRow(selected_row)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    pos_window = POSWindow()
    pos_window.show()
    sys.exit(app.exec_())
