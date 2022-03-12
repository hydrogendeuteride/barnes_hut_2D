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
void treeTraversal(Node<TreeData> leafNode, Node<TreeData> rootNode, double timestep, 
                    std::function<std::tuple<vec2, vec2>(vec2 &p, vec2 &q, 
                    double leafMass, double rootMass, vec2 &dist_v, double timestep)> Integrator);

std::tuple<vec2, vec2> semi_implict_euler(vec2 &p, vec2 &q, double leafMass, double rootMass, 
                                            vec2 &dist, double timestep); 
//hamiltonian symplectic integrator 
//(p, q) -> (p, q) one time

inline vec2 acceleration(double leafMass, double rootMass, vec2 &dist);

 #endif