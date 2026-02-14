#include <iostream>
#include <queue>

#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <api.hpp>
#include <floodfill.hpp>

void floodfill(int hori[16][17], int vert[17][16], int man[16][16], char *goal) {
    std::queue<Cell> q;

    // Initialize manhattan distances
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            man[y][x] = -1;
        }
    }

    // Set goal values to 0 and add them to queue
    if (std::strcmp("goal", goal) == 0) {
        for (int y = 7; y <= 8; y++) {
            for (int x = 7; x <= 8; x++) {
                man[y][x] = 0;
                q.push(make_cell(x, y));
            }
        }
    }
    else {
        man[0][0] = 0;
        q.push(make_cell(0, 0));
    }

    // Floodfill algorithm
    while (!q.empty()) {
        struct Cell cur_cell = q.front();
        q.pop();
        int x = cur_cell.x;
        int y = cur_cell.y;
        int new_val = man[y][x] + 1;

        // Set all blank (man = -1) + accessible (wall = 0) neighbors to cell val + 1
        // Top
        if (y + 1 <= 15 && man[y + 1][x] == -1 && vert[y + 1][x] == 0) {
            man[y + 1][x] = new_val;
            q.push(make_cell(x, y + 1));
        }
        // Bottom
        if (y - 1 >= 0 && man[y - 1][x] == -1 && vert[y][x] == 0) {
            man[y - 1][x] = new_val;
            q.push(make_cell(x, y - 1));
        }
        // Right
        if (x + 1 <= 15 && man[y][x + 1] == -1 && hori[y][x + 1] == 0) {
            man[y][x + 1] = new_val;
            q.push(make_cell(x + 1, y));
        }
        // Left
        if (x - 1 >= 0 && man[y][x - 1] == -1 && hori[y][x] == 0) {
            man[y][x - 1] = new_val;
            q.push(make_cell(x - 1, y));
        }
    }
}

void move(Position *position, int hori[16][17], int vert[17][16], int man[16][16], char *goal) {
    // Change goal depending on input
    while ((std::strcmp("goal", goal) == 0) ? is_not_center(position) : is_not_start(position)) {
        
    }
}

struct Cell make_cell(int x, int y) {
    struct Cell cell;
    cell.x = x;
    cell.y = y;
    return cell;
}

bool is_not_center(Position *position) {
    return !(position->x == 7 && position->y == 7) && !(position->x == 7 && position->y == 8)
           && !(position->x == 8 && position->y == 7) && !(position->x == 8 && position->y == 8);
}

bool is_not_start(Position *position) {
    return !(position->x == 0 && position->y == 0);
}