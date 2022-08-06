#include "qtree.hpp"

template <typename TreeData>
void Node<TreeData>::GenerateLeaf(int depth, std::vector<TreeData> bodies)
{
    std::vector<TreeData> q1, q2, q3, q4;

    this->bodies = bodies;

    for (auto body1 : this->bodies)
    {
        if (body1.x(0,0) < (this->posX + (this->width / 2.0)))
        {
            if (body1.x(1,0) < (this->posY + (this->height / 2.0))) 
                q1.push_back(body1);
            else
                q3.push_back(body1);
        }
        else 
        {
            if (body1.x(1,0) < (this->posY + (this->height / 2.0)))
                q2.push_back(body1);
            else
                q4.push_back(body1);
        }
    }

    if (depth < MAX_DEPTH && q1.size() > 1)
    {
        this->hasLeaf = true;
        leaf0 = std::make_unique<Node<TreeData>>(this->width / 2.0, this->height / 2.0,
                            this->posX, this->posY); //q1`s ownership is moved to leaf0, only the last leaf gets real body data
        
        GenerateLeaf(depth + 1, q1);
    }

    if (depth < MAX_DEPTH && q2.size() > 1)
    {
        this->hasLeaf = true;
        leaf1 = std::make_unique<Node<TreeData>>(this->width / 2.0, this->height / 2.0, 
                                this->posX + (this->width / 2.0), this->posY);
        
        GenerateLeaf(depth + 1, q2);
    }

    if (depth < MAX_DEPTH && q3.size() > 1)
    {
        this->hasLeaf = true;
        leaf2 = std::make_unique<Node<TreeData>>(this->width / 2.0, this->height / 2.0, 
                            this->posX, this->posY + (this->height / 2.0));
        
        GenerateLeaf(depth + 1, q3);
    }

    if (depth < MAX_DEPTH && q4.size() > 1)
    {
        this->hasLeaf = true;
        leaf3 = std::make_unique<Node<TreeData>>(this->width / 2.0, this->height / 2.0, 
                           this->posX + (this->width / 2.0), this->posY + this->height / 2.0);
        
        GenerateLeaf(depth + 1, q4);
    }
}
//Maybe recursion optimization on g++ -O2??
// O(n log n) time complexity

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
void Node<TreeData>::reset()
{
    if(!this->hasLeaf)
    {
        leaf0->reset();
        leaf1->reset();
        leaf2->reset();
        leaf3->reset();
    }
    else 
    {
        this->bodies.clear();
    }
}

template <typename TreeData>
double Node<TreeData>::CalcTotalMass()
{
    return std::accumulate(this->bodies.begin(), this->bodies.end(), 0,
                             [](double sum, const auto& x) {return sum + x.x.mass;});
}

template <typename TreeData>
vec2 Node<TreeData>::CalcCOM()
{
    double mass =  CalcTotalMass();

    vec2 massDist = std::accumulate(this->bodies.begin(), this->bodies.end(), vec2(0, 0),
                        [](vec2 sum, const auto& x) {return sum + (x.mass * x.x);});
    
    return massDist / mass;
}