#ifndef PHYSICS_H
#define PHYSICS_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include "qtree.hpp"
#include <functional>
#include <tuple>

constexpr double THETA = 0.5;
constexpr double G_CONST = 0.1;

typedef Eigen::Vector2d vec2;

template<typename TreeData>
class BHtree
{
    inline vec2 Acceleration(const double leafMass, const double rootMass, const vec2 &dist); //calculate 1:! acceleration

    vec2 Net_Acceleration(TreeData& leaf, Node<TreeData> *rootNode); //calculate 1:n acceleration

    public:
    void Calc_Next_Phase_Space(TreeData& leaf, Node<TreeData> *rootNode, double timestep);  //calculate next step
};

namespace Integrator 
{
    class Semi_Implicit_Euler  //one step calculation, semi implicit euler
    {
        std::tuple<vec2, vec2> operator()(const std::tuple<vec2, vec2>& Phase_Space, 
                                            const vec2 &accel, const double timestep)
        {
            auto [v_1, x_1] = Phase_Space;
            vec2 x, v;
            x << 0.0, 0.0;
            v << 0.0, 0.0;

            v_1 = v + accel * timestep;
            x_1 = x + v_1 * timestep;

            return std::make_tuple(x_1, v_1);
        }
    };
}

 #endif