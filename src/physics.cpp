#include "physics.hpp"
#include <tuple>
#include <vector>


template <typename ... Ts, std::size_t ... Is>
std::tuple<Ts...> sumT (std::tuple<Ts...> const & t1,
                        std::tuple<Ts...> const & t2,
                        std::index_sequence<Is...> const &)
 { return { (std::get<Is>(t1) + std::get<Is>(t2))... }; }

template <typename ... Ts>
std::tuple<Ts...> operator+ (std::tuple<Ts...> const & t1,
                             std::tuple<Ts...> const & t2)
 { return sumT(t1, t2, std::make_index_sequence<sizeof...(Ts)>{}); }

template<typename TreeData>
std::tuple<vec2, vec2> treeTraversal(TreeData leaf, Node<TreeData> *rootNode, double timestep, 
                    std::function<std::tuple<vec2, vec2>(vec2 &p, vec2 &q, double leafMass,
                     double rootMass, vec2 &dist_v, double timestep)> Integrator, 
                     std::tuple<vec2, vec2> res)
{
    std::tuple<vec2, vec2> ret = std::make_tuple(vec2(0.0, 0.0), vec2(0.0, 0.0));

    vec2 leafCOM  = leaf.x;
    vec2 rootCOM = CalcCOM(rootNode);

    vec2 dist_v = leafCOM - rootCOM;
    double dist = dist_v.norm();

    if ((rootNode->width / dist <= THETA) || rootNode->hasLeaf == false)
    {
        vec2 vel = leaf.v;
        vec2 pos = leaf.x;

        double leafmass = leaf.mass;
        double rootmass = CalcTotalMass(rootNode);

        ret = Integrator(vel, pos, leafmass, rootmass, dist_v, timestep);            
        return ret;
    }
    else 
    {
        return treeTraversal(leaf, rootNode -> leaf0, timestep, Integrator, res + ret);
        return treeTraversal(leaf, rootNode -> leaf1, timestep, Integrator, res + ret);
        return treeTraversal(leaf, rootNode -> leaf2, timestep, Integrator, res + ret);
        return treeTraversal(leaf, rootNode -> leaf3, timestep, Integrator, res + ret);
    }
} // O(log N), recursion optimized

std::tuple<vec2, vec2> semi_implict_euler(const vec2 &v, const vec2 &x, 
                                            const double leafMass, const double rootMass,
                                            const vec2 &dist_v, const double timestep)
{
    vec2 v_1, x_1;
    v_1 = v + acceleration(leafMass, rootMass, dist_v) * timestep;
    x_1 = x + (v_1 / leafMass) * timestep;

    return std::make_tuple(v_1, x_1);
}

inline vec2 acceleration(const double leafMass, const double rootMass, const vec2 &dist)
{
    return -((G_CONST * leafMass * rootMass) / (std::pow(dist.norm(), 3))) * dist;
}
