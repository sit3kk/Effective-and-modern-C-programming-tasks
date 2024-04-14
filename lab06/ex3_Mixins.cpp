#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Red
{
public:
    static constexpr char color[] = "red";
};

class Yellow
{
public:
    static constexpr char color[] = "yellow";
};

class Blue
{
public:
    static constexpr char color[] = "blue";
};

class Circle
{
    double r = 0;

public:
    Circle() = default;
    Circle(double r) : r(r) {}
    double area() const { return 3.14 * r * r; }
};

class Rectangle
{
    double a = 0, b = 0;

public:
    Rectangle() = default;
    Rectangle(double a, double b) : a(a), b(b) {}
    double area() const { return a * b; }
};

class Note
{
    vector<string> notes;

public:
    Note(const string &note)
    {
        add(note);
    }
    void add(const string &note)
    {
        notes.push_back(note);
    }
};

template <typename... Bases>
class Mixins : public Bases...
{
public:
    template <typename... Args>
    Mixins(Args &&...args) : Bases(std::forward<Args>(args))... {}
};

int main()
{
    using RedCircle = Mixins<Red, Circle>;
    RedCircle x(Red{}, Circle{3});
    cout << x.color << " area = " << x.area() << endl;

    using BlueRectangleWithNotes = Mixins<Blue, Rectangle, Note>;
    BlueRectangleWithNotes y(Blue{}, Rectangle{3, 4}, Note{"Hey"});
    y.add("Ho");
    cout << y.color << " area = " << y.area() << endl;

    return 0;
}
