#include <iostream>
#include <queue>
#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <api.hpp>
#include <floodfill.hpp>

void floodfill(int hori[16][17], int vert[17][16], int man[16][16], char *goal)
{
    std::queue<Cell> q;

    // Initialize manhattan distances
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            man[y][x] = -1;
        }
    }

    // Set goal values to 0 and add them to queue
    if (std::strcmp("goal", goal) == 0)
    {
        for (int y = 7; y <= 8; y++)
        {
            for (int x = 7; x <= 8; x++)
            {
                man[y][x] = 0;
                q.push(make_cell(x, y));
            }
        }
    }
    else
    {
        man[0][0] = 0;
        q.push(make_cell(0, 0));
    }

    // Floodfill algorithm
    while (!q.empty())
    {
        struct Cell cur_cell = q.front();
        q.pop();
        int x = cur_cell.x;
        int y = cur_cell.y;
        int new_val = man[y][x] + 1;

        // Set all blank (man = -1) + accessible (wall = 0) neighbors to cell val + 1
        // Top
        if (y + 1 <= 15 && man[y + 1][x] == -1 && vert[y + 1][x] == 0)
        {
            man[y + 1][x] = new_val;
            q.push(make_cell(x, y + 1));
        }
        // Bottom
        if (y - 1 >= 0 && man[y - 1][x] == -1 && vert[y][x] == 0)
        {
            man[y - 1][x] = new_val;
            q.push(make_cell(x, y - 1));
        }
        // Right
        if (x + 1 <= 15 && man[y][x + 1] == -1 && hori[y][x + 1] == 0)
        {
            man[y][x + 1] = new_val;
            q.push(make_cell(x + 1, y));
        }
        // Left
        if (x - 1 >= 0 && man[y][x - 1] == -1 && hori[y][x] == 0)
        {
            man[y][x - 1] = new_val;
            q.push(make_cell(x - 1, y));
        }
    }
}

void move(Position *position, int hori[16][17], int vert[17][16], int man[16][16], char *goal)
{
    // Change goal depending on input
    while ((std::strcmp("goal", goal) == 0) ? is_not_center(position) : is_not_start(position))
    {
        mark_walls(position, hori, vert);
        floodfill(hori, vert, man, goal);

        char directions[] = {'n', 'e', 's', 'w'};
        int x = position->x;
        int y = position->y;
        int cur_dir = position->direction;

        // Need default values, setting them high so no risk of error
        int n = 1000;
        int e = 1000;
        int s = 1000;
        int w = 1000;

        // Check value isn't out of range and no blocking walls
        if (y + 1 <= 15 && vert[y + 1][x] == 0)
        {
            n = man[y + 1][x];
        }

        if (x + 1 <= 15 && hori[y][x + 1] == 0)
        {
            e = man[y][x + 1];
        }

        if (y - 1 >= 0 && vert[y][x] == 0)
        {
            s = man[y - 1][x];
        }

        if (x - 1 >= 0 && hori[y][x] == 0)
        {
            w = man[y][x - 1];
        }

        int dirs[] = {n, e, s, w};

        int dir = 0;
        int small_dist = n;

        for (int j = 0; j < 4; j++)
        {
            if (dirs[j] < small_dist)
            {
                small_dist = dirs[j];
                dir = j;
            }
        }

        int turn_amount = dir - cur_dir;

        while (turn_amount > 0)
        { // Turn right
            turnRight();
            changeDir(position, 'r');
            turn_amount--;
        }
        while (turn_amount < 0)
        { // Turn left
            turnLeft();
            changeDir(position, 'l');
            turn_amount++;
        }
        moveForward();
        movePositionForward(position);
    }
}

void mark_walls(struct Position *position, int hori[16][17], int vert[17][16])
{
    // Array wall sets
    switch (position->direction)
    {
    case 0: // north
        if (wallFront())
        {
            vert[position->y + 1][position->x] = 1;
        }
        if (wallRight())
        {
            hori[position->y][position->x + 1] = 1;
        }
        if (wallLeft())
        {
            hori[position->y][position->x] = 1;
        }
        break;
    case 1: // east
        if (wallFront())
        {
            hori[position->y][position->x + 1] = 1;
        }
        if (wallRight())
        {
            vert[position->y][position->x] = 1;
        }
        if (wallLeft())
        {
            vert[position->y + 1][position->x] = 1;
        }
        break;
    case 2: // south
        if (wallFront())
        {
            vert[position->y][position->x] = 1;
        }
        if (wallRight())
        {
            hori[position->y][position->x] = 1;
        }
        if (wallLeft())
        {
            hori[position->y][position->x + 1] = 1;
        }
        break;
    case 3: // west
        if (wallFront())
        {
            hori[position->y][position->x] = 1;
        }
        if (wallRight())
        {
            vert[position->y + 1][position->x] = 1;
        }
        if (wallLeft())
        {
            vert[position->y][position->x] = 1;
        }
        break;
    }
}

void changeDir(Position *position, char direction)
{
    if (direction == 'l')
    {
        position->direction--;
        if (position->direction < 0)
        {
            position->direction = 3;
        }
    }
    else
    {
        position->direction++;
        if (position->direction > 3)
        {
            position->direction = 0;
        }
    }
}

void movePositionForward(Position *position)
{
    switch (position->direction)
    {
    case 0:
        position->y++;
        break;
    case 1:
        position->x++;
        break;
    case 2:
        position->y--;
        break;
    case 3:
        position->x--;
        break;
    }
}

struct Cell make_cell(int x, int y)
{
    struct Cell cell;
    cell.x = x;
    cell.y = y;
    return cell;
}

bool is_not_center(Position *position)
{
    return !(position->x == 7 && position->y == 7) && !(position->x == 7 && position->y == 8) && !(position->x == 8 && position->y == 7) && !(position->x == 8 && position->y == 8);
}

bool is_not_start(Position *position)
{
    return !(position->x == 0 && position->y == 0);
}