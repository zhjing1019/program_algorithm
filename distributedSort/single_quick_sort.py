import random
import timeit



def quick_sort(A):
    n = len(A)
    quick_sort_split(A, 0, n)

        
        
def quick_sort_split(A, l, r):
    if l >= r - 1:
        return

    j = l + 1
    for i in range(l + 1, r):
        if A[i] < A[l]:
            A[i], A[j] = A[j], A[i]
            j += 1
    A[l], A[j-1] = A[j-1], A[l]

    quick_sort_split(A, l, j - 1)
    quick_sort_split(A, j, r)


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