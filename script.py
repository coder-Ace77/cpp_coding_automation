import sys
import re

def split_file_by_delimiter(file_path, delimiter='$'):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            split_content = [part.strip() for part in content.split(delimiter) if part.strip()]
            return split_content
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' was not found.")
        return []
    except Exception as e:
        print(f"An error occurred: {e}")
        return []

def split_string(content, delimiter='|'):
    split_content = [part.strip() for part in content.split(delimiter) if part.strip()]
    return split_content

def split_string_only(input_string,delimiter='\n'):
    split_content = [line.rstrip() for line in input_string.split('\n') if line.strip()]
    return split_content

def store(buffer):
    fl = open("output.txt" , 'w')
    fl.write(buffer)

def separate_debug_lines(input_string):
    debug_lines = ""
    other_lines = ""
    
    for line in input_string.splitlines():
        if not line.startswith("[DEBUG]"):
            other_lines += line + "\n"
        debug_lines += line + "\n"    
    return debug_lines, other_lines


def extract_debug_info(debug_line):
    match = re.match(r"\[DEBUG\] (\d+): (.*)", debug_line)
    if match:
        line_number = int(match.group(1))  
        text = match.group(2) 
        return line_number, text
    else:
        return 0,debug_line

def process_debug_logs(deg_lines):
    l = []
    for line in deg_lines.splitlines():
        if extract_debug_info(line) is not None:
            l.append(extract_debug_info(line))
    # print(l)
    return l

def save_tuples_to_file(tuple_list, filename="log.txt"):
    with open(filename, 'w') as file:
        for tup1, tup2 in tuple_list:
            file.write(f"{tup1},{tup2}\n")



output_str = sys.stdin.read().strip()
deg_lines,output_str = separate_debug_lines(output_str)
processed_debug_logs = process_debug_logs(deg_lines)
save_tuples_to_file(processed_debug_logs)


# print(output_str)    
expected_arr = split_file_by_delimiter(file_path="expected.txt", delimiter='\n')
out_arr = split_string(output_str)
# print(out_arr)


storedStr = output_str.replace('|',' ')

j = 0
for i in range(len(out_arr)):
    s = split_string_only(out_arr[i])
    for line in s:
        if expected_arr[j] == line:
            j += 1
        else:
            print(f"Failed on test case {i+1}  : expected '{expected_arr[j]}'  , found '{line}'")
            store(storedStr)
            exit()

if j != len(expected_arr):
    print(f"Failed on test case {len(out_arr)}")
else:
    print(f"All {len(out_arr)} test cases passed!")
store(storedStr)



