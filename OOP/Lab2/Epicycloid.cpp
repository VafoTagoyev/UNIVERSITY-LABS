//#include "stdafx.h"
#include <strstream>

#include <stdio.h>
#include <string.h>
#include <cmath>

#include "Epicycloid.h"

using namespace Prog2;

    Epicycloid::Epicycloid(double Rad, double rad, int sign) // инициализируюший конструктор
    {
        if (Rad < 0 || rad < 0)
            throw std::runtime_error("invalid parameters");
        R = Rad; r = rad; flag = sign;
    }

    // cеттеры
    Epicycloid& Epicycloid::setR(double R0)
    {
        if (R0 < 0)
            throw std::runtime_error("invalid radius");
        R = R0;
        return *this;
    }

    Epicycloid& Epicycloid::setr(double r0)
    {
        if (r0 < 0)
            throw std::runtime_error("invalid radius");
        r = r0;
        return *this;
    }

    Epicycloid& Epicycloid::setH(int h0)
    {
        if (h0 != 1 && h0 != -1)
            throw std::runtime_error("invalid value");
        flag = h0;
        return *this;
    }

    Point Epicycloid::Coordinates(double phi) const   // координаты точки на плоскости;
    {
        if(R < 0 || r < 0 || phi < 0)
            throw std::runtime_error("invalid radii or degree");
        double k = R / r;
        double corX = r * (k + 1) * (cos(phi) - cos((k+1)*phi) / (k+1));
        double corY = r * (k + 1) * (sin(phi) - sin((k+1)*phi) / (k+1));
        Point res;
        res.x = corX;
        res.y = corY;
        return res;
    }

    void Epicycloid::CheckType(double d) const   // тип эпициклоиды (обыкновенная, укороченная, удлиненная)
    {
        if(d < 0)
            throw std::runtime_error("illegal argument");

        if(d == r) std::cout << "Common Epicycloid" << std::endl;
        else if(d > r) std::cout << "Elongated Epicycloid" << std::endl;
        else std::cout << "Shortened Epicycloid" << std::endl;
    }

    double Epicycloid::area(double phi) const   // секториальную площадь эпициклоиды
    {
        if(R < 0 || r < 0 || phi < 0)
            throw std::runtime_error("invalid radii or degree");

        double k = R / r;
        double s;
        s = pow((r*(k+1)), 2) / 2 * (phi + phi/(pow(k+1, 2)) - 2*sin(k*phi)/(k*(k+1)));

        return s;
    }

    int Epicycloid::CheckForAstroid() const    // признак является ли данная эпициклоида астроидой
    {
        double k = R / r;

        if(flag == -1 && k == 4)
            return 1;

        return 0;
    }

