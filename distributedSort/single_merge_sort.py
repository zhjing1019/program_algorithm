import random
import timeit



def msort(A):
    merge_sort(A, 0, len(A), A[:])

def merge_sort(A, l, r, B):
    if l >= r - 1:
        return A
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



def is_sorted(arr):
    n = len(arr)
    for i in range(1, n):
        if arr[i-1] > arr[i]:
            return False
    return True



if __name__ == "__main__":
    random.seed(123)
    a = [random.randint(0, 1000000000) for _ in range(100000)]
    b = a[:]
    print('multiple len', len(a), timeit.timeit(lambda : msort(a), number=1))
    print(is_sorted(a))