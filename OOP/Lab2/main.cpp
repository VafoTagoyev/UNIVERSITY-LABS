//#include "stdafx.h"
#include <iostream>

#include "Epicycloid.h"
#include "Epicycloid.cpp"

int main()
{
    Prog2::Epicycloid e(3, 1, 1);
    int fl1 = 1, flag;
    double R, r, d;
    double area;
    while(fl1){
        std::cout << "The inner radius of the bounding epicycloid : " << e.Radii1() << std::endl;
        std::cout << "The external radius of the bounding epicycloid : " << e.Radii2() << std::endl;
        std::cout << "The curvature radius of epicycloid : " << e.CurvatureRad() << std::endl;
        std::cout << "Enter the distance from the center of the generative circle to the border of guide circle : " << std::endl;
        std::cin >> d;
        std::cout << "The type of epicycloid : ";
        e.CheckType(d);
        if(e.CheckForAstroid())
            std::cout << "The epicycloid is an astroid" << std::endl;
        else
            std::cout << "The epicycloid is not an astroid" << std::endl;
        int fl2 = 1;
        while(fl2){
            std::cout << "Enter angle for calculate coordinates and area or precc ctrl+Z to quit :" << std::endl;
            double phi;
            Prog2::Point Cor;
            std::cin >> phi;
            fl2 = std::cin.good();
            if(!fl2)
                continue;
            try{
                Cor = e.Coordinates(phi);
                area = e.area(phi);
                std::cout << "Coordinates : ";
                std::cout << "CorX = " << Cor.x << " ; " << "CorY = " << Cor.y << std::endl;
                std::cout << "Area : " << area << std::endl;
            }
            catch(std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        //std::cin.clear();
        std::cout << "Enter new R, r and sign to continue or press ctrl+Z to quit :" << std::endl;
        std::cin >> R >> r >> flag;
        if(std::cin.good()){
            try{
                e.setR(R);
            }
            catch (std::exception &ex){
                std::cout << ex.what() << std::endl;
            }
            try{
                e.setr(r);
            }
            catch (std::exception &ex){
                std::cout << ex.what() << std::endl;
            }
            try{
                e.setH(flag);
            }
            catch (std::exception &ex){
                std::cout << ex.what() << std::endl;
            }
        }
        else
            fl1 = 0;
    }
    return 0;
}

