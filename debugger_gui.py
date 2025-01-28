import sys
from PyQt5.QtWidgets import (
    QApplication,
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QTextEdit,
    QLabel,
    QPushButton,
    QShortcut,
)
from PyQt5.QtCore import Qt
import os


def process_text_log_line(s):
    try:
        keys_part, values_part = s.split(" = ")
    except ValueError:
        raise ValueError("Invalid input format. Expected '<key1>@<key2>...<keyn> = <val1>@<val2>...<valn>'")

    keys = keys_part.split(",")
    values = values_part.split("@")

    if len(keys) != len(values):
        raise ValueError("Mismatched number of keys and values.", keys, values)
    return keys, values


def read_file(file_path):
    try:
        with open(file_path, "r") as file:
            content = file.read()
        return content
    except FileNotFoundError:
        return "Error: File not found."
    except PermissionError:
        return "Error: Permission denied."
    except Exception as e:
        return f"Error: {e}"


def read_log_file(filename="log.txt"):
    tuple_list = []
    with open(filename, "r") as file:
        for line in file:
            line = line.strip()
            tup1, tup2 = line.split(",", 1)
            tuple_list.append((int(tup1), tup2))
    return tuple_list


def preprocess_log(l):
    ans = []
    curr_out = ""
    for i in range(len(l)):
        if l[i][0] == 0:
            curr_out += l[i][1].split("|")[0] + "\n"
        else:
            ans.append([l[i][0], l[i][1], curr_out])
    return ans


class DebugApp(QWidget):
    def __init__(self, cpp_code, log_data):
        super().__init__()
        self.cpp_code = cpp_code
        self.log_data = log_data
        self.current_index = 0
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Debug GUI")
        self.setGeometry(100, 100, 1200, 800)
        self.setStyleSheet("background-color: #2e2e2e; padding: 20px;")

        # Main layout
        main_layout = QHBoxLayout()

        # Code display
        self.code_display = QTextEdit()
        self.code_display.setReadOnly(True)
        self.code_display.setFontFamily("Courier")
        self.code_display.setFontPointSize(12)
        self.code_display.setStyleSheet("background-color: #3c3c3c; color: #ffffff; border-radius: 5px; padding: 10px;")
        main_layout.addWidget(self.code_display, 3)

        # Right side layout for variables and output
        right_layout = QVBoxLayout()

        # Variables display
        self.variables_display = QTextEdit()
        self.variables_display.setReadOnly(True)
        self.variables_display.setFontPointSize(12)
        self.variables_display.setStyleSheet("background-color: #404040; color: #ffffff; border-radius: 5px; padding: 10px;")
        right_layout.addWidget(self.variables_display, 2)

        # Output display
        self.output_display = QTextEdit()
        self.output_display.setReadOnly(True)
        self.output_display.setFontPointSize(12)
        self.output_display.setStyleSheet("background-color: #383838; color: #ffffff; border-radius: 5px; padding: 10px;")
        right_layout.addWidget(self.output_display, 1)

        # Navigation buttons
        nav_layout = QHBoxLayout()
        self.prev_button = QPushButton("Previous")
        self.prev_button.setStyleSheet("background-color: #00796b; color: #ffffff; padding: 10px; font-size: 16px; border-radius: 5px;")
        self.prev_button.clicked.connect(self.prev_log)
        self.next_button = QPushButton("Next")
        self.next_button.setStyleSheet("background-color: #00796b; color: #ffffff; padding: 10px; font-size: 16px; border-radius: 5px;")
        self.next_button.clicked.connect(self.next_log)
        nav_layout.addWidget(self.prev_button)
        nav_layout.addWidget(self.next_button)
        right_layout.addLayout(nav_layout)

        main_layout.addLayout(right_layout, 1)
        self.setLayout(main_layout)

        # Add keybindings
        QShortcut(Qt.Key_Left, self).activated.connect(self.prev_log)
        QShortcut(Qt.Key_Right, self).activated.connect(self.next_log)

        # Display initial log
        self.update_display()

    def update_display(self):
        if not self.log_data:
            self.code_display.setText("No DEBUG pointers found!")
            return

        log_entry = self.log_data[self.current_index]
        highlight_line, random_text, output = log_entry

        # Display code with highlight
        lines = self.cpp_code.splitlines()
        start_line = max(highlight_line - 10, 0)
        end_line = min(highlight_line + 20, len(lines))
        relevant_code = "\n".join(lines[start_line:end_line + 1])
        self.code_display.setText(relevant_code)

        # Highlight the specific line
        cursor = self.code_display.textCursor()
        cursor.movePosition(cursor.Start)
        for _ in range(highlight_line - start_line):
            cursor.movePosition(cursor.Down)
        cursor.select(cursor.LineUnderCursor)
        self.code_display.setTextCursor(cursor)

        # Display variables
        keys, values = process_text_log_line(random_text)
        variables_text = "\n".join([f"{key}: {value}" for key, value in zip(keys, values)])
        self.variables_display.setText(variables_text)

        # Display output
        self.output_display.setText(output)

    def prev_log(self):
        if self.current_index > 0:
            self.current_index -= 1
            self.update_display()

    def next_log(self):
        if self.current_index < len(self.log_data) - 1:
            self.current_index += 1
            self.update_display()


if __name__ == "__main__":
    # Read files
    cpp_code = read_file("main.cpp")
    log_data = preprocess_log(read_log_file())

    # Run the application
    app = QApplication(sys.argv)
    window = DebugApp(cpp_code, log_data)
    window.show()
    sys.exit(app.exec_())