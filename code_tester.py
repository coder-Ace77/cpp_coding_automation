import random

def generate_test_cases(num_cases, max_k, max_n):
    test_cases = []
    for _ in range(num_cases):
        k = random.randint(0, max_k)
        test_cases.append(k)
    return test_cases

def main():
    num_cases = 1000  # Number of test cases
    max_k = 105  # Maximum value for k
    max_n = 500  # Maximum value for n

    test_cases = generate_test_cases(num_cases, max_k, max_n)

    # Print the number of test cases
    print(num_cases)
    
    for k in test_cases:
        print(k)

if __name__ == "__main__":
    main()