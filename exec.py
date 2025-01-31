import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QTextEdit, QLabel, QPushButton, QShortcut
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QKeySequence
import subprocess

class FileEditor(QWidget):
    def __init__(self, filename, title, bg_color, text_color):
        super().__init__()
        self.filename = filename
        self.title = title
        self.bg_color = bg_color
        self.text_color = text_color
        self.initUI()

    def initUI(self):
        self.setWindowTitle(f"Edit {self.filename}")
        
        title_label = QLabel(self.title, self)
        title_label.setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px; color: #f5f5f5;")

        self.text_edit = QTextEdit(self)
        self.text_edit.setPlaceholderText(f"Edit content of {self.filename}...")
        self.text_edit.setStyleSheet(f"background-color: {self.bg_color}; color: {self.text_color}; font-size: 14px; border-radius: 5px; padding: 10px;")
        
        self.load_file()

        self.text_edit.textChanged.connect(self.auto_save_file)

        layout = QVBoxLayout()
        layout.addWidget(title_label)
        layout.addWidget(self.text_edit)

        self.setLayout(layout)

    def load_file(self):
        """Load the content from the file into the QTextEdit widget."""
        try:
            with open(self.filename, 'r') as file:
                content = file.read()
                self.text_edit.setText(content)
        except FileNotFoundError:
            self.text_edit.clear()

    def auto_save_file(self):
        """Automatically save the content of the QTextEdit widget back to the file."""
        with open(self.filename, 'w') as file:
            content = self.text_edit.toPlainText()
            file.write(content)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Script Tester")
        self.setStyleSheet("background-color: #2e2e2e; padding: 20px;")

        self.input_editor = FileEditor('input.txt', "Input", "#3c3c3c", "#ffffff")
        self.output_editor = FileEditor('output.txt', "Output", "#404040", "#ffffff")
        self.expected_editor = FileEditor('expected.txt', "Expected", "#383838", "#ffffff")

        self.run_button = QPushButton("Run", self)
        self.run_button.setStyleSheet("background-color: #00796b; color: #ffffff; padding: 10px; font-size: 16px; border-radius: 5px;")
        self.run_button.clicked.connect(self.run_script)

        self.script_button = QPushButton("Debug", self)
        self.script_button.setStyleSheet("background-color: #00796b; color: #ffffff; padding: 10px; font-size: 16px; border-radius: 5px;")
        self.script_button.clicked.connect(self.debug_script)

        # Correct the QShortcut usage for Ctrl+R (previous log)
        QShortcut(QKeySequence("Ctrl+R"), self).activated.connect(self.run_script)
        
        # You can also add the shortcut for right arrow if needed:
        QShortcut(QKeySequence("Ctrl+D"), self).activated.connect(self.debug_script)

        # Add a QTextEdit widget to display the script output
        self.output_display = QTextEdit(self)
        self.output_display.setStyleSheet("background-color: #333333; color: #ffffff; font-size: 14px; padding: 10px;")
        self.output_display.setReadOnly(True)
        self.output_display.setPlaceholderText("Script output will be displayed here...")

        layout = QVBoxLayout()
        layout.addWidget(self.input_editor)
        layout.addWidget(self.output_editor)
        layout.addWidget(self.expected_editor)
        layout.addWidget(self.run_button)
        layout.addWidget(self.script_button)
        layout.addWidget(self.output_display)  # Add the output display to the layout
        self.setLayout(layout)
        self.resize(600, 800)  # Adjust the window size to accommodate the output display
        self.show()

    def run_script(self):
        """Execute the script and display the output in the same window."""
        try:
            result = subprocess.run(['bash', 'script.sh'], capture_output=True, text=True, check=True)
            output_text = result.stdout
        except subprocess.CalledProcessError as e:
            output_text = f"Error executing script:\n{e.stderr}"
        self.output_display.setPlainText(output_text)  # Display the output in the QTextEdit widget
        self.input_editor.load_file()
        self.output_editor.load_file()
        self.expected_editor.load_file()

    def debug_script(self):
        """Execute the script in debug mode and display the output in the same window."""
        try:
            result = subprocess.run(['bash', 'script.sh', '-dg'], capture_output=True, text=True, check=True)
            output_text = result.stdout
        except subprocess.CalledProcessError as e:
            output_text = f"Error executing script:\n{e.stderr}"
        self.output_display.setPlainText(output_text)  # Display the output in the QTextEdit widget
        self.input_editor.load_file()
        self.output_editor.load_file()
        self.expected_editor.load_file()

    def prev_log(self):
        """Handle the action for Ctrl+R shortcut to go to previous log."""
        print("Previous Log")

    def next_log(self):
        """Handle the action for right arrow key to go to next log."""
        print("Next Log")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())