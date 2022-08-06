#ifndef _QTREE_H_
#define _QTREE_H_

#include <vector>
#include <memory>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <tuple>
#include <algorithm>
#include <numeric>

typedef Eigen::Vector2d vec2;

constexpr int MAX_DEPTH = 100;

struct body
{
    vec2 x;
    vec2 v;
    double mass;

    body(vec2 x, vec2 v, double mass) : x(x), v(v), mass(mass){};
};

template <typename TreeData>
class Node
{
public:
    std::unique_ptr<Node> leaf0;
    std::unique_ptr<Node> leaf1;
    std::unique_ptr<Node> leaf2;
    std::unique_ptr<Node> leaf3;
    
    bool hasLeaf = false;
    
    double width;
    double height;
    double posX;
    double posY;

    std::vector<TreeData> bodies;

    Node(double w, double h, double x, double y) //get rvalue (just move)
        : width(w), height(h), posX(x), posY(y) {};
    
    void GenerateLeaf(int depth, std::vector<TreeData>&& bodies);

    void GenerateLeaf(int depth, std::vector<TreeData>& bodies);

    bool contains(vec2 x);

    double CalcTotalMass();

    vec2 CalcCOM();

    void ResetNode();   //erase all nodes, bodies in leaves
};

#endif