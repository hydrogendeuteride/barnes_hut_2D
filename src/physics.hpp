#ifndef PHYSICS_H
#define PHYSICS_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include "qtree.hpp"
#include <functional>
#include <tuple>

constexpr double THETA = 0.5;
constexpr double G_CONST = 1.0;

typedef Eigen::Vector2d vec2;

template<typename TreeData>
class BHtree
{
    inline vec2 Acceleration(const double leafMass, const double rootMass, const vec2 &dist); //calculate 1:! acceleration

    vec2 Net_Acceleration(TreeData& leaf, Node<TreeData> *rootNode); //calculate 1:n acceleration

    std::tuple<vec2, vec2> Semi_Implict_Euler(const std::tuple<vec2, vec2>& Phase_Space, 
                                           const vec2 &accel, const double timestep);

    void Calc_Next_Phase_Space(TreeData& leaf, Node<TreeData> *rootNode, double timestep);
};

 #endif