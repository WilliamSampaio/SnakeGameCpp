#include <clocale>

#include "snakes_nest.hpp"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    SnakeGame s;
    s.start_game();
    return 0;
}
