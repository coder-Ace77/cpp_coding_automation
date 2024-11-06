import re
import os

pattern = r'import\("(.*?)"\)'

def read_modules():
    with open("lib/.data", 'r') as f:
        modules = f.readlines()
    mp = {}
    for i in modules:
        arr = i.strip().split(',')
        if len(arr) == 2:
            mp[arr[0]] = arr[1] 
    return mp

def split_string_only(input_string):
    return input_string.splitlines(keepends=True)  

def read_file_content(file_path):
    if os.path.exists(file_path):
        with open(file_path, 'r') as f:
            return f.read()
    else:
        print(f'[File "{file_path}" not found.]')
        return ''

def parse(filename="main.cpp"): 
    module_map = read_modules()
    with open(filename, 'r') as f:
        text = f.read()
    
    cmds = split_string_only(text)
    out = []

    cnts = 0

    for cmd in cmds:
        match = re.search(pattern, cmd)
        if match and cmd.startswith("import("):
            inner_text = match.group(1)
            if inner_text in module_map:
                cnts+=1
                module_content = read_file_content(module_map[inner_text])
                cmd = cmd.replace(match.group(0), module_content)
            else:
                print(f'[Err : module "{inner_text}" not found.]')
                exit(1)

        out.append(cmd)

    if cnts>0:
        with open(filename, 'w') as out_file:
            out_file.writelines(out)  

    return out

if __name__ == "__main__":
    parse()
    print("[Linked.]",end="")
