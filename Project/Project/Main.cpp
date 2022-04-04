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
int columnMax[WIDTH] = { 0 };

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
        //columnMax[i] = 0;
        for (int j = 0; j < WIDTH; j++)
        {
            currentBoard[i][j] = 0;            
        }
    }
    for (int i = 0; i < WIDTH; i++)
    {
        columnMax[i] = 0;
    }
}

void PlayRedTurn(int a)
{
    if (columnMax[a - 1] < HEIGHT)
    {
        columnMax[a - 1]++;
        for (int i = HEIGHT - 1; i >= 0; i--)
        {
            if (currentBoard[i][a - 1] == 0)
            {                
                currentBoard[i][a-1] = 1;
                red[redcount].setPosition(((a - 1) * 100), (i * 100));
                redcount++;
                redTurn = false;
                break;
            }
        }
    }
    else
        redTurn = true;
}

void PlayBlueTurn(int a)
{
    if (columnMax[a - 1] < HEIGHT)
    {
        columnMax[a - 1]++;
        for (int i = HEIGHT - 1; i >= 0; i--)
        { 
            if (currentBoard[i][a - 1] == 0)
            {
                currentBoard[i][a - 1] = 2;
                blue[bluecount].setPosition(((a - 1) * 100), (i * 100));
                bluecount++;
                redTurn = true;
                break;
            }
        }
    }
    else
        redTurn = false;
}

bool EndGame()
{
    //check horizontal match of 4
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH - 3; j++)
        {
            if (currentBoard[i][j] == 1 && currentBoard[i][j + 1] == 1 && currentBoard[i][j + 2] == 1 && currentBoard[i][j + 3] == 1)
            {
                cout << "Red has won!\n";                
                return true;
            }
            else if (currentBoard[i][j] == 2 && currentBoard[i][j + 1] == 2 && currentBoard[i][j + 2] == 2 && currentBoard[i][j + 3] == 2)
            {
                cout << "Blue has won!\n";                
                return true;
            }
        }
    }

    //check vertical match of 4
    for (int i = 0; i < HEIGHT - 3; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (currentBoard[i][j] == 1 && currentBoard[i + 1][j] == 1 && currentBoard[i + 2][j] == 1 && currentBoard[i + 3][j] == 1)
            {
                cout << "Red has won!\n";                
                return true;
            }
            else if (currentBoard[i][j] == 2 && currentBoard[i + 1][j] == 2 && currentBoard[i + 2][j] == 2 && currentBoard[i + 3][j] == 2)
            {
                cout << "Blue has won!\n";                
                return true;
            }
        }
    }

    //check diagonal match of 4
    for (int i = 0; i < HEIGHT - 3; i++)
    {
        for (int j = 0; j < WIDTH - 3; j++)
        {
            if (currentBoard[i][j] == 1 && currentBoard[i + 1][j + 1] == 1 && currentBoard[i + 2][j + 2] == 1 && currentBoard[i + 3][j + 3] == 1)
            {
                cout << "Red has won!\n";               
                return true;
            }
            else if (currentBoard[i][j] == 2 && currentBoard[i + 1][j + 1] == 2 && currentBoard[i + 2][j + 2] == 2 && currentBoard[i + 3][j + 3] == 2)
            {
                cout << "Blue has won!\n";                
                return true;
            }
        }
    }

    for (int i = 0; i < HEIGHT - 3; i++)
    {
        for (int j = WIDTH - 1; j >= 3; j--)
        {
            if (currentBoard[i][j] == 1 && currentBoard[i + 1][j - 1] == 1 && currentBoard[i + 2][j - 2] == 1 && currentBoard[i + 3][j - 3] == 1)
            {
                cout << "Red has won!\n";                
                return true;
            }
            else if (currentBoard[i][j] == 2 && currentBoard[i + 1][j - 1] == 2 && currentBoard[i + 2][j - 2] == 2 && currentBoard[i + 3][j - 3] == 2)
            {
                cout << "Blue has won!\n";                
                return true;
            }
        }
    }

    //check if noone has got a match, hence match tied
    if (turns == 42)
    {
        cout << "Draw game between Red and Blue, its a Tie!" << endl;        
        return true;
    }        
    return false;
}

int main()
{
    RenderWindow window(sf::VideoMode(700, 600), "Connect4");

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
                    if (redTurn)
                    {
                        PlayRedTurn(pos.x);                        
                    }
                    else
                    {
                        PlayBlueTurn(pos.x);                        
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
        if (EndGame())
        {
            system("pause");
            set();
        }
    }

    return 0;
}