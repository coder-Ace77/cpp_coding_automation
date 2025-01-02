from rich.console import Console
from rich.syntax import Syntax
from rich.panel import Panel
from rich.columns import Columns
from rich.layout import Layout
import os
import time

def process_text_log_line(s):
    try:
        keys_part, values_part = s.split(" = ")
    except ValueError:
        raise ValueError("Invalid input format. Expected '<key1>@<key2>...<keyn> = <val1>@<val2>...<valn>'")

    keys = keys_part.split(",")
    values = values_part.split("@")

    if len(keys) != len(values):
        raise ValueError("Mismatched number of keys and values." , keys,values)
    return keys, values



def display_with_highlight(cpp_code: str, random_text: str, highlight_line: int):
    console = Console()
    lines = cpp_code.splitlines()
    start_line = max(highlight_line - 10, 0)  
    end_line = min(highlight_line + 20, len(lines))
    relevant_code = "\n".join(lines[start_line:end_line + 1])
    highlighted_code = ""
    for i, line in enumerate(relevant_code.splitlines(), start=start_line + 1):
        if i == highlight_line:
            highlighted_code += f"{line}\n"
        else:
            highlighted_code += line + "\n"

    cpp_syntax = Syntax(
        highlighted_code, 
        "cpp", 
        theme="monokai", 
        line_numbers=True, 
        highlight_lines={highlight_line - start_line}
    )
    cpp_panel = Panel(cpp_syntax, title="Code")
    var , vals = process_text_log_line(random_text)
    l=[]
    for i in range(len(var)):
        text_panel = Panel(vals[i], title=var[i], border_style="green",width=40) 
        l.append(text_panel)

    layout = Layout()

    layout.split_row(
        Layout(cpp_panel, ratio=3),  
        Layout(Columns(l), ratio=1) 
    )

    outer_panel = Panel(layout, title="Debug", border_style="magenta", height=37)


    console.print(outer_panel)


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

cpp_code = read_file("main.cpp")

def read_log_file(filename="log.txt"):
    tuple_list = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            tup1, tup2 = line.split(",", 1)
            tuple_list.append((int(tup1), tup2))
    return tuple_list

l = read_log_file()

import sys
import tty
import termios

def get_arrow_key():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        key = sys.stdin.read(3)  
        if key == '\x1b[A': 
            return "Up Arrow"
        elif key == '\x1b[B': 
            return "Down Arrow"
        elif key == '\x1b[D': 
            return "Left Arrow"
        elif key == '\x1b[C': 
            return "Right Arrow"
        else:
            return "Not an arrow key"
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

i = 0
while True:
    os.system("clear")

    if i<0:
        i=0
    if i>=len(l):
        i=len(l)-1
        
    display_with_highlight(cpp_code,l[i][1],l[i][0])
    n=get_arrow_key()
    if n=="Right Arrow":
        i+=1
    elif n=="Left Arrow":
        i-=1
    else:
        break
    time.sleep(0.005)
