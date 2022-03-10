#include "physics.hpp"
#include <cmath>
#include <tuple>
#include <eigen3/Eigen/Dense>

template<typename TreeData>
void treeTraversal(Node<TreeData> *leafNode, Node<TreeData> *rootNode, double timestep)
{
    if (rootNode->hasLeaf)
    {
        Eigen::Vector2d leafCOM, rootCOM;
        leafCOM << std::get<0>(CalcCOM(leafNode)), std::get<1>(CalcCOM(leafNode));
        rootCOM << std::get<0>(CalcCOM(rootNode)), std::get<1>(CalcCOM(rootNode));

        vec2 dist_v = rootCOM - leafCOM;
        double dist = dist_v.norm();

        if ((rootNode->width / dist <= THETA) || rootNode->hasLeaf == false)
        {
            //doSometing
        }
        else 
        {
            treeTraversal(leafNode, rootNode -> leaf0);
            treeTraversal(leafNode, rootNode -> leaf1);
            treeTraversal(leafNode, rootNode -> leaf2);
            treeTraversal(leafNode, rootNode -> leaf3);
        }
    }
}

std::tuple<vec2, vec2> semi_implict_euler(vec2 &p, vec2 &q, double leafMass, double rootMass,
                                            vec2 &dist_v, double timestep)
{
    vec2 p_1, q_1;
    p_1 = p + Force(leafMass, rootMass, dist_v) * timestep;
    q_1 = q + (p_1 / leafMass) * timestep;

    return std::make_tuple(p_1, q_1);
}

inline vec2 Force(double leafMass, double rootMass, vec2 &dist)
{
    return ((G_CONST * leafMass * rootMass) / (std::pow(dist.norm(), 3))) * dist;
}