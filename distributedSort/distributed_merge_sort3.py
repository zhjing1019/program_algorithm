from multiprocessing import Pool
import itertools
import random
import timeit




def merge_sort(A):
    n = len(A)

    with Pool(12) as p:
        width = 1
        while width < n:
            args = []
            for i in range(0, n, 2 * width):
                begin = i
                middle = min(n, i + width)
                end = min(n, i + 2 * width)
                args.append((A[begin:end], 0, middle - i, end - i))
            r = p.starmap_async(merge_sort_partition, args)
            A[:] = itertools.chain.from_iterable(r.get())
            width *= 2
            


def merge_sort_partition(A, begin, middle, end):
    B = A[:]
    i = begin
    j = middle
    for k in range(begin, end):
        if j >= end or (i < middle and A[i] < A[j]):
            B[k] = A[i]
            i += 1
        else:
            B[k] = A[j]
            j += 1
    return B


def is_sorted(A):
    n = len(A)
    for i in range(n - 1):
        if A[i] > A[i + 1]:
            return False
    return True

random.seed(123)

a = [random.randint(0, 1000000000) for _ in range(5000000)]
# a = [random.randint(0, 10) for _ in range(5)]



if __name__ == "__main__":
    print('multiple len', len(a), timeit.timeit(lambda : merge_sort(a), number=1))
    # print(a)
    # merge_sort(a)
    # print(a)
    print(is_sorted(a))



