#include "lib.hpp"
#include <cmath>
#include <fmt/core.h>
#include <memory>
#include <set>

struct Shape {
  public: // есть неявно
    int x, y;
    Shape(int x, int y) : x(x), y(y) {}
    virtual ~Shape() noexcept = default;
    virtual void draw() const = 0;
    virtual auto circumference() const -> float = 0;
};

auto area(Shape const &shape) -> float;

class Rectangle : virtual public Shape {
  public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : Shape{x, y}, width(width), height(height) {}
    // Shape::draw = Rectangle::draw
    void draw() const override {
        fmt::print("Rectangle({}, {})", width, height);
    }

    auto circumference() const -> float override {
        return float(2 * width + 2 * height);
    }

  private:
    int width, height;
    friend auto area(Shape const &shape) -> float;
    friend auto area(Rectangle const &shape) -> float;
};

struct Diamond : virtual Shape {
    Diamond(int x, int y, int side, float angle)
        : Shape{x, y}, side{side}, angle{angle} {}
    void draw() const override {
        fmt::print("Diamond({}, {} rad)", side, angle);
    }
    auto circumference() const -> float override { return float(4 * side); }

  protected:
    int side;
    float angle;
    friend auto area(Shape const &shape) -> float;
};

constexpr double pi = 3.1415926;
struct Square : Rectangle, Diamond {
    Square(int x, int y, int side)
        : Shape{x, y}, Rectangle(x, y, side, side),
          Diamond(x, y, side, pi / 2) {}
    void draw() const override { Rectangle::draw(); }
    auto circumference() const -> float override { return float(4 * side); }
};

void call_draw(Shape const &shape) { shape.draw(); }

void call_draw_and_delete(std::unique_ptr<Shape> shape) { shape->draw(); }

// СЛОЖНО!
auto down_cast(std::unique_ptr<Shape> &&shape) -> std::unique_ptr<Rectangle> {
    auto ptr = dynamic_cast<Rectangle *>(shape.get());
    if (ptr != nullptr)
        return std::unique_ptr<Rectangle>(
            dynamic_cast<Rectangle *>(shape.release()));
    return nullptr;
}

auto area(Shape const &shape) -> float {
    // Code smell
    if (auto rect = dynamic_cast<Rectangle const *>(&shape))
        return rect->width * rect->height;
    if (auto diamond = dynamic_cast<Diamond const *>(&shape))
        return diamond->side * diamond->side * std::sin(diamond->angle);
    return 0;
}

auto area(Rectangle const &rect) { return rect.width * rect.height; }

int main() {
    Rectangle rect;
    rect.draw();
    fmt::print("Rectangle area: {}\n", area(rect));
    Shape &my_shape = rect;
    my_shape.draw();
    call_draw(rect);
    fmt::print("Rectangle area: {}\n", area(my_shape));
    auto new_rect = std::make_unique<Rectangle>(3, 2, 4, 5);
    auto new_shape = std::unique_ptr<Shape>{std::move(new_rect)};
    new_shape->draw();
    new_rect = down_cast(std::move(new_shape));
    call_draw_and_delete(std::move(new_rect));
    Square sq(0, 0, 1);
    call_draw(sq);
    auto shapes = std::vector<std::unique_ptr<Shape>>{};
    shapes.emplace_back(std::move(new_rect));
    shapes.emplace_back(std::make_unique<Square>(0, 0, 1));
    float sum_of_circumferences = 0.;
    for (auto const &shape : shapes)
        sum_of_circumferences += shape->circumference();

    return 0;
}