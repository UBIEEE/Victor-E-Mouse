#pragma once

struct Cell
{
    int x, y;
};

bool is_not_center(Position *position);

bool is_not_start(Position *position);

struct Cell make_cell(int x, int y);

void floodfill(int hori[16][17], int vert[17][16], int man[16][16], char *goal);

void move(struct Position *position, int hori[16][17], int vert[17][16], int man[16][16], char *goal);

void mark_walls(struct Position *position, int hori[16][17], int ver[17][16]);

void set_walls(int hori[16][17], int vert[17][16]);