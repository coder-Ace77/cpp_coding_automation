import subprocess
import time

def execute_python(file):
    result = subprocess.run(["python3", file], capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError(f"Error executing {file}: {result.stderr}")
    return result.stdout.strip()

def compile_cpp(file, output):
    result = subprocess.run(
        ["g++", "-std=c++17", "-include", "pch.h", file, "-o", output],
        capture_output=True,
        text=True
    )
    if result.returncode != 0:
        raise RuntimeError(f"Compilation failed for {file}: {result.stderr}")


def execute_cpp(executable, input_data):
    result = subprocess.run([f"./{executable}"], input=input_data, capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError(f"Error executing {executable}: {result.stderr}")
    return result.stdout.strip()

def main():
    print("Enter number of test loops to run",end=":")
    
    compile_cpp("correct.cpp", "correct")
    compile_cpp("main.cpp", "main")

    num_tests = int(input())

    for test_index in range(1, num_tests + 1):
        print(f"\nRunning testing file {test_index}...")
        
        test_cases = execute_python("testcode.py")

        expected_output = execute_cpp("correct", test_cases)

        actual_output = execute_cpp("main", test_cases)

        test_cases_lines = test_cases.splitlines()
        expected_lines = expected_output.splitlines()
        actual_lines = actual_output.splitlines()

        print("\nComparison:")
        for i, test in enumerate(test_cases_lines, start=1):
            expected_lines = expected_output.splitlines()
            actual_lines = actual_output.splitlines()
            for line_num, (expected, actual) in enumerate(zip(expected_lines, actual_lines), start=1):
                expected = expected.strip()
                actual = actual.strip()

                if expected != actual:
                    print(f"Test case {i}: Failed")
                    print(f"Mismatch at line {line_num}:")
                    print(f"Expected: {expected}")
                    print(f"Actual: {actual}")
                    print(f"Test Cases:")
                    print(test_cases)
                    exit(1)  
            print(f"Test case {i}: Passed")
            time.sleep(0.005)


if __name__ == "__main__":
    main()
