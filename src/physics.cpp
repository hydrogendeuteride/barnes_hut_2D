#include "physics.hpp"

template<typename TreeData>
void treeTraversal(Node<TreeData> *leafNode, Node<TreeData> *rootNode, double timestep, 
                    std::function<std::tuple<vec2, vec2>(vec2 &p, vec2 &q, double leafMass,
                     double rootMass, vec2 &dist_v, double timestep)> Integrator)
{
    if (rootNode->hasLeaf)
    {
        vec2 leafCOM  = CalcCOM(leafNode);
        vec2 rootCOM = CalcCOM(rootNode);

        vec2 dist_v = rootCOM - leafCOM;
        double dist = dist_v.norm();

        if ((rootNode->width / dist <= THETA) || rootNode->hasLeaf == false)
        {
            vec2 vel = leafNode->bodies.at(0).v;
            vec2 pos = leafNode->bodies.at(0).x;

            double leafmass = leafNode->bodies.at(0).mass;
            double rootmass = CalcTotalMass(rootNode);

            vec2 vel_1, pos_1;
            std::make_tuple(vel_1, pos_1) = Integrator(vel, pos, leafmass, rootmass, dist_v, timestep); 
            
            leafNode->bodies.at(0).x = pos_1(0);
            leafNode->bodies.at(0).v = vel_1(0);
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

std::tuple<vec2, vec2> semi_implict_euler(vec2 &v, vec2 &x, double leafMass, double rootMass,
                                            vec2 &dist_v, double timestep)
{
    vec2 v_1, x_1;
    v_1 = v + acceleration(leafMass, rootMass, dist_v) * timestep;
    x_1 = x + (v_1 / leafMass) * timestep;

    return std::make_tuple(v_1, x_1);
}

inline vec2 acceleration(double leafMass, double rootMass, vec2 &dist)
{
    return -((G_CONST * leafMass * rootMass) / (std::pow(dist.norm(), 3))) * dist;
}