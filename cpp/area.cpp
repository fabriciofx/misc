#include <iostream>
#include <list>
#include <memory>

class Shape {
public:
    virtual ~Shape() noexcept {}
    virtual double area() const noexcept = 0;
};

class Shapes {
public:
    Shapes() = delete;
    Shapes(Shapes const&) = delete;
    Shapes& operator =(Shapes const&) = delete;
    template <typename... Args>
    Shapes(Args&& ... args) {
        construct(std::forward<Args>(args) ...);
    }
    double total() const noexcept {
        double total = 0.0;
        for (auto const& shape : _items) {
            total += shape->area();
        }
        return total;
    }
private:
    template <typename Arg>
    void construct(Arg&& arg) {
        _items.push_back(std::forward<Arg>(arg));
    }
    template <typename Arg, typename... Args>
    void construct(Arg&& arg, Args&&... args) {
        _items.push_back(std::forward<Arg>(arg));
        construct(std::forward<Args>(args) ...);
    }
    std::list<std::shared_ptr<Shape>> _items;
};

class Circle : public Shape {
public:
    Circle(double radius) : _radius(radius) {}
    double area() const noexcept {
        return 3.14 * _radius * _radius;
    }
private:
    double _radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double base, double height) : _base(base), _height(height) {}
    double area() const noexcept {
        return _base * _height;
    }
private:
    double _base, _height;
};

class Square : public Shape {
public:
    Square(double face) : _face(face) {}
    double area() const noexcept {
        return _face * _face;
    }
private:
    double _face;
};

int main(void)
{
    Shapes shapes(std::make_shared<Circle>(1.5), std::make_shared<Circle>(2.0),
        std::make_shared<Rectangle>(2.0, 3.0), std::make_shared<Square>(2));
    std::cout << "Area total: " << shapes.total() << std::endl;
    return 0;
}
