from itertools import combinations
import string
import time
def square_sum(n):
    res = 0
    for i in range(n):
        res += n*n
    return res
def save_combinations(n, output_file):
    whole = []
    for l in combinations(string.ascii_lowercase[:n], 5):
        whole.append(','.join(l))
    with open(output_file, 'w') as f:
        f.write('\n'.join(whole))
def main():
    print(square_sum(10000))
    save_combinations(10, './combinations.txt')
    time.sleep(0.01)

if __name__ == '__main__':
    main()
