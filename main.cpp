#include <iostream>
#include <chrono>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "point.h"
#include "triangle.h"
#include "delaunay.h"
#include "edge.h"

using namespace std;



inline float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}



int main()
{

    
    int numberPoints = 10;
    bool GENERATE_POINTS_IN_CODE = true;  


    vector<Point2> points;
    const int BOUNDINGBOXWEIGHT = 1000;
    const int BOUNDINGBOXHEIGHT = 1000;


    if (GENERATE_POINTS_IN_CODE) {   
        srand(time(NULL));
        cout << "Generowanie " << numberPoints << " punktow" << endl;
        for (int i = 0; i < numberPoints; i++) {

            float pktx = RandomFloat(50, BOUNDINGBOXWEIGHT - 50);
            float pkty = RandomFloat(50, BOUNDINGBOXWEIGHT - 50);
            cout << "Punkt: (" << pktx << ", " << pkty << ");" << endl;
           
            points.push_back(Point2(pktx, pkty));
        }
    }
    else { return 0; }
 
    Delaunay triangulation;
    vector<Triangle*> currentTriangle;
    

    triangulation.triangulate(points, currentTriangle);

    
    
    vector<Edge*> edges = triangulation.getEdges();

    ofstream outFile;
    outFile.open("C:/Users/Gabriela/source/repos/GO_projekt/segments.txt");
    

    for (auto p = begin(edges); p != end(edges); p++) {
        outFile << (*p)->p1.x << " " << (*p)->p2.x << " " << (*p)->p1.y << " " << (*p)->p2.y << endl;
    }
    outFile.close();


    
    sf::RenderWindow window(sf::VideoMode(BOUNDINGBOXWEIGHT, BOUNDINGBOXHEIGHT), "Delaunay ");

    
    vector<array<sf::Vertex, 2> > lines;
    for (auto e = begin(edges); e != end(edges); e++) {
        lines.push_back({ {
                                 sf::Vertex(sf::Vector2f((*e)->p1.x + 1, (*e)->p1.y + 1)),
                                 sf::Vertex(sf::Vector2f((*e)->p2.x + 1, (*e)->p2.y + 1))
                         } });
    }
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        
        for (auto l = begin(lines); l != end(lines); l++) {
            window.draw((*l).data(), 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}