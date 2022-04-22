#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "physics.hpp"
#include "qtree.hpp"
#include <random>
#include <cmath>

constexpr double ViewHeight = 1920;
constexpr double ViewWidth = 1080;

constexpr double Simsize = 327680;



sf::RenderWindow window(sf::VideoMode(1920, 1080), "barnes-hut");

template<typename TreeData>
void calculatemove(Node<TreeData> *root);

template<typename TreeData>
void bodies_disk(std::vector<TreeData> bodies, unsigned int number, double width, double height, 
                    double mass_min, double mass_max, double dist_min, double dist_max);

int main()
{
    sf::View View(sf::FloatRect(0, 0, ViewHeight / 2, ViewWidth / 2));
        
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            
        }
    }
    
    std::vector<body> bodies;

    return 0;
}

template<typename TreeData>
void calculatemove(Node<TreeData> *root, std::vector<body> &bodies)
{
    std::vector<TreeData> bodies_new;
    for (const auto& x : bodies) 
    {
        auto [vel, pos] = treeTraversal(x, root, 1.0, semi_implict_euler);
        bodies_new.emplace_back(pos, vel, x.mass);
    }

    bodies = std::move(bodies_new);
}
//https://stackoverflow.com/questions/69025611/c-how-do-i-return-2-values-using-tuple-and-autovalue1-value2-as-c-says

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