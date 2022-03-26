#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <complex>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "physics.hpp"
#include "qtree.hpp"
#include <random>
#include <cmath>
#include <tuple>
#include <vector>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "barnes-hut");

template<typename TreeData>
void calculatemove(Node<TreeData> *root);

template<typename TreeData>
void bodies_disk(std::vector<TreeData> bodies, unsigned int number, double width, double height, 
                    double mass_min, double mass_max, double dist_min, double dist_max);

int main()
{
    std::cout<<"testing"<<std::endl;
    
    std::vector<body> bodies;

    return 0;
}

template<typename TreeData>
void calculatemove(Node<TreeData> *root, std::vector<body> &bodies)
{
    for (const auto& x : bodies) 
    {
        x.v = std::get<0>(treeTraversal(x, root, 1.0, semi_implict_euler));
        x.x = std::get<1>(treeTraversal(x, root, 1.0, semi_implict_euler));
    }
}

template<typename TreeData>
void bodies_uniform(std::vector<TreeData> &bodies, unsigned int number, double width, double height, 
                    double mass_min, double mass_max, double dist_min, double dist_max)
{
    std::random_device rand;
    std::mt19937 gen(rand());

    std::uniform_real_distribution<double> r(width, height);
    std::uniform_real_distribution<double> m(mass_min, mass_max);

    for (int i = 0; i < number; i++) 
    {
        bodies.emplace_back(vec2(r(gen) * 0.3 , r(gen) * 0.3),
                            vec2(r(gen) * dist_max * 0.1, r(gen) * dist_max * 0.1), 
                            m); 
    }
}