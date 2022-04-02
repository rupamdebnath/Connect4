#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int HEIGHT = 6;
const int WIDTH = 7;

Texture board;
Texture red_checker;
Texture blue_checker;

int currentBoard[HEIGHT][WIDTH];
int turns, redcount = 0, bluecount = 0;
bool redTurn;
int columnMax[WIDTH];

Sprite main_board;
Sprite blue[21];
Sprite red[21];

void set()
{
    board.loadFromFile("Images/board.png");
    red_checker.loadFromFile("Images/red.png");
    blue_checker.loadFromFile("Images/blue.png");

    main_board.setTexture(board);
    for (int i = 0; i < 21; i++)
    {
        red[i].setTexture(red_checker);
        blue[i].setTexture(blue_checker);
    }

    redTurn = true;
    turns = 0;
    redcount = 0;
    bluecount = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        columnMax[i] = 0;
        for (int j = 0; j < WIDTH; j++)
        {
            currentBoard[i][j] = 0;
        }
    }
}

void PlayRedTurn(int a)
{
    if (columnMax[a - 1] < HEIGHT)
    {
        columnMax[a - 1]++;
        for (int i = HEIGHT - 1; i >= 0; i--)
        {
            if (currentBoard[a - 1][i] == 0)
            {
                currentBoard[a - 1][i] = 1;
                red[redcount].setPosition((a - 1) * 100, i * 100);
                redcount++;
                break;
            }
        }
    }

}

void PlayBlueTurn(int a)
{
    if (columnMax[a - 1] < HEIGHT)
    {
        columnMax[a - 1]++;
        for (int i = HEIGHT - 1; i >= 0; i--)
        {
            if (currentBoard[a - 1][i] == 0)
            {
                currentBoard[a - 1][i] = 1;
                blue[bluecount].setPosition((a - 1) * 100, i * 100);
                bluecount++;
                break;
            }
        }
    }

}

int main()
{
    RenderWindow window(sf::VideoMode(700, 600), "Connect4");
    //CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Blue);
    set();
    while (window.isOpen())
    {
        Event e;
        Vector2i pos;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
            if (e.type == Event::MouseButtonPressed)
            {
                if (e.key.code == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(window);
                    pos.x /= 100;
                    pos.y /= 100;
                    pos.x++;
                    pos.y++;
                    //cout << pos.x << " " << pos.y << endl;
                    if (redTurn)
                    {
                        PlayRedTurn(pos.x);
                        redTurn = false;
                    }
                    else
                    {
                        PlayBlueTurn(pos.x);
                        redTurn = true;
                    }
                    turns++;
                }
            }
        }
        window.clear();
        window.draw(main_board);
        for (int i = 0; i < redcount; i++) 
        {
            window.draw(red[i]);
        }
        for (int i = 0; i < bluecount; i++)
        {
            window.draw(blue[i]);
        }
        window.display();
        window.display();
    }

    return 0;
}