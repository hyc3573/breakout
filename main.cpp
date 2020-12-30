#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <Windows.h>

#define SWIDTH 800
#define SHEIGHT 800

#define PWIDTH 60
#define PHEIGHT 10

#define BWIDTH 20
#define BHEIGHT 14

#define BMARGIN 5
#define PMARGIN 10

#define BLRAD 5
#define BLMARGIN 50

#define PI 3.1415926

typedef int Square;

using namespace std;
using namespace sf;

int main()
{
    unsigned int t = GetTickCount64();
    srand(t);

    RenderWindow window(VideoMode(SWIDTH, SHEIGHT), L"È¥µ·! ÆÄ±«! ¸Á°¡¤¡!");

    Event event;

    Clock clock;

    RectangleShape paddle = RectangleShape(Vector2f(PWIDTH, PHEIGHT));
    paddle.setFillColor(Color::White);
    paddle.setOrigin(PWIDTH / 2, PHEIGHT / 2);

    CircleShape ball = CircleShape(BLRAD);
    ball.setFillColor(Color::White);
    ball.setOrigin(BLRAD, BLRAD);

    float direction;
    float bSpeed;

    int movement;
    float speed;

    float dt = 0;

    auto reset = [&]()
    {
        ball.setPosition(SWIDTH / 2, SHEIGHT - PMARGIN - BLMARGIN);
        paddle.setPosition(SWIDTH / 2, SHEIGHT - PMARGIN);

        direction = (rand() % 90 + 135) * PI / 180;
        bSpeed = 500.f;

        movement = 0;
        speed = 500.f;
    }; // Á¸³ª ÁÁ±º?

    reset();

    while (window.isOpen()) 
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::Left:
                    movement = -1;
                    break;
                case Keyboard::Right:
                    movement = 1;
                    break;
                }
                break;

            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Left:
                    if (movement == -1)
                    {
                        movement = 0;
                    }
                    break;
                case Keyboard::Right:
                    if (movement == 1)
                    {
                        movement = 0;
                    }
                    break;
                }
                break;
            }
        }

        if (ball.getPosition().x <= BLRAD || ball.getPosition().x >= SWIDTH - BLRAD)
        {
            direction = 2 * PI - direction;
        }

        if (ball.getPosition().y <= BLRAD || paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            direction = PI - direction;
        }

        if (ball.getPosition().y >= SHEIGHT - BLRAD)
        {
            reset();
        }

        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        paddle.move(movement * speed * dt, 0);
        paddle.setPosition(max(min(paddle.getPosition().x, (float)SWIDTH - PWIDTH / 2), 0.f + PWIDTH / 2), paddle.getPosition().y);

        ball.move(sin(direction) * bSpeed * dt, cos(direction) * bSpeed * dt);

        window.clear(Color::Black);

        window.draw(paddle);
        window.draw(ball);

        window.display();
    }
    return 0;
}