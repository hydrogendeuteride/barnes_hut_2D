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
#include <utility>
#include <vector>

constexpr double ViewHeight = 1920;
constexpr double ViewWidth = 1080;

constexpr double Simsize = 327680;

constexpr double MinMass = 1.0;
constexpr double MaxMass = 5.0;


sf::RenderWindow window(sf::VideoMode(1920, 1080), "barnes-hut");

template<typename TreeData>
void CalculateMove(BHtree<TreeData> b, std::vector<TreeData> &bodies, Node<TreeData> *root, double timestep);

template<typename TreeData>
void Bodies_Uniform(std::vector<TreeData> &bodies, unsigned int number, double size, double mass_min, double mass_max);

template <typename TreeData>
void Boundary(std::vector<TreeData> &bodies);

template<typename TreeData>
void render(sf::RenderWindow& window, const std::vector<TreeData>& bodies);

int main()
{
    sf::View View(sf::FloatRect(0, 0, ViewHeight / 2, ViewWidth / 2));

    std::vector<body> bodies;
    Bodies_Uniform(bodies, 10000, Simsize , MinMass, MaxMass);

    Node<body> Root(Simsize, Simsize, 0.0, 0.0);
    
    BHtree<body> BH;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Root.GenerateLeaf(50, std::forward<std::vector<body>>(bodies));
        CalculateMove(BH, bodies, &Root, 0.5);
        Boundary(bodies);
        Root.ResetNode();


    }

    return 0;
}

template<typename TreeData>
void CalculateMove(BHtree<TreeData> b, std::vector<TreeData> &bodies, Node<TreeData> *root, double timestep)    //calculate one step
{
    for (auto& x : bodies) 
        b.Calc_Next_Phase_Space(x, root, timestep);
}

template <typename TreeData>
void Boundary(std::vector<TreeData> &bodies)
{
    for (auto& body : bodies) 
    {
        if ( (body.x(0,0) > Simsize && body.v(0,0) > 0) 
                    || (body.x(0,0) < 0 && body.v(0,0) < 0)) //x axis
            body.v(0,0) = -body.v(0,0); 

        if ((body.x(1,0) > Simsize && body.v(1,0) > 0) 
                    || (body.x(1,0) < Simsize && body.v(1,0) < 0))  //y axis
            body.v(1,0) = -body.v(1,0);    
    }
}

template<typename TreeData>
void Bodies_Uniform(std::vector<TreeData> &bodies, unsigned int number, double size, double mass_min, double mass_max)
{
    std::random_device rand;
    std::mt19937 gen(rand());

    std::uniform_real_distribution<double> r(0, Simsize);
    std::uniform_real_distribution<double> m(mass_min, mass_max);

    for (int i = 0; i < number; i++) 
    {
        
        bodies.emplace_back(vec2(r(gen) * 0.3 + Simsize / 2.0, r(gen) * 0.3 + Simsize / 2.0),
                            vec2(1.0 / r(gen) * 0.3, 1.0 / r(gen) * 0.3), 
                            m(gen)); 
        
    }
}

template<typename TreeData>
void render(sf::RenderWindow& window, const std::vector<TreeData>& bodies)
{
    window.clear();
    
    
    for (const auto& x : bodies) 
    {
        
    }
}