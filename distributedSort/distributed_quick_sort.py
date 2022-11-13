from multiprocessing import Pool
import itertools
import random
import timeit
import os



def quick_sort(A):
    n = len(A)
    with Pool(12) as p:
        quick_sort_split(A, 0, n, p, 0)

def quick_sort_split(A, l, r, p : Pool, depth : int):
    if l >= r - 1:
        return A

    j = l + 1
    for i in range(l + 1, r):
        if A[i] < A[l]:
            A[i], A[j] = A[j], A[i]
            j += 1
    A[l], A[j-1] = A[j-1], A[l]

    if depth == 3:
        args = [(A[l : j - 1], 0, j - l - 1, None, depth + 1), (A[j : r], 0, r - j, None, depth + 1)]
        res = p.starmap(quick_sort_split, args)
        A[l : j - 1] = res[0][:]
        A[j : r] = res[1][:]
        return A
    else:
        quick_sort_split(A, l, j - 1, p, depth + 1)
        quick_sort_split(A, j, r, p, depth + 1)
    return A
        

def is_sorted(arr):
    n = len(arr)
    for i in range(1, n):
        if arr[i-1] > arr[i]:
            return False
    return True


if __name__ == "__main__":
    random.seed(123)
    a = [random.randint(0, 1000000000) for _ in range(10000000)]
    print('multiple len', len(a), timeit.timeit(lambda : quick_sort(a), number=1))
    print(is_sorted(a))