import sys

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

def split_string(content, delimiter='$'):
    split_content = [part.strip() for part in content.split(delimiter) if part.strip()]
    return split_content

def split_string_only(input_string,delimiter='\n'):
    split_content = [line.rstrip() for line in input_string.split('\n') if line.strip()]
    return split_content

def store(buffer):
    fl = open("output.txt" , 'w')
    fl.write(buffer)

output_str = sys.stdin.read().strip()    
expected_arr = split_file_by_delimiter(file_path="expected.txt", delimiter='\n')
out_arr = split_string(output_str)

storedStr = output_str.replace('$',' ')


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



