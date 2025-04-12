#include <iostream>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <cmath>  // for std::cos, std::sin
#define PI 3.14159265



class Circle {
    sf::CircleShape m_Circle;
    std::string m_name;
    sf::Font myFont;

    float m_x;
    float m_y;
    float m_vx;
    float m_vy;
    int   m_r;
    int   m_g;
    int   m_b;
    float m_radius;
    float m_segments;
public:       
    Circle(const std::string& name,
        float x, float y, float vx, float vy, int r,
        int g, int b, float radius, float segments,float speed, float angleDeg)
        : m_name(name), m_x(x), m_y(y), m_vx(vx), m_vy(vy),
        m_r(r), m_g(g), m_b(b), m_radius(radius), m_segments(segments)

    {
        float angleRad = angleDeg * PI / 180.0f;
        m_vx = speed * std::cos(angleRad);
        m_vy = speed * std::sin(angleRad);

        m_Circle.setFillColor(sf::Color(m_r, m_g, m_b));
        m_Circle.setPointCount(static_cast<size_t>(m_segments));
        m_Circle.setRadius(m_radius);
        m_Circle.setOrigin(m_radius, m_radius);
        m_Circle.setPosition(m_x, m_y);


    }
    ~Circle() {};

    void updatePosition()
    {
        
        m_x += m_vx;
        m_y += m_vy;

        // ¼òµ¥±ß½ç·´µ¯Âß¼­
        if (m_x - m_radius < 0 || m_x + m_radius > 800) m_vx *= -1;
        if (m_y - m_radius < 0 || m_y + m_radius > 600) m_vy *= -1;

        m_Circle.setPosition(m_x, m_y);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_Circle);
    }


};



class Draw {
    unsigned int m_width = 800;
    unsigned int m_height = 600;

    sf::Font myFont;
    sf::Text m_text;
    sf::RenderWindow m_window;

    std::vector<Circle> m_Circles;

public:
    Draw() : m_window(sf::VideoMode(m_width, m_height), "myword") {
        m_window.setFramerateLimit(60);

        m_Circles.emplace_back("ball1", 200, 200, 1.5f, 1.2f, 255, 100, 150, 30.0f, 32.0f, 2.0f, 45.0f);
        m_Circles.emplace_back("ball2", 600, 400, -2.0f, -1.5f, 100, 255, 150, 40.0f, 32.0f, 5.0f, 120.0f);
        m_Circles.emplace_back("ball3", 100, 500, 2.0f, -1.0f, 100, 150, 255, 25.0f, 32.0f, 3.5f, 270.0f);
        m_Circles.emplace_back("ball4", 700, 100, -1.5f, 1.8f, 255, 255, 100, 35.0f, 32.0f, 1.0f, 10.0f);
    }

        ~Draw() {};

        void LoadFont()
        {
            if (!myFont.loadFromFile("fonts/tech.ttf"))
            {
                // if we can't load the font, print an error to the error console and exit
                std::cerr << "Could not load font!\n";
                exit(-1);
            }

            m_text.setFont(myFont);
            m_text.setString("Hello world");
            m_text.setCharacterSize(24); 
            m_text.setFillColor(sf::Color::White);
            m_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        }


        void mainLoop()
        {
            while (m_window.isOpen())
            {
                sf::Event event;
                while (m_window.pollEvent(event))
                {
                    if (event.key.code == sf::Keyboard::Escape) {
                        m_window.close();
                    }
                    if (event.type == sf::Event::KeyPressed)
                    {
                        std::cout << "Key pressed with code = " << event.key.code << "\n";
                    }
                }

                for (auto& circle : m_Circles)
                {
                    
                    circle.updatePosition();

                }
                
                m_window.clear();

                for (auto& circle : m_Circles)
                {
                    circle.Draw(m_window);
                }
                m_window.draw(m_text);

                m_window.display();               // call the window display function
            }
        }
};


int main(int argc, char* argv[])
{

    Draw draw;
    draw.LoadFont();
    draw.mainLoop();



    return 0;
}