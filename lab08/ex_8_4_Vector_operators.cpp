#include <iostream>
using namespace std;

template <typename L, typename R>
class Vector_lazy;

template <int N>
class Vector
{
  int data[N];

public:
  Vector()
  {
    cout << "Default constructor" << endl;
  }

  Vector(initializer_list<int> list)
  {
    cout << "Initializer list constructor" << endl;
    auto it = list.begin();
    for (int i = 0; i < N; ++i)
    {
      data[i] = (it != list.end() ? *it++ : 0);
    }
  }

  Vector(const Vector &m)
  {
    std::copy(m.data, m.data + N, data);
    cout << "Copy constructor" << endl;
  }

  int operator[](int index) const
  {
    return data[index];
  }

  int &operator[](int index)
  {
    return data[index];
  }

  template <typename L, typename R>
  Vector(const Vector_lazy<L, R> &lazy)
  {
    for (int i = 0; i < N; ++i)
    {
      data[i] = lazy[i];
    }
  }

  friend ostream &operator<<(ostream &out, const Vector &m)
  {
    for (int i = 0; i < N; ++i)
    {
      out << m.data[i] << (i < N - 1 ? ", " : "");
    }
    return out;
  }
};

template <typename L, typename R>
class Vector_lazy
{
public:
  using Func = int (*)(const L &, const R &, int);

  Vector_lazy(const L &left_, const R &right_, Func op_)
      : left(left_), right(right_), op(op_) {}

  int operator[](int n) const
  {
    return op(left, right, n);
  }

private:
  L left;
  R right;
  Func op;
};

template <int N, typename L, typename R>
Vector_lazy<L, R> operator+(const L &l, const R &r)
{
  return Vector_lazy<L, R>(l, r, [](const L &l, const R &r, int n)
                           { return l[n] + r[n]; });
}

template <int N, typename L, typename R>
Vector_lazy<L, R> operator-(const L &l, const R &r)
{
  return Vector_lazy<L, R>(l, r, [](const L &l, const R &r, int n)
                           { return l[n] - r[n]; });
}

template <int N, typename L>
Vector_lazy<L, int> operator*(const L &l, int scalar)
{
  return Vector_lazy<L, int>(l, scalar, [](const L &l, int scalar, int n)
                             { return l[n] * scalar; });
}
int main()
{
  using V = Vector<10>;
  V v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  V x(v);
  V y{4, 4, 2, 5, 3, 2, 3, 4, 2, 1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;

  // Computes only one coordinate of Vector
  int e = (z + x + y)[2];
  cout << " e = " << e << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */