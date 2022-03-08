#ifndef _QTREE_H_
#define _QTREE_H_

#include <vector>

template <typename TreeData>
class Node
{
public:
    std::vector<Node*> leaves;
    
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