#include <iostream>
#include <cmath>

/*Класс Shape определяет интерфейс для всех геометрических объектов. 
В него входят чисто виртуальные методы draw(), erase(), move(), rotate()*/
//АБСТРАКТНЫЙ КЛАСС ДЛЯ ВСЕХ ГЕОМ.ФИГУР
class Shape {
public:
    virtual void draw() const = 0;      // изобразить
    virtual void erase() const = 0;     // убрать
    virtual void move(double dx, double dy) = 0; // передвинуть
    virtual void rotate(double angle) = 0;       // повернуть
    virtual ~Shape() = default;
};
/*Класс Point наследует от Shape и реализует все чисто виртуальные 
методы. Класс представляет собой точку в двумерном пространстве с 
координатами (x, y)*/


//ТОЧКА


class Point : public Shape {
protected:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    void draw() const override {
        std::cout << "Draw Point at (" << x << ", " << y << ")\n";
    }

    void erase() const override {
        std::cout << "Erase Point at (" << x << ", " << y << ")\n";
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override {
        // Поворот точки вокруг начала координат
        double rad = angle * 3.14159265358979323846 / 180.0;
        double newX = x * cos(rad) - y * sin(rad);
        double newY = x * sin(rad) + y * cos(rad);
        x = newX;
        y = newY;
    }

    virtual void info() const {
        std::cout << "Point at (" << x << ", " << y << ")\n";
    }
};
/*Класс Line наследует от Shape и содержит две точки (start и end). Он 
реализует методы для рисования, удаления, перемещения и поворота линии*/

//ЛИНИЯ


class Line : public Shape {
protected:
    Point start, end;
public:
    Line(Point start, Point end) : start(start), end(end) {}

    void draw() const override {
        std::cout << "Draw Line from ";
        start.info();
        std::cout << " to ";
        end.info();
    }

    void erase() const override {
        std::cout << "Erase Line from ";
        start.info();
        std::cout << " to ";
        end.info();
    }

    void move(double dx, double dy) override {
        start.move(dx, dy);
        end.move(dx, dy);
    }

    void rotate(double angle) override {
        start.rotate(angle);
        end.rotate(angle);
    }
};
/*Класс Rectangle наследует от Shape и представляет собой 
прямоугольник, определяемый нижней левой точкой, шириной и высотой*/


//ПРЯМОУГОЛЬНИК


class Rectangle : public Shape {
protected:
    Point bottomLeft;
    double width, height;
public:
    Rectangle(Point bottomLeft, double width, double height)
        : bottomLeft(bottomLeft), width(width), height(height) {}

    void draw() const override {
        std::cout << "Draw Rectangle with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " width: " << width << ", height: " << height << "\n";
    }

    void erase() const override {
        std::cout << "Erase Rectangle with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " width: " << width << ", height: " << height << "\n";
    }

    void move(double dx, double dy) override {
        bottomLeft.move(dx, dy);
    }

    void rotate(double angle) override {
        // Простая реализация: только поворот угла
        bottomLeft.rotate(angle);
    }
};
/*  Создание класса Square с использованием виртуального 
наследования:
    Класс Square наследует от Rectangle с использованием виртуального 
наследования и представляет собой квадрат.*/


//КВАДРАТ


class Square : public virtual Rectangle {
public:
    Square(Point bottomLeft, double sideLength)
        : Rectangle(bottomLeft, sideLength, sideLength) {}

    void draw() const override {
        std::cout << "Draw Square with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " side length: " << width << "\n";
    }

    void erase() const override {
        std::cout << "Erase Square with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " side length: " << width << "\n";
    }
};
/*  Создание класса Parallelogram с использованием виртуального 
наследования:
    Класс Parallelogram наследует от Rectangle с использованием 
виртуального наследования и добавляет дополнительный параметр — угол.*/


//ПАРАЛЛЕЛОГРАММ


class Parallelogram : public virtual Rectangle {
protected:
    double angle;
public:
    Parallelogram(Point bottomLeft, double width, double height, double angle)
        : Rectangle(bottomLeft, width, height), angle(angle) {}

    void draw() const override {
        std::cout << "Draw Parallelogram with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " width: " << width << ", height: " << height << ", angle: " << angle << "\n";
    }

    void erase() const override {
        std::cout << "Erase Parallelogram with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " width: " << width << ", height: " << height << ", angle: " << angle << "\n";
    }

    void rotate(double angle) override {
        // Здесь мы можем реализовать поворот параллелограмма
        this->angle += angle;
        bottomLeft.rotate(angle);
    }
};
/*Создание класса Rhombus:
Класс Rhombus наследует от Parallelogram и Rectangle, представляя 
собой ромб*/


//РОМБ


class Rhombus : public Parallelogram {
public:
    Rhombus(Point bottomLeft, double sideLength, double angle)
        : Rectangle(bottomLeft, sideLength, sideLength), Parallelogram(bottomLeft, sideLength, sideLength, angle) {}

    void draw() const override {
        std::cout << "Draw Rhombus with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " side length: " << width << ", angle: " << angle << "\n";
    }

    void erase() const override {
        std::cout << "Erase Rhombus with bottom-left corner at ";
        bottomLeft.info();
        std::cout << " side length: " << width << ", angle: " << angle << "\n";
    }
};
/*В функции main() создаются объекты различных классов, и 
вызываются их методы для демонстрации возможностей рисования, 
удаления, перемещения и поворота.*/
int main() {
    Point p1(0, 0);
    Point p2(1, 1);

    Line line(p1, p2);
    line.draw();
    line.move(1, 1);
    line.draw();
    line.rotate(45);
    line.draw();

    Rectangle rect(p1, 4, 2);
    rect.draw();
    rect.move(1, 1);
    rect.draw();

    Square square(p1, 2);
    square.draw();
    square.move(2, 2);
    square.draw();

    Parallelogram para(p1, 4, 2, 30);
    para.draw();
    para.move(1, 1);
    para.draw();

    Rhombus rhombus(p1, 2, 45);
    rhombus.draw();
    rhombus.move(1, 1);
    rhombus.draw();

    return 0;
}