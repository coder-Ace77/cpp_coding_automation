def mul(a, b, mod):
    return [
        [
            (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % mod,
            (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % mod
        ],
        [
            (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % mod,
            (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % mod
        ]
    ]

def matrix_pow(a, k, mod):
    res = [[1, 0], [0, 1]]  # Identity matrix
    while k > 0:
        if k % 2 == 1:
            res = mul(res, a, mod)
        a = mul(a, a, mod)
        k //= 2
    return res

def solve():
    a, b, m = map(int, input().split())
    
    if b == 0:
        print(2)
        return
    if b == 1:
        print(a % m)
        return
    
    x = [[a, -1], [1, 0]]
    
    # Matrix exponentiation
    result_matrix = matrix_pow(x, b - 1, m)
    
    # Final result: (result_matrix[0][0] * a + result_matrix[0][1] * 2) % m
    result = (result_matrix[0][0] * a + result_matrix[0][1] * 2) % m
    print(result)

# Main
solve()
