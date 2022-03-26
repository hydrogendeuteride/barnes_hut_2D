#ifndef PHYSICS_H
#define PHYSICS_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include "qtree.hpp"
#include <functional>

constexpr double THETA = 0.5;
constexpr double G_CONST = 1.0;

typedef Eigen::Vector2d vec2;

template<typename TreeData>
std::tuple<vec2, vec2> treeTraversal(TreeData leaf, Node<TreeData> *rootNode, double timestep, 
                    std::function<std::tuple<vec2, vec2>(vec2 &p, vec2 &q, 
                    double leafMass, double rootMass, vec2 &dist_v, double timestep)> Integrator,
                    std::tuple<vec2, vec2> res = std::make_tuple(vec2(0.0, 0.0), vec2(0.0, 0.0)));

std::tuple<vec2, vec2> semi_implict_euler(const vec2 &v, const vec2 &x, 
                                            const double leafMass, const double rootMass,
                                            const vec2 &dist_v, const double timestep);


inline vec2 acceleration(const double leafMass, const double rootMass, const vec2 &dist);

 #endif