from multiprocessing import Pool
import itertools
import random
import timeit
import os


def msort(A):
    merge_sort(A, 0, len(A), A[:])
    return A


def merge_sort(A, l, r, B):
    if l >= r -1:
        return
    
    m = l + (r - l) // 2

    merge_sort(A, l, m, B)
    merge_sort(A, m, r, B)

    merge_sort_partition(A, l, m, r, B)


def merge_sort_partition(A, begin, middle, end, B):
    i = begin
    j = middle
    for k in range(begin, end):
        if j >= end or (i < middle and A[i] < A[j]):
            B[k] = A[i]
            i += 1
        else:
            B[k] = A[j]
            j += 1

    for i in range(begin, end):
        A[i] = B[i]


def is_sorted(A):
    n = len(A)
    for i in range(n - 1):
        if A[i] > A[i + 1]:
            return False
    return True




def main(a):
    batch_count = os.cpu_count()
    batch_size = len(a) // (batch_count - 1)
    args = []
    for i in range(batch_count):
        args.append(a[i * batch_size : (i+1) * batch_size])

    with Pool(batch_count) as p:
        r = p.map(msort, args)

    # 多路归并
    idx = [0] * batch_count
    j = 0
    while j < len(a):
        minval = float('inf')
        minidx = 0
        for i in range(batch_count):
            if idx[i] < len(r[i]) and r[i][idx[i]] < minval:
                minval = r[i][idx[i]]
                minidx = i
        a[j] = minval
        idx[minidx] += 1
        j += 1




if __name__ == "__main__":
    random.seed(123)
    a = [random.randint(0, 1000000000) for _ in range(5000000)]
    print('multiple len', len(a), timeit.timeit(lambda : main(a), number=1))
    print(is_sorted(a))