#pragma once
#include <iostream>
#include <string>

int id_graphic = 1;

/// @brief класс, представляющий графический примитив
class GraphicPrimitive
{
private:
    const int id;           // id графического примитива
    std::string figureName; // название примитива

public:
    /// @brief конструктор с параметрами
    /// @param name название примитива
    GraphicPrimitive(const std::string name) : figureName(name), id(id_graphic++) {}


    /// @brief конструктор с ID (для избежания ошибок при использовании make_shared)
    /// @param id ID графического примитива
    GraphicPrimitive(int id, const std::string name) : id(id), figureName(name) {}

    /// @brief гетер id
    /// @return id
    const int getId() const
    {
        return id;
    }

    /// @brief гетер названия примитива
    /// @return название примитива
    const std::string getFigureName() const
    {
        return figureName;
    }

    /// @brief деструктор
    ~GraphicPrimitive()
    {
        std::cout << "Удален графический примитив \"" << figureName << "\" (ID: " << id << ")" << std ::endl;
    }
};

/// @brief класс графического примитива "круг"
class Circle : public GraphicPrimitive
{
private:
    double radius; // радиус круга
public:
    /// @brief конструктор с параметрами
    /// @param radius радиус
    Circle(const double &radius) : GraphicPrimitive("Circle"), radius(radius)
    {
        std::cout << "Создан графический примитив \"Circle\" с радиусом " << radius << "; ID: " << getId() << std ::endl;
    }

};

/// @brief класс графического примитива "прямоугольник"
class Rectangle : public GraphicPrimitive
{
private:
    double length; // длина прямоугольника
    double width;  // ширина прямоугольника
public:
    /// @brief конструктор с параметрами
    /// @param length длина
    /// @param width ширина
    Rectangle(const double &length, const double &width) : GraphicPrimitive("Rectangle"), length(length), width(width)
    {
        std::cout << "Создан графический примитив \"Rectangle\" с длиной " << length << " и шириной " << width << "; ID: " << getId() << std ::endl;
    }

};

/// @brief класс прямоугольника с равными сторонами (квадрат)
class Square : public Rectangle
{
private:
    double length; // сторона квадрата
public:
    /// @brief конструктор с параметрами
    /// @param length сторона квадрата
    Square(const double &length) : Rectangle(length, length) {}
};