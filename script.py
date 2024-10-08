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

out_arr = split_file_by_delimiter(file_path="outputx.txt")
expected_arr = split_file_by_delimiter(file_path="expected.txt" , delimiter='\n')

def split_string_by_newline(input_string):
    split_content = [line.rstrip() for line in input_string.split('\n') if line.strip()]
    return split_content

j = 0

for i in range(len(out_arr)):
    s = split_string_by_newline(out_arr[i])
    for line in s:
        if expected_arr[j]==line:
            j+=1
        else:
            print(f"Failed on test case {i+1}  : expected '{expected_arr[j]}'  , found '{line}'")
            exit()

if(j!=len(expected_arr)):
    print(f"Failed on test case {len(out_arr)}")
else:
    print("All passed")

