#ifndef EPICYCLOID_H_INCLUDED
#define EPICYCLOID_H_INCLUDED
//#include "gtest\gtest_prod.h"
//#include "gtest\gtest_prod.h"
#include <cmath>

namespace Prog2{
    struct Point{
        double x, y; // координаты точки на плоскости
        //Point(double x0 = 1, double y0 = 0) :x(x0), y(y0){}
    };

    class Epicycloid{
    private:
        //Point P0, P1;        // координаты центр окружности
        double R, r; // R -> радиус направляющей окружности; r -> радиус порождающего круга
        int flag;        // flag -> задание -1 если внутри +1 усли снаружее

    public:
        Epicycloid(double Rad = 1, double rad = 1, int sign = 1);  // инициализируюший конструктор

        // cеттеры
        Epicycloid& setR(double R0);
        Epicycloid& setr(double r0);
        Epicycloid& setH(int h0);
        // геттеры
        //Point getP0() const{ return P0; }
        //Point getP1() const{ return P1; }
        double getR() const{ return R; }
        double getr() const{ return r; }
        int getH() const{ return flag; }
        // другие методы
        Point Coordinates(double phi) const; // координаты точки на плоскости
        double area(double phi) const; // секториальную площадь эпициклоиды
        double Radii1() const{ return R; } // радиус ограничивающих эпициклоиду внутренный
        double Radii2() const{ return R + 2 * r; } // радиусы ограничивающих эпициклоиду внешный
        double CurvatureRad() const{ return 1; } // радиус кривизны
        void CheckType(double d) const; // тип эпициклоиды (обыкновенная, укороченная, удлиненная)
        int CheckForAstroid() const;  // признак является ли данная эпициклоида астроидой
    };
}
#endif // EPICYCLOID_H_INCLUDED
