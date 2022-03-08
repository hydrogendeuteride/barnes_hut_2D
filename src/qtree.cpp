#include "qtree.hpp"
#include <tuple>
#include <algorithm>
#include <optional>

template <typename TreeData>
void Node<TreeData>::generateLeaf(int depth, std::vector<TreeData> &bodies)
{
    std::vector<TreeData> q1, q2, q3, q4;

    for (auto body : bodies)
    {
        if (body.x < (this->posX + (this->width / 2.0)))
        {
            if (body.y < (this->posY + (this->height / 2.0)))
                q1.push_back(body);
            else
                q3.push_back(body);
        }
        else 
        {
            if (body.y < (this->posY + (this->height / 2.0)))
                q2.push_back(body);
            else
                q4.push_back(body);
        }
    }

    if (!q1.empty() && depth >= 1)
    {
        this->hasLeaf = true;
        leaves.emplace_back(Node<TreeData>(q1, this->width / 2.0, this->height / 2.0,
                                this->posX, this->posY));
        
        generateLeaf(depth - 1, q1);
    }

    if (!q2.empty() && depth >= 1)
    {
        this->hasLeaf = true;
        leaves.emplace_back(Node<TreeData>(q2, this->width / 2.0, this->height / 2.0, 
                                this->posX + (this->width / 2.0), this->posY));
        
        generateLeaf(depth - 1, q2);
    }

    if (!q3.empty() && depth >= 1)
    {
        this->hasLeaf = true;
        leaves.emplace_back(Node<TreeData>(q3, this->width / 2.0, this->height / 2.0, 
                                this->posX, this->posY + (this->height / 2.0)));
        
        generateLeaf(depth - 1, q3);
    }

    if (!q4.empty() && depth >= 1)
    {
        this->hasLeaf = true;
        leaves.emplace_back(Node<TreeData>(q4, this->width / 2.0, this->height / 2.0, 
                                this->posX + (this->width / 2.0), this->posY + this->height / 2.0));
        
        generateLeaf(depth - 1, q4);
    }
}//Maybe recursion optimization on g++ -O2??
// O(nlog(n)) time complexity

template <typename TreeData>
double CalcTotalMass(Node<TreeData> &node)
{
    double mass = 0;
    std::for_each(node.bodies.begin(), node.bodies.end(),
                     [mass](const auto &x) {mass += x.mass;});

    return mass;
}

template <typename TreeData>
std::tuple<double, double> CalcCOM(Node<TreeData> &node)
{
    double mass = 0;
    std::for_each(node.bodies.begin(), node.bodies.end(), 
                    [mass](const auto &x) {mass += x.mass;});

    double massDistX = 0;
     std::for_each(node.bodies.begin(), node.bodies.end(), 
                    [mass](const auto &x) {mass += (x.mass * x.x);});

    double massDistY = 0;
    std::for_each(node.bodies.begin(), node.bodies.end(), 
                    [mass](const auto &x) {mass += (x.mass * x.y);});

    return std::make_tuple(massDistX / mass, massDistY / mass);
}

template <typename TreeData>
std::vector<Node<TreeData>> leaves;

template <typename TreeData>
void leafNodes(Node<TreeData> &root)
{
    if (!root)
        return;
    
    if (!root.hasLeaf)
    {
        leaves<TreeData>.push_back(root);
        return;
    }

    if (root.leaves.at(0)) 
        leafNodes(root.leaves.at(0));

    if (root.leaves.at(1)) 
        leafNodes(root.leaves.at(1));

    if (root.leaves.at(2)) 
        leafNodes(root.leaves.at(2));

    if (root.leaves.at(3)) 
        leafNodes(root.leaves.at(3));
}//O(n) time complexity