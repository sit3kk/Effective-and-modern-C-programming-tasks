#pragma include once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix
{
private:
	T data[N * M];

public:
public:
	constexpr size_t numberOfRows() const { return N; }
	constexpr size_t numberOfColumns() const { return M; }

	Matrix(int nrows = N, int ncols = M)
	{
		std::fill_n(data, N * M, T{});
	}
	Matrix(const std::initializer_list<std::initializer_list<T>> &list)
	{
		T *p = data;
		for (const auto &row : list)
		{
			T *p2 = std::copy(row.begin(), row.end(), p);
			std::fill(p2, p += M, T{});
		}
	}

	Matrix(const Matrix &m)
	{
		std::copy_n(m.data, N * M, data);
	}

	Matrix &operator=(const Matrix &m)
	{
		if (&m != this)
		{
			std::copy_n(m.data, N * M, data);
		}
		return *this;
	}

	T &operator()(int i, int j)
	{
		return data[(i - 1) * M + j - 1];
	}

	const T &operator()(int i, int j) const
	{
		return data[(i - 1) * M + j - 1];
	}

	friend Matrix operator+(const Matrix &a, const Matrix &b)
	{
		Matrix r;
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= M; ++j)
			{
				r(i, j) = a(i, j) + b(i, j);
			}
		}
		return r;
	}

	class iterator
	{
	private:
		T *ptr;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T *;
		using reference = T &;

		explicit iterator(pointer p) : ptr(p) {}

		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }

		iterator &operator++()
		{
			ptr++;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const iterator &other) const { return ptr == other.ptr; }
		bool operator!=(const iterator &other) const { return ptr != other.ptr; }
	};

	// Const iterator for read-only access
	class const_iterator
	{
	private:
		const T *ptr;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = const T;
		using difference_type = ptrdiff_t;
		using pointer = const T *;
		using reference = const T &;

		explicit const_iterator(pointer p) : ptr(p) {}

		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }

		const_iterator &operator++()
		{
			ptr++;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const const_iterator &other) const { return ptr == other.ptr; }
		bool operator!=(const const_iterator &other) const { return ptr != other.ptr; }
	};

	// Functions to obtain iterators
	iterator begin() { return iterator(data); }
	iterator end() { return iterator(data + N * M); }
	const_iterator begin() const { return const_iterator(data); }
	const_iterator end() const { return const_iterator(data + N * M); }

	// Row iterator to iterate through a specific row
	class row_iterator
	{
	private:
		T *ptr;

	public:
		row_iterator(T *start) : ptr(start) {}

		T &operator*() const { return *ptr; }
		row_iterator &operator++()
		{
			ptr++;
			return *this;
		}
		row_iterator operator++(int)
		{
			row_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		bool operator==(const row_iterator &other) const { return ptr == other.ptr; }
		bool operator!=(const row_iterator &other) const { return ptr != other.ptr; }
	};

	row_iterator row_begin(size_t row) { return row_iterator(data + row * M); }
	row_iterator row_end(size_t row) { return row_iterator(data + (row + 1) * M); }

	// Column iterator to iterate through a specific column
	class col_iterator
	{
	private:
		T *ptr;

	public:
		col_iterator(T *start) : ptr(start) {}

		T &operator*() const { return *ptr; }
		col_iterator &operator++()
		{
			ptr += M;
			return *this;
		}
		col_iterator operator++(int)
		{
			col_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		bool operator==(const col_iterator &other) const { return ptr == other.ptr; }
		bool operator!=(const col_iterator &other) const { return ptr != other.ptr; }
	};

	col_iterator col_begin(size_t col) { return col_iterator(data + col); }
	col_iterator col_end(size_t col) { return col_iterator(data + col + M * N); }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M> &m, int width = 10)
{
	for (size_t i = 1; i <= m.numberOfRows(); ++i)
	{
		for (size_t j = 1; j <= m.numberOfColumns(); ++j)
		{
			if (j != 1)
				cout << " ";
			cout << setw(width) << m(i, j);
		}
		cout << endl;
	}
}
