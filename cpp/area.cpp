#include <iostream>
#include <list>

class Shape {
public:
    virtual ~Shape() {}
    virtual double area() = 0;
};

class Shapes {
public:
    Shapes(Shape* a, Shape* b, Shape* c) {
        _items.push_back(a);
        _items.push_back(b);
        _items.push_back(c);
    }
    double total() {
        double total = 0.0;
        for (auto shape : _items) {
            total += shape->area();
        }
        return total;
    }
private:
    std::list<Shape*> _items;
};

class Circle : public Shape {
public:
    Circle(double radius) : _radius(radius) {}
    double area() { return 3.14 * _radius * _radius; }
private:
    double _radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double base, double height) : _base(base), _height(height) {}
    double area() { return _base * _height; }
private:
    double _base, _height;
};

int main(void)
{
    Circle c1(1.5);
    Circle c2(2.0);
    Rectangle r1(2.0, 3.0);
    Shapes shapes(&c1, &c2, &r1);
    std::cout << "Area total: " << shapes.total() << std::endl;
    return 0;
}
