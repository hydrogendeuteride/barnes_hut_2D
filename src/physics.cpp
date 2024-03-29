#include "physics.hpp"
#include "qtree.hpp"
#include <vector>
#include <queue>

/*template <typename ... Ts, std::size_t ... Is>
std::tuple<Ts...> sumT (std::tuple<Ts...> const & t1,
                        std::tuple<Ts...> const & t2,
                        std::index_sequence<Is...> const &)
 { return { (std::get<Is>(t1) + std::get<Is>(t2))... }; }

template <typename ... Ts>
std::tuple<Ts...> operator+ (std::tuple<Ts...> const & t1,
                             std::tuple<Ts...> const & t2)
 { return sumT(t1, t2, std::make_index_sequence<sizeof...(Ts)>{}); }*/

/*template<typename TreeData>
inline vec2 BHtree<TreeData>::Acceleration(const double leafMass, const double rootMass, const vec2 &dist)
{
    return -((G_CONST * leafMass * rootMass) / (std::pow(dist.norm(), 3))) * dist;
}*/
/*
template<typename TreeData>
vec2 BHtree<TreeData>::Net_Acceleration(TreeData &leaf, Node<TreeData> *rootNode)
{
    vec2 Net_acc = vec2(0.0, 0.0);

    std::queue<Node<TreeData>*> q;
    q.push(rootNode);

    while (!q.empty()) 
    {
        Node<TreeData> *tmp = q.front();
        q.pop();

        vec2 leafCOM  = leaf.x;
        vec2 rootCOM = CalcCOM(rootNode);

        vec2 dist_v = leafCOM - rootCOM;
        double dist = dist_v.norm();

        if ( ( (tmp->width / dist <= THETA) || tmp->hasLeaf == false ) )
        {
            if (!tmp->contains(leaf.x))
                Net_acc += Acceleration(leaf.mass, tmp->CalcTotalMass(), dist_v);
        }

        if (tmp->leaf0 != nullptr) 
            q.push(tmp->leaf0);  

        if (tmp->leaf1 != nullptr) 
            q.push(tmp->leaf1);  
        
        if (tmp->leaf2 != nullptr) 
            q.push(tmp->leaf2);  
        
        if (tmp->leaf3 != nullptr) 
            q.push(tmp->leaf3);    
    }

    return Net_acc;
} // Iterative, O(n)
*//*
template<typename TreeData>
void BHtree<TreeData>::Calc_Next_Phase_Space(TreeData& leaf, Node<TreeData> *rootNode, double timestep)
{
    std::tuple<vec2, vec2> p = std::make_tuple(leaf.x, leaf.v);
    std::tuple<vec2, vec2> tmp;

    Integrator::Semi_Implicit_Euler euler;
    tmp = euler(p, Net_Acceleration(leaf, rootNode), timestep);

    auto [x, v] = tmp;
    leaf.x = x;
    leaf.v = v;
}
*/