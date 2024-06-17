#include <ncurses.h>
#include <iostream>
#include <vector>

struct UnitType
{
    int s_x, s_y;
    UnitType(int s_col, int s_row)
    {
        s_x = s_col;
        s_y = s_row;
    }
    UnitType()
    {
        s_x = 0;
        s_y = 0;
    }
};

class Plane
{
protected:
    int width;
    int height;

public:
    Plane(int w, int h)
    {
        width = w;
        height = h;
    }

    void draw()
    {

        move(0, 0);
        addch('+');
        move(0, width - 1);
        addch('+');
        move(height - 1, 0);
        addch('+');
        move(height - 1, width - 1);
        addch('+');

        for (int i = 1; i < width - 1; i++)
        {
            move(0, i);
            addch('-');
        }

        for (int i = 1; i < height - 1; i++)
        {
            move(i, 0);
            addch('|');
        }

        for (int i = 1; i < width - 1; i++)
        {
            move(height - 1, i);
            addch('-');
        }

        for (int i = 1; i < height - 1; i++)
        {
            move(i, width - 1);
            addch('|');
        }
    }
};

class SnakeGame
{
protected:
    int max_width;
    int max_height;

    std::vector<UnitType> snake;
    char snake_char = 'X';

    UnitType food;
    char food_char = 'O';

    int delay = 1000;

    Plane *plane;

public:
    SnakeGame()
    {
        initscr();
        nodelay(stdscr, true);
        keypad(stdscr, true);
        noecho();
        curs_set(0);

        max_width = getmaxx(stdscr) / 2;
        max_height = getmaxy(stdscr) / 2;

        plane = new Plane(max_width, max_height);

        plane->draw();

        srand(time(NULL));
        insert_food();

        for (int i = 0; i < 3; ++i)
        {
            snake.push_back(UnitType((max_width / 2) - i, max_height / 2));
        }

        for (int i = 0; i < ((int)snake.size()); i++)
        {
            move(snake[i].s_y, snake[i].s_x);
            addch(snake_char);
        }

        move(food.s_y, food.s_x);
        addch(food_char);
        refresh();
    }

    ~SnakeGame()
    {
        nodelay(stdscr, false);
        getch();
        endwin();
    }

    void insert_food()
    {
        while (true)
        {
            int tmpx = rand() % max_width + 1;
            int tmpy = rand() % max_height + 1;

            for (int i = 0; i < ((int)snake.size()); ++i)
            {
                if (snake[i].s_x == tmpx && snake[i].s_y == tmpy)
                {
                    continue;
                }
            }

            if (tmpx >= max_width - 2 || tmpy >= max_height - 2)
            {
                continue;
            }

            food.s_x = tmpx;
            food.s_y = tmpy;
            break;
        }
    }
};

int main(int argc, char **argv)
{
    SnakeGame s;
    return 0;
}
