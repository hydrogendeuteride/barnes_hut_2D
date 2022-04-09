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

    Node(std::vector<TreeData> b, double w, double h, double x, double y) 
        : bodies(std::move(b)), width(w), height(h), posX(x), posY(y) {};
    
    void generateLeaf(int depth, std::vector<TreeData> bodies);
    void reset();

    ~Node();
};

template <typename TreeData>
double CalcTotalMass(Node<TreeData> *node);

template <typename TreeData>
vec2 CalcCOM(Node<TreeData> *node);

#endif