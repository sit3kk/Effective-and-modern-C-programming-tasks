#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtx; // Mutex to avoid data races in the array

template <int N>
struct Array
{
	int a[N];
	int i = 0;
	long long sum = 0;

	int f(int x)
	{
		int y = x % 11;
		return (y * y + 1);
	}

	void generateArray()
	{
		while (i < N)
		{
			lock_guard<mutex> lock(mtx);
			if (i < N)
			{
				a[i++] = rand();
			}
		}
		i = 0;
		while (i < N)
		{
			lock_guard<mutex> lock(mtx);
			if (i < N)
			{
				a[i] = f(a[i]);
				i++;
			}
		}
	}

	long long computeSum()
	{
		long long local_sum = 0;
		for (int x : a)
		{
			local_sum += x;
		}
		return local_sum;
	}

	void parallelComputeSum(int num_threads)
	{
		vector<thread> threads;
		vector<long long> partial_sums(num_threads, 0);
		int chunk_size = N / num_threads;

		for (int t = 0; t < num_threads; ++t)
		{
			threads.emplace_back([&, t]()
								 {
                int start = t * chunk_size;
                int end = (t == num_threads - 1) ? N : start + chunk_size;
                for (int i = start; i < end; ++i) {
                    partial_sums[t] += a[i];
                } });
		}

		for (auto &th : threads)
		{
			th.join();
		}

		sum = accumulate(partial_sums.begin(), partial_sums.end(), 0LL);
	}
};
int main()
{
	srand(2019);
	using A = Array<1000>;
	A array;
	std::thread t1(&A::generateArray, &array);
	//  What happens if you uncomment this line?
	std::thread t2(&A::generateArray, &array);
	t2.join();
	t1.join();
	for (int i = 0; i < 40; i++)
	{
		cout << array.a[0 + i] << "  ";
	}
	long long sum = array.computeSum();
	cout << "\n sum = " << sum << endl;
}
