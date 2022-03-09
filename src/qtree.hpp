#ifndef _QTREE_H_
#define _QTREE_H_

#include <vector>
#include <memory>

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

    Node(std::vector<TreeData> &b, double w, double h, double x, double y) : bodies(b), width(w), height(h), posX(x), posY(y) {};
    
    void generateLeaf(int depth, std::vector<TreeData> &bodies);
    
    ~Node();
};

#endif