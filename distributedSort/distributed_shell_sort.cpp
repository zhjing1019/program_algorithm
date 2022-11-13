#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>

#define N 10000000

using namespace std;


int swap(int arr[], int x, int y)
{
    int t = arr[x];
    arr[x] = arr[y];
    arr[y] = t;
}

void insertSortK(int arr[], int n, int gap, int k)
{
    for (size_t i = gap + k; i < n; i += gap)
    {
        for (size_t j = i; j >= gap; j -= gap)
        {
            if (arr[j] < arr[j - gap])
            {
                swap(arr, j, j - gap);
            }
            else
            {
                break;
            }
        }
    }
}

void shell_sort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /=2)
    {
        vector<thread> ts;
        for (int k = 0; k < gap; k++)
        {
            if (gap < 600)
            {
                ts.push_back(thread(insertSortK, arr, n, gap, k));
            }
            else
            {
                insertSortK(arr, n, gap, k);
            }
            
        }

        for (auto &t : ts) {
            t.join();
        }
    }
}

bool is_sorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}


int main()
{
    srand(123);
    // int arr[] = {1, 5, 2, 3,4 };
    int* arr = new int[N];
    for (size_t i = 0; i < N; i++)
    {
        arr[i] = rand() % 10;
        // cout << arr[i] << ", ";
    }
    
    cout << endl;
    

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    shell_sort(arr, N);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    
    // for (size_t i = 0; i < N; i++)
    // {
    //     cout << arr[i] << ", ";
    // }

    cout << endl <<"is sorted " << is_sorted(arr, N) <<endl;
    return 0;
}