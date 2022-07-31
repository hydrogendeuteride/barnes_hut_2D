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
void CalculateMove(Node<TreeData> *root, double timestep);

template<typename TreeData>
void bodies_disk(std::vector<TreeData> bodies, unsigned int number, double width, double height, 
                    double mass_min, double mass_max, double dist_min, double dist_max);

int main()
{
    sf::View View(sf::FloatRect(0, 0, ViewHeight / 2, ViewWidth / 2));
    
    std::vector<body> bodies;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            
        }
    }

    return 0;
}

template<typename TreeData>
void CalculateMove(Node<TreeData> *root, std::vector<body> &bodies, double timestep)
{
    for (auto& x : bodies) 
        Calc_Next_Phase_Space(x, root, timestep);
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