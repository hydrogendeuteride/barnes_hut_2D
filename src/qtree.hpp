#ifndef _QTREE_H_
#define _QTREE_H_

#include <vector>
#include <memory>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>

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
    std::shared_ptr<Node> leaf0;
    std::shared_ptr<Node> leaf1;
    std::shared_ptr<Node> leaf2;
    std::shared_ptr<Node> leaf3;
    
    bool hasLeaf = false;
    
    double width;
    double height;
    double posX;
    double posY;

    std::vector<TreeData> bodies;

    Node(double w, double h, double x, double y) //empty node
        : width(w), height(h), posX(x), posY(y) {};

    Node(std::vector<TreeData>& bodies, double w, double h, double x, double y) //copy
        : bodies(bodies), width(w), height(h), posX(x), posY(y) {};
    
    Node(std::vector<TreeData>&& bodies, double w, double h, double x, double y) //get rvalue (just move)
        : bodies(bodies), width(w), height(h), posX(x), posY(y) {};

    bool contains(vec2 x);

    double CalcTotalMass();

    vec2 CalcCOM();

    void ResetNode();   //erase all nodes, bodies in leaves
};

template <typename TreeData>
bool Node<TreeData>::contains(vec2 x)
{
    for (auto& i : this->bodies) 
    {
        if (i.x == x) 
        {
            return true;
        }
    }

    return false;
}

template <typename TreeData>
double Node<TreeData>::CalcTotalMass()
{
    return std::accumulate(this->bodies.begin(), this->bodies.end(), 0,
                             [](double sum, const auto& x) {return sum + x.mass;});
}

template <typename TreeData>
vec2 Node<TreeData>::CalcCOM()
{
    double mass =  CalcTotalMass();

    vec2 massDist = std::accumulate(this->bodies.begin(), this->bodies.end(), vec2(0, 0),
                        [](vec2 sum, const auto& x) {return sum + (x.mass * x.x);});
    
    return massDist / mass;
}

template<typename TreeData>
void GenLeaf_iterative(std::shared_ptr<Node<TreeData>> root, int depth)
{
    std::queue<std::shared_ptr<Node<TreeData>>> queue;
    queue.push(root);

    while (!queue.empty()) 
    {
        std::shared_ptr<Node<TreeData>> tmp = queue.front();
        queue.pop();

        std::vector<TreeData> q1, q2, q3, q4;

        for (auto body1 : tmp->bodies)
        {
            if (body1.x(0,0) < (tmp->posX + (tmp->width / 2.0)))
            {
                if (body1.x(1,0) < (tmp->posY + (tmp->height / 2.0))) 
                    q1.push_back(body1);
                else
                    q3.push_back(body1);
            }
            else 
            {
                if (body1.x(1,0) < (tmp->posY + (tmp->height / 2.0)))
                    q2.push_back(body1);
                else
                    q4.push_back(body1);
            }
        }
        //https://stackoverflow.com/questions/43070571/is-it-possible-to-stdmove-local-stack-variables

        if (depth < MAX_DEPTH && q1.size() >= 1)
        {
            tmp->hasLeaf = true;
            tmp->leaf0 = std::make_shared<Node<TreeData>>(std::move(q1) 
                            ,tmp->width / 2.0, tmp->height / 2.0, tmp->posX, tmp->posY);
                             //q1`s ownership is moved to leaf0
            depth++;
            queue.push(tmp->leaf0);
        }

        if (depth < MAX_DEPTH && q2.size() >= 1)
        {
            tmp->hasLeaf = true;
            tmp->leaf1 = std::make_shared<Node<TreeData>>(std::move(q2) 
                            ,tmp->width / 2.0, tmp->height / 2.0, tmp->posX, tmp->posY);
                             //q1`s ownership is moved to leaf0
            depth++;
            queue.push(tmp->leaf1);
        }

        if (depth < MAX_DEPTH && q3.size() >= 1)
        {
            tmp->hasLeaf = true;
            tmp->leaf2 = std::make_shared<Node<TreeData>>(std::move(q3) 
                            ,tmp->width / 2.0, tmp->height / 2.0, tmp->posX, tmp->posY);
                             //q1`s ownership is moved to leaf0
            depth++;
            queue.push(tmp->leaf2);
        }

        if (depth < MAX_DEPTH && q4.size() >= 1)
        {
            tmp->hasLeaf = true;
            tmp->leaf3 = std::make_shared<Node<TreeData>>(std::move(q4) 
                            ,tmp->width / 2.0, tmp->height / 2.0, tmp->posX, tmp->posY);
                             //q1`s ownership is moved to leaf0
            depth++;
            queue.push(tmp->leaf3);
        }
    }
}

template<typename TreeData>
void Reset(std::shared_ptr<Node<TreeData>> root)
{
    std::stack<std::shared_ptr<Node<TreeData>>> stack, s2;
    std::shared_ptr<Node<TreeData>> node;
    stack.push(root);

    while (!stack.empty()) 
    {
        node = stack.top();
        stack.pop();
        s2.push(node);

        if (node->leaf0 != nullptr) 
            stack.push(node.leaf0);
        
        if (node->leaf1 != nullptr) 
            stack.push(node.leaf1);
        
        if (node->leaf2 != nullptr) 
            stack.push(node.leaf2);

        if (node->leaf3 != nullptr) 
            stack.push(node.leaf3);
    }

    while (!s2.empty()) 
    {
        node = s2.top();
        s2.pop();

        node->bodies.clear();
        node.reset();
    }
}

#endif