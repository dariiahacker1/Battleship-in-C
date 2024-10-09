#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <stdbool.h>

void start_screen();

int calculate_score(char field[10][10], int rows, int columns);

void initialization(int rows, int columns, char field[columns][rows]);

void print_fields(int rows, int columns, char player_field[columns][rows], char robot_field[columns][rows]);

void print_player(int rows, int columns, char player_field[columns][rows]);

void print_robot(int rows, int columns, char robot_field[columns][rows]);

void place_ships(int rows, int columns, char field[columns][rows], int x, int y, int type, char position);

bool validate_ship_placement(int rows, int columns, int x, int y, char position, int type, char field[columns][rows]);

void shot(int rows, int columns, char empty_field[columns][rows], int x, int y, char robot_field[columns][rows]);

void print_empty(int rows, int columns, char empty_field[columns][rows]);

int amount_of_ships(int type, int *n);

int check_win(int rows, int columns, char field[columns][rows]);

bool validate_shot(int rows, int columns, char robot_field[columns][rows], int x, int y);

bool check_coordinates_validity(int x, int y, int columns, int rows);

void player_ship_setting(int rows, int columns, char field[columns][rows], char player_field[columns][rows]);

void game(int rows, int columns, char field[columns][rows], char player_field[columns][rows],
          char robot_field[columns][rows], char empty_field[columns][rows]);

void robot_shot(int rows, int columns, char field[columns][rows], char player_field[columns][rows]);

void robot_ship_setting(int rows, int columns, char field[columns][rows], char robot_field[columns][rows]);

void additional_arsenal(int balance);

void preparing();

void player_winner();
void robot_winner();

#define COLOR_NICE 8
#define COLOR_AAA 20
#define COLOR_BBB 30
#define COLOR_CCC 40
#define COLOR_DDD 50
#define COLOR_EEE 60
#define COLOR_HE 100
#define COLOR_COW 66
#define COLOR_SHIP 65

#define COLOR_F 71
#define COLOR_SIX 72

#define COLOR_FFFF 73

#define COLOR_FF 74

#define COLOR_S 75

#define COLOR_T 76

#define COLOR_ROBO 77

int main()
{

    int rows = 10;
    int columns = 10;

    char player_field[columns][rows];
    char robot_field[columns][rows];
    char field[columns][rows];
    char empty_field[columns][rows];

    game(rows, columns, field, player_field, robot_field, empty_field);

    print_fields(rows, columns, player_field, empty_field);

    return 0;
}

void initialization(int rows, int columns, char field[columns][rows])
{

    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {

            field[x][y] = ' ';
        }
    }
}

bool check_coordinates_validity(int x, int y, int columns, int rows)
{
    return (x >= 0 && x < columns && y >= 0 && y < rows);
}

void print_fields(int rows, int columns, char player_field[columns][rows], char robot_field[columns][rows])
{

    start_color();

    init_color(COLOR_GREEN, 449, 512, 520);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    init_color(COLOR_YELLOW, 172, 699, 746);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    init_color(COLOR_MAGENTA, 996, 707, 129);
    init_pair(10, COLOR_MAGENTA, COLOR_BLACK);

    printw("\n");

    attron(COLOR_PAIR(8));
    printw("\t\t Your board: \t\t\t\t\t\t\t\t Robot's board:\n");

    attroff(COLOR_PAIR(8));

    printw("     ");

    attron(COLOR_PAIR(2));
    for (int i = 0; i < 10; i++)
    {
        printw("%d   ", i);
    }
    attroff(COLOR_PAIR(2));

    printw("\t\t\t\t     ");

    attron(COLOR_PAIR(2));
    for (int i = 0; i < 10; i++)
    {
        printw("%d   ", i);
    }
    attroff(COLOR_PAIR(2));

    printw("\n");

    attron(COLOR_PAIR(1));
    printw("   +");
    for (int x = 0; x < columns; x++)
    {

        printw("---+");
    }

    printw("\t\t\t\t");

    printw("   +");
    for (int x = 0; x < columns; x++)
    {
        printw("---+");
    }

    printw("\n");

    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));

    for (int y = 0; y < rows; y++)
    {

        char alpha = 'A' + y;

        attron(COLOR_PAIR(2));

        printw("%c", alpha);

        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        printw("  | ");

        attroff(COLOR_PAIR(1));

        for (int x = 0; x < columns; x++)
        {

            attron(COLOR_PAIR(10));
            printw("%c", player_field[x][y]);

            attroff(COLOR_PAIR(10));

            attron(COLOR_PAIR(1));
            printw(" | ");
        }
        attroff(COLOR_PAIR(1));
        printw("\t\t\t\t");

        attron(COLOR_PAIR(2));

        printw("%c", alpha);

        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        printw("  | ");

        attroff(COLOR_PAIR(1));

        for (int x = 0; x < columns; x++)
        {

            attron(COLOR_PAIR(10));
            printw("%c", robot_field[x][y]);
            attroff(COLOR_PAIR(10));

            attron(COLOR_PAIR(1));

            printw(" | ");
        }

        printw("\n");
        printw("   +");
        for (int y = 0; y < rows; y++)
        {

            printw("---+");
        }

        printw("\t\t\t\t");
        printw("   +");
        for (int y = 0; y < rows; y++)
        {
            printw("---+");
        }

        printw("\n");
    }

    printw("\n");

    attroff(COLOR_PAIR(1));
}

void place_ships(int rows, int columns, char field[columns][rows], int x, int y, int type, char position)
{
    int length = type;

    if (tolower(position) == 'v')
    {
        for (int i = 0; i < length; i++)
        {
            field[x][y + i] = 'X';
        }
    }
    else if (tolower(position) == 'h')
    {
        for (int i = 0; i < length; i++)
        {
            field[x + i][y] = 'X';
        }
    }
}

bool validate_ship_placement(int rows, int columns, int x, int y, char position, int type, char field[columns][rows])
{
    int length = type;

    position = tolower(position);

    if (position == 'v' && y + length > rows)
    {

        return false;
    }
    else if (position == 'h' && x + length > columns)
    {

        return false;
    }

    if (x >= columns || x < 0 || y < 0 || y >= rows)
    {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        if (position == 'v')
        {
            if (field[x][y + i] != ' ')
            {
                return false;
            }
        }
        else if (position == 'h')
        {
            if (field[x + i][y] != ' ')
            {
                return false;
            }
        }
    }

    for (int i = -1; i <= length; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newX = x + ((position == 'h') ? i : j);
            int newY = y + ((position == 'v') ? i : j);

            if (newX >= 0 && newX < columns && newY >= 0 && newY < rows)
            {
                if (field[newX][newY] != ' ')
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int check_win(int rows, int columns, char field[columns][rows])
{

    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {

            if (field[x][y] == 'X')
            {

                return 0;
            }
        }
    }
    return 1;
}

int amount_of_ships(int type, int *n)
{
    switch (type)
    {
    case 1:
        *n = 4;
        break;

    case 2:
        *n = 3;
        break;

    case 3:
        *n = 2;
        break;

    case 4:
        *n = 1;
        break;

    default:
        return 0;
    }

    return *n;
}

void print_player(int rows, int columns, char player_field[columns][rows])
{

    start_color();

    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);

    init_color(COLOR_YELLOW, 160, 836, 191);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

    init_color(COLOR_CYAN, 313, 508, 668);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    init_color(COLOR_BLUE, 996, 199, 0);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);

    move(0, 0);
    printw("\n");

    attron(COLOR_PAIR(13));
    printw("\t     IT'S TIME TO PREPARE \n");
    attroff(COLOR_PAIR(13));

    printw("     ");

    attron(COLOR_PAIR(5));
    for (int i = 0; i < 10; i++)
    {
        printw("%d   ", i);
    }
    attroff(COLOR_PAIR(5));
    printw("\n");

    attron(COLOR_PAIR(6));
    printw("   +");
    for (int x = 0; x < columns; x++)
    {

        printw("---+");
    }

    printw("\n");

    attroff(COLOR_PAIR(6));
    for (int y = 0; y < rows; y++)
    {

        char alpha = 'A' + y;
        attron(COLOR_PAIR(5));
        printw(" %c ", alpha);
        attroff(COLOR_PAIR(5));

        attron(COLOR_PAIR(6));
        printw("| ");
        attroff(COLOR_PAIR(6));

        for (int x = 0; x < columns; x++)
        {

            attron(COLOR_PAIR(13));
            printw("%c ", player_field[x][y]);
            attroff(COLOR_PAIR(13));

            attron(COLOR_PAIR(6));
            printw("| ");
        }

        printw("\n");
        printw("   +");
        for (int y = 0; y < rows; y++)
        {

            printw("---+");
        }

        attroff(COLOR_PAIR(6));

        printw("\n");
    }

    printw("\n");
}

void print_robot(int rows, int columns, char robot_field[columns][rows])
{

    printw("\n");

    printw("\t\t\t\t Robot's board: \n");

    printw("     ");
    for (int i = 0; i < 10; i++)
    {
        printw("%d   ", i);
    }

    printw("\n");

    printw("   +");
    for (int x = 0; x < columns; x++)
    {

        printw("---+");
    }

    printw("\n");

    for (int y = 0; y < rows; y++)
    {

        char alpha = 'A' + y;
        printw(" %c | ", alpha);

        for (int x = 0; x < columns; x++)
        {

            printw("%c | ", robot_field[x][y]);
        }

        printw("\n");
        printw("   +");
        for (int y = 0; y < rows; y++)
        {

            printw("---+");
        }

        printw("\n");
    }

    printw("\n");
}

void player_ship_setting(int rows, int columns, char field[columns][rows], char player_field[columns][rows])
{

    curs_set(1);
    start_color();

    init_color(COLOR_YELLOW, 160, 836, 191);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

    init_color(COLOR_NICE, 996, 199, 0);
    init_pair(13, COLOR_NICE, COLOR_BLACK);

    keypad(stdscr, TRUE); 
    raw();

    int x = 0, y = 0;

    char type_1[][1] = {
        {'X'},
        {'X'},
        {'X'},
        {'X'}};

    static int size1 = sizeof(type_1) / sizeof(type_1[0]);

    char type_2[][2] = {
        {'X', 'X'},
        {'X', 'X'},
        {'X', 'X'}};

    static int size2 = sizeof(type_2) / sizeof(type_2[0]);

    char type_3[][3] = {
        {'X', 'X', 'X'},
        {'X', 'X', 'X'}};

    static int size3 = sizeof(type_3) / sizeof(type_3[0]);

    char type_4[][4] = {
        {'X', 'X', 'X', 'X'}};

    static int size4 = sizeof(type_4) / sizeof(type_4[0]);

    print_player(rows, columns, player_field);

    int row_offset = 7;
    int col_offset = 55;

    attron(COLOR_PAIR(13));
    // Available type 1 ships:
    for (int i = 0; i < size1; i++)
    {
        mvprintw(row_offset, col_offset + i * 4, "%c", type_1[i][0]);
        printw("\t");
    }

    // Available type 2 ships:
    row_offset += 4;
    for (int i = 0; i < size2; i++)
    {
        mvprintw(row_offset, col_offset + i * 4, "%c", type_2[i][0]);
        mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_2[i][1]);
        printw("\t");
    }

    // Available type 3 ships:
    row_offset += 4;
    for (int i = 0; i < size3; i++)
    {
        mvprintw(row_offset, col_offset + i * 4, "%c", type_3[i][0]);
        mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_3[i][1]);
        mvprintw(row_offset, col_offset + i * 4 + 2, "%c", type_3[i][2]);
        printw("\t");
    }

    // Available type 4 ships:
    row_offset += 4;
    for (int i = 0; i < size4; i++)
    {
        mvprintw(row_offset, col_offset + i * 4, "%c", type_4[i][0]);
        mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_4[i][1]);
        mvprintw(row_offset, col_offset + i * 4 + 2, "%c", type_4[i][2]);
        mvprintw(row_offset, col_offset + i * 4 + 3, "%c", type_4[i][3]);
        printw("\t");
    }

    attroff(COLOR_PAIR(13));
    preparing();

    int type;

    do
    {

        move(38, 0);

        do
        {
            attron(COLOR_PAIR(6));

            mvprintw(24, 63, "Choose the type of ship (1-4): ");
            scanw("%d", &type);

            attroff(COLOR_PAIR(6));
        } while (type > 4 || type < 1);

        move(25, 4);

        attron(COLOR_PAIR(13));
        printw("  Use arrow keys to select coordinates. \n"
               "           Press ENTER to place ship.");
        attroff(COLOR_PAIR(13));

        refresh();

        curs_set(0);
        echo();

        int ch;

        int initial_y = y + 4;
        int initial_x = x * 4 + 5;
        int fy = initial_y;
        int fx = initial_x;
        mvaddch(fy, fx, '^');
        refresh();


        while ((ch = getch()) != 10)
        {

            int prev_fy = fy;
            int prev_fx = fx;

            mvprintw(prev_fy, prev_fx, " ");

            switch (ch)
            {
            case KEY_UP:
                if (y > 0)
                {
                    y--;
                    fy -= 2;
                }
                break;
            case KEY_DOWN:
                if (y < rows - 1)
                {
                    y++;
                    fy += 2;
                }
                break;
            case KEY_LEFT:
                if (x > 0)
                {
                    x--;
                    fx -= 4;
                }
                break;
            case KEY_RIGHT:
                if (x < columns - 1)
                {
                    x++;
                    fx += 4;
                }
                break;

                mvaddch(fy, fx, '^');
                refresh();
            }

            move(initial_y, initial_x);
            mvaddch(fy, fx, '^');

            refresh();
        }

        curs_set(2);

        char position;

        move(28, 0);

        if (type == 2 || type == 3 || type == 4)
        {
            printw("Enter direction (h - horizontal, v - vertical): ");
            refresh();

            scanw(" %c", &position);
            position = tolower(position);
        }
        else
        {

            position = 'h';
        }

        if (!validate_ship_placement(rows, columns, x, y, position, type, player_field))
        {
            printw("\nINVALID PLACEMENT\n");

            y = -1;
        }
        else
        {
            switch (type)
            {
            case 1:
                if (size1 > 0)
                {
                    place_ships(rows, columns, player_field, x, y, type, position);
                    y = -1;
                    size1--;
                }
                else
                {
                    printw("\nNO MORE SHIPS OF TYPE 1 LEFT\n");
                }
                break;
            case 2:
                if (size2 > 0)
                {
                    place_ships(rows, columns, player_field, x, y, type, position);
                    y = -1;
                    size2--;
                }
                else
                {
                    printw("\nNO MORE SHIPS OF TYPE 2 LEFT\n");
                }
                break;
            case 3:
                if (size3 > 0)
                {
                    place_ships(rows, columns, player_field, x, y, type, position);
                    y = -1;
                    size3--;
                }
                else
                {
                    printw("\nNO MORE SHIPS OF TYPE 3 LEFT\n");
                }
                break;
            case 4:
                if (size4 > 0)
                {
                    place_ships(rows, columns, player_field, x, y, type, position);
                    y = -1;
                    size4--;
                }
                else
                {
                    printw("\nNO MORE SHIPS OF TYPE 4 LEFT\n");
                }
                break;
            default:
                break;
            }
        }

        clear();

        print_player(rows, columns, player_field);

        int n = 0;
        amount_of_ships(type, &n);

        int row_offset = 7;
        int col_offset = 55;

        attron(COLOR_PAIR(13));
        // Available type 1 ships:
        for (int i = 0; i < size1; i++)
        {
            mvprintw(row_offset, col_offset + i * 4, "%c", type_1[i][0]);
            printw("\t");
        }

        // Available type 2 ships:
        row_offset += 4;
        for (int i = 0; i < size2; i++)
        {
            mvprintw(row_offset, col_offset + i * 4, "%c", type_2[i][0]);
            mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_2[i][1]);
            printw("\t");
        }

        // Available type 3 ships:
        row_offset += 4;
        for (int i = 0; i < size3; i++)
        {
            mvprintw(row_offset, col_offset + i * 4, "%c", type_3[i][0]);
            mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_3[i][1]);
            mvprintw(row_offset, col_offset + i * 4 + 2, "%c", type_3[i][2]);
            printw("\t");
        }

        // Available type 4 ships:
        row_offset += 4;
        for (int i = 0; i < size4; i++)
        {
            mvprintw(row_offset, col_offset + i * 4, "%c", type_4[i][0]);
            mvprintw(row_offset, col_offset + i * 4 + 1, "%c", type_4[i][1]);
            mvprintw(row_offset, col_offset + i * 4 + 2, "%c", type_4[i][2]);
            mvprintw(row_offset, col_offset + i * 4 + 3, "%c", type_4[i][3]);
            printw("\t");
        }
        attroff(COLOR_PAIR(13));

        preparing();

        refresh();

        if (size1 <= 0 && size2 <= 0 && size3 <= 0 && size4 <= 0)
        {

            printw("GET READY FOR FIGHT\n\n");

            clear();
            return;
        }

    } while (1);

    noraw();
    noecho();
    return;
}

void robot_ship_setting(int rows, int columns, char field[columns][rows], char robot_field[columns][rows])
{
    srand(time(NULL));

    int length[10] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};

    int ships_placed = 0;

    while (ships_placed < 10)
    {
        int rob_x = rand() % columns;
        int rob_y = rand() % rows;
        char position = (rand() % 2 == 1) ? 'h' : 'v';

        if (validate_ship_placement(rows, columns, rob_x, rob_y, position, length[ships_placed], robot_field))
        {
            place_ships(rows, columns, robot_field, rob_x, rob_y, length[ships_placed], position);
            ships_placed++;
        }
    }
}

bool validate_shot(int rows, int columns, char robot_field[columns][rows], int x, int y)
{

    if (x > columns || x < 0 || y < 0 || y > rows)
    {

        return false;
    }

    return true;
}

void print_empty(int rows, int columns, char empty_field[columns][rows])
{

    printw("\n");

    printw("\t\t\t\t Robot's board: \n");

    printw("     ");
    for (int i = 0; i < 10; i++)
    {
        printw("%d   ", i);
    }

    printw("\n");

    printw("   +");
    for (int x = 0; x < columns; x++)
    {

        printw("---+");
    }

    printw("\n");

    for (int y = 0; y < rows; y++)
    {

        char alpha = 'A' + y;
        printw(" %c | ", alpha);

        for (int x = 0; x < columns; x++)
        {

            printw("%c | ", empty_field[x][y]);
        }

        printw("\n");
        printw("   +");
        for (int y = 0; y < rows; y++)
        {

            printw("---+");
        }

        printw("\n");
    }

    printw("\n");
}

void shot(int rows, int columns, char empty_field[columns][rows], int x, int y, char robot_field[columns][rows])
{

    if (empty_field[x][y] == 'X' && robot_field[x][y] == '*')
    {

        return;
    }
    else if (robot_field[x][y] == 'X')
    {

        empty_field[x][y] = 'X';
        robot_field[x][y] = '*';
    }
    else
    {

        empty_field[x][y] = '.';
        robot_field[x][y] = '.';
    }
}

void robot_shot(int rows, int columns, char field[columns][rows], char player_field[columns][rows])
{
    static int last_x = -1;
    static int last_y = -1;
    static int direction = 0;
    static int hit = 0;

    int x, y;

    if (hit == 1)
    {
        int new_x = last_x + (direction == 0 ? -1 : direction == 2 ? 1
                                                                   : 0);
        int new_y = last_y + (direction == 1 ? 1 : direction == 3 ? -1
                                                                  : 0);

        if (new_x >= 0 && new_x < columns && new_y >= 0 && new_y < rows &&
            player_field[new_x][new_y] != '*' && player_field[new_x][new_y] != '.')
        {

            if (player_field[new_x][new_y] == 'X')
            {
                player_field[new_x][new_y] = '*';
                last_x = new_x;
                last_y = new_y;
                hit = 1;
                return;
            }
            else
            {
                player_field[new_x][new_y] = '.';
                direction = (direction + 1) % 4;
                hit = 0;
                return;
            }
        }
        else
        {
            direction = (direction + 1) % 4;
        }
    }

    do
    {
        x = rand() % columns;
        y = rand() % rows;
    } while (player_field[x][y] == '.' || player_field[x][y] == '*');

    if (player_field[x][y] == 'X')
    {
        player_field[x][y] = '*';
        last_x = x;
        last_y = y;
        hit = 1;
    }
    else
    {
        player_field[x][y] = '.';
    }
}

void preparing()
{

    start_color();

    init_color(COLOR_GREEN, 957, 668, 0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 

    init_color(COLOR_BLUE, 0, 668, 523);
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 

    init_color(COLOR_MAGENTA, 184, 441, 957); // blue
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

    init_color(COLOR_RED, 355, 56, 957); // fiolet
    init_pair(4, COLOR_RED, COLOR_BLACK);

    init_color(COLOR_CYAN, 313, 508, 668);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    init_color(COLOR_YELLOW, 160, 836, 191);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

    int x = 50;
    int y = 5;

    attron(COLOR_PAIR(6));
    mvprintw(3, 69, "AVAILABLE SHIPS");
    attroff(COLOR_PAIR(6));

    move(y, x);

    attron(COLOR_PAIR(5));
    for (int j = 0; j < 13; j++)
    {
        printw("\\---");
    }
    printw("\\");
    attroff(COLOR_PAIR(5));


    x = 51;
    y = 9;

    attron(COLOR_PAIR(5));
    for (int i = 0; i < 3; i++)
    {
        move(y, x);

        for (int j = 0; j < 17; j++)
        {
            printw("---");
        }

        y += 4;
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(1));
    move(6, 75);
    printw("     __/\\__\n");

    move(7, 75);
    printw("  ~~~\\____/~~~~~\n");
    move(8, 75);
    printw("    ~  ~~~   ~ \n");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    move(10, 75);
    printw("       |\\\n");
    move(11, 75);
    printw("     _/]_\\_\n");
    move(12, 75);
    printw("  ~~~\"~~~~~^~~\n");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    move(14, 69);
    printw("         _____/______\n");
    move(15, 69);
    printw("   _____/____\\_______\\___\n");
    move(16.1, 69);
    printw("   \\____________________/\n");

    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    move(18, 64);
    printw("               --\"--------         \n");
    move(19, 64);
    printw("     .____...../ /__| |__\\ \\______,      \n");
    move(20, 64);
    printw("      \\__________________________/\n");
    attroff(COLOR_PAIR(4));

    move(22, 50);

    attron(COLOR_PAIR(5));
    for (int j = 0; j < 13; j++)
    {
        printw("/---");
    }
    printw("/");

    attroff(COLOR_PAIR(5));

    move(25, 7);
}

int calculate_score(char field[10][10], int rows, int columns)
{
    int score = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (field[i][j] == '*')
            {
                score++;
            }
        }
    }
    return score;
}

void additional_arsenal(int balance)
{

    start_color();

    init_color(COLOR_RED, 492, 719, 422);
    init_pair(7, COLOR_RED, COLOR_BLACK);

    init_color(COLOR_BLUE, 996, 199, 0);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);

    init_color(COLOR_WHITE, 473, 449, 727);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    int k = 120;

    attron(COLOR_PAIR(9));
    mvprintw(1, k - 1, "         PRESS Q1");
    attroff(COLOR_PAIR(9));

    attron(COLOR_PAIR(7));
    mvprintw(2, k - 1, " +----------------------+");

    mvprintw(3, k - 1, " |      Game Store      |");

    mvprintw(4, k - 1, " +----------------------+");
    if (balance == 100)
    {
        mvprintw(5, k - 1, " | Balance: %d         |", balance);
    }
    else if (balance < 100)
    {
        mvprintw(5, k - 1, " | Balance: %d          |", balance);
    }
    else if (balance == 0)
    {
        mvprintw(5, k - 1, " | Balance: %d           |", balance);
    }

    mvprintw(6, k - 1, " |----------------------|");

    mvprintw(7, k - 1, " | 1. Bomber:     ");

    attron(COLOR_PAIR(8));
    mvprintw(7, k + 17, "30    ");
    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(7));

    mvprintw(7, k + 23, "|");

    mvprintw(8, k - 1, " |             __|__    |");
    mvprintw(9, k - 1, " |   __|__  *---o0o---* |");
    mvprintw(10, k, "|*---o0o---*           |");
    mvprintw(11, k, "|----------------------|");
    mvprintw(12, k, "| 2. Mines:      ");

    attron(COLOR_PAIR(8));
    mvprintw(12, k + 17, "15    ");
    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(7));
    mvprintw(12, k + 23, "|");

    mvprintw(13, k, "|  _____________       |");
    mvprintw(14, k, "| |_____________|~~~~X |");
    mvprintw(15, k, "|                      |");
    mvprintw(16, k, "|----------------------|");
    mvprintw(17, k, "| 3. Rocket:     ");
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(8));
    mvprintw(17, k + 17, "20    ");

    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(7));
    mvprintw(17, k + 23, "|");

    mvprintw(18, k, "|       /\\             |");
    mvprintw(19, k, "|      (  )            |");
    mvprintw(20, k, "|      (  )            |");
    mvprintw(21, k, "|     /|/\\|\\           |");
    mvprintw(22, k, "|    /_||||_\\          |");
    mvprintw(23, k, "+----------------------+");
    attroff(COLOR_PAIR(7));

    refresh();
}

void start_screen()
{

    initscr();

    curs_set(0);

    start_color();

    init_color(COLOR_GREEN, 183, 957, 113);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    init_color(COLOR_BLUE, 0, 488, 957);

    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    init_color(COLOR_MAGENTA, 957, 539, 172);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

    int y = 10;
    int x = 30;

    attron(COLOR_PAIR(1));

    mvprintw(y++, x, "          ");
    mvprintw(y++, x, "           o");
    mvprintw(y++, x, "           |");
    mvprintw(y++, x, "         ,'~'.");
    mvprintw(y++, x, "        /     \\");
    mvprintw(y++, x, "       |   ____|_");
    mvprintw(y++, x, "       |  '___,,_'         .----------------.");
    mvprintw(y++, x, "       |  ||(o |o)|       ( I AM THE WINNER! )");
    mvprintw(y++, x, "       |   -------         ,----------------'");
    mvprintw(y++, x, "       |  _____|         -'");
    mvprintw(y++, x, "       \\  '####,");
    mvprintw(y++, x, "        -------");
    mvprintw(y++, x, "      /________\\");
    mvprintw(y++, x, "    (  )        |)");
    mvprintw(y++, x, "    '_ ' ,------|\\        /|");
    mvprintw(y++, x, "   /_ /  |      |\\_\\     / |");
    mvprintw(y++, x, "  /_ /|  |     o| _\\    /__|__");
    mvprintw(y++, x, " /_ / |  |      |\\ _\\___\\____/");
    mvprintw(y++, x, "(  (  |  |      | (_,_,_,____/");
    mvprintw(y++, x, " \\ _\\ |   ------|        ");
    mvprintw(y++, x, "  \\ _\\|_________|");
    mvprintw(y++, x, "   \\ _\\ \\__\\\\__\\");
    mvprintw(y++, x, "   |__| |__||__|");
    mvprintw(y++, x, "  /__/  |__||__|");
    mvprintw(y++, x, "        |__||__|");
    mvprintw(y++, x, "        |__||__|");
    mvprintw(y++, x, "        /__)/__/");
    mvprintw(y++, x, "       /__//__/");
    mvprintw(y++, x, "      /__//__/");
    mvprintw(y++, x, "     /__//__/.");
    mvprintw(y++, x, "   .'    '.   '.");
    mvprintw(y++, x, "  (________)____)");

    attroff(COLOR_PAIR(1));

    x = 100;
    y = 12;

    attron(COLOR_PAIR(2));

    mvprintw(y++, x, "           YOUR PHOTO           ");
    mvprintw(y++, x, "+------------------------------+");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "|                              |");
    mvprintw(y++, x, "+------------------------------+");

    attroff(COLOR_PAIR(2));

    x = 70;
    y = 40;

    while (1)
    {

        mvprintw(y + 6, x, "                     ");
        mvprintw(y + 5, x, "                     ");
        mvprintw(y + 4, x, "                     ");
        mvprintw(y + 3, x, "                     ");
        mvprintw(y + 2, x, "                     ");
        mvprintw(y + 1, x, "                     ");

        attron(COLOR_PAIR(3));

        mvprintw(y, x, "___   _____________");
        mvprintw(y + 1, x, "\\   \\ /   /   _____/");
        mvprintw(y + 2, x, " \\   Y   /\\_____  \\");
        mvprintw(y + 3, x, "  \\     / /        \\");
        mvprintw(y + 4, x, "   \\___/ /_______  /");
        mvprintw(y + 5, x, "                 \\/");

        attroff(COLOR_PAIR(3));

        refresh();

        y--;

        if (y < 20)
        {
            break;
        }

        napms(50);
    }

    y = 0;
    x = 18;

    attron(COLOR_PAIR(3));
    mvprintw(y++, x,
             "                                                                                                                   _____ ");
    mvprintw(y++, x,
             " _____ _____ _____ ____  __ __    _____ _____ _____    _____ _____ _____ _____ __    _____ _____ _____ _____ _____|___  |");
    mvprintw(y++, x,
             "| __  |   __|  _  |    \\|  |  |  |   __|     | __  |  | __  |  _  |_   _|_   _|  |  |   __|   __|  |  |     |  _  | |  _|");
    mvprintw(y++, x,
             "|    -|   __|     |  |  |_   _|  |   __|  |  |    -|  | __ -|     | | |   | | |  |__|   __|__   |     |-   -|   __| |_|  ");
    mvprintw(y++, x,
             "|__|__|_____|__|__|____/  |_|    |__|  |_____|__|__|  |_____|__|__| |_|   |_| |_____|_____|_____|__|__|_____|__|    |_|  ");
    mvprintw(y++, x, "  \n");
    attron(COLOR_PAIR(2));
    mvprintw(y++, x, "    PRESS ENTER ");
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));

    refresh();


    getch();
    clear();
    endwin();
}

void player_winner()
{

    initscr();

    start_color();

    init_color(COLOR_AAA, 496, 668, 828);
    init_pair(20, COLOR_AAA, COLOR_BLACK);

    init_color(COLOR_BBB, 332, 539, 828);
    init_pair(30, COLOR_BBB, COLOR_BLACK);

    init_color(COLOR_CCC, 238, 406, 828);
    init_pair(40, COLOR_CCC, COLOR_BLACK);

    init_color(COLOR_DDD, 164, 242, 828);
    init_pair(50, COLOR_DDD, COLOR_BLACK);

    init_color(COLOR_EEE, 238, 23, 828);
    init_pair(60, COLOR_EEE, COLOR_BLACK);

    init_color(COLOR_HE, 996, 121, 676);
    init_pair(100, COLOR_HE, COLOR_BLACK);

    init_color(COLOR_COW, 512, 359, 836);
    init_pair(66, COLOR_COW, COLOR_BLACK);

    init_color(COLOR_SHIP, 668, 242, 836);
    init_pair(65, COLOR_SHIP, COLOR_BLACK);

    curs_set(0);

    int y = 30;
    int x = 88;

    attron(COLOR_PAIR(66));

    mvprintw(y++, x, "           .         .");
    mvprintw(y++, x, "           \\' .____.'/");
    mvprintw(y++, x, "          __'-.  .-'__                         .--.");
    mvprintw(y++, x, "          '_i:'oo':i_'---...____...----i\"\"\"-.-'.-\"\\");
    mvprintw(y++, x, "            /._  _\\.       :       /   '._   ;/    ;'-._");
    mvprintw(y++, x, "           (  o  o  )       '-.__.'       '. '.     '-.\"");
    mvprintw(y++, x, "            '-.__.-' _.--.                 '-.:");
    mvprintw(y++, x, "             : '-'  /     ;   _..--,  /       ;");
    mvprintw(y++, x, "             :      '-._.-'  ;     ; :       :");
    mvprintw(y++, x, "              :  `      .'    '-._.' :      /");
    mvprintw(y++, x, "               \\  :    /    ____....--\\    :");
    mvprintw(y++, x, "                '._\\  :\"\"\"\"    '.     !.   :");
    mvprintw(y++, x, "                 : |: :           'www'| \\ '|");
    mvprintw(y++, x, "                 | || |              : |  | :");
    mvprintw(y++, x, "                 | || |             .' !  | |");
    mvprintw(y++, x, "                .' !| |            /__I   | |");
    mvprintw(y++, x, "               /__I.' !                  .' !");
    mvprintw(y++, x, "                  /__I                  /__I ");

    attroff(COLOR_PAIR(66));

    y = 18;
    x = 0;

    attron(COLOR_PAIR(65));
    mvprintw(y++, x, "                    |");
    mvprintw(y++, x, "                    |");
    mvprintw(y++, x, "           |        |");
    mvprintw(y++, x, "         |-|-|      |");
    mvprintw(y++, x, "           |        |");
    mvprintw(y++, x, "           | {O}    |");
    mvprintw(y++, x, "           '--|     |");
    mvprintw(y++, x, "             .|]_   |");
    mvprintw(y++, x, "       _.-=.' |     |");
    mvprintw(y++, x, "      |    |  |]_   |");
    mvprintw(y++, x, "      |_.-='  |   __|__");
    mvprintw(y++, x, "       _.-='  |\\   /|\\");
    mvprintw(y++, x, "      |    |  |-'-'-'-'-.");
    mvprintw(y++, x, "      |_.-='  '========='");
    mvprintw(y++, x, "           `   |     |");
    mvprintw(y++, x, "            `. |    / \\");
    mvprintw(y++, x, "              ||   /   \\____.--=''''==--.._");
    mvprintw(y++, x, "              ||_.'--=='    |__  __  __  _.'");
    mvprintw(y++, x, "              ||  |    |    |\\ ||  ||  || |");
    mvprintw(y++, x, " ____         ||__|____|____| \\||__||__||_/");
    mvprintw(y++, x, "|    |______  |===.---. .---.========''''=-._ |");
    mvprintw(y++, x, "|    ||     |\\| |||   | |   |      '===' ||  \\|");
    mvprintw(y++, x, "|-.._||_____|_\\___'---' '---'______....---===''======//=//////========|");
    mvprintw(y++, x, "|--------------\\------------------/-----------------//-//////---------/");
    mvprintw(y++, x, "|               \\                /                 // //////         /");
    mvprintw(y++, x, "|                \\______________/                 // //////         /");
    mvprintw(y++, x, "|                                        _____===//=//////=========/");
    mvprintw(y++, x, "|=================================================================/");
    mvprintw(y++, x, "'----------------------------------------------------------------`");
    attroff(COLOR_PAIR(65));

    x = 5;
    y = 2;

    attron(COLOR_PAIR(20));
    mvprintw(y++, x, "_________  ________    _______    __________________    ____________________ ___.____       ________________.___________    _______    _________");
    attroff(COLOR_PAIR(20));

    attron(COLOR_PAIR(30));
    mvprintw(y++, x, "\\_   ___ \\ \\_____  \\   \\      \\  /  _____/\\______   \\  /  _  \\__    ___/    |   \\    |     /  _  \\__    ___/|   \\_____  \\   \\      \\  /   _____/");
    attroff(COLOR_PAIR(30));

    attron(COLOR_PAIR(40));
    mvprintw(y++, x, "/    \\  \\/  /   |   \\  /   |   \\/   \\  ___ |       _/ /  /_\\  \\|    |  |    |   /    |    /  /_\\  \\|    |   |   |/   |   \\  /   |   \\ \\_____  \\");
    attroff(COLOR_PAIR(40));

    attron(COLOR_PAIR(50));
    mvprintw(y++, x, "\\     \\____/    |    \\/    |    \\    \\_\\  \\|    |   \\/    |    \\    |  |    |  /|    |___/    |    \\    |   |   /    |    \\/    |    \\/        \\");
    attroff(COLOR_PAIR(50));

    attron(COLOR_PAIR(60));
    mvprintw(y++, x, " \\______  /\\_______  /\\____|__  /\\______  /|____|_  /\\____|__  /____|  |______/ |_______ \\____|__  /____|   |___\\_______  /\\____|__  /_______  /");
    mvprintw(y++, x, "        \\/         \\/         \\/        \\/        \\/         \\/                         \\/       \\/                     \\/         \\/        \\/");
    attroff(COLOR_PAIR(60));

    x = 46;
    y = 15;

    int times = 0;
    while (1)
    {

        attron(COLOR_PAIR(100));
        mvprintw(y, x, "  _   _         _   _         _   _         _   _ ");
        mvprintw(y + 1, x, "/   V   \\     /   V   \\     /   V   \\     /   V   \\");
        mvprintw(y + 2, x, "|       |     |       |     |       |     |       |");
        mvprintw(y + 3, x, " \\     /       \\     /       \\     /       \\     / ");
        mvprintw(y + 4, x, "   \\ /           \\ /           \\ /           \\ /  ");
        mvprintw(y + 5, x, "    *             *             *             *    ");
        attroff(COLOR_PAIR(100));

        refresh();
        napms(500);

        mvprintw(y, x, "                                                               ");
        mvprintw(y + 1, x, "                                                            ");
        mvprintw(y + 2, x, "                                                                         ");
        mvprintw(y + 3, x, "                                                                     ");
        mvprintw(y + 4, x, "                                                                     ");
        mvprintw(y + 5, x, "                                                                     ");

        refresh();
        napms(500);

        times++;

        if (times > 5)
        {
            break;
        }
    }

    attron(COLOR_PAIR(100));
    mvprintw(y, x, "  _   _         _   _         _   _         _   _ ");
    mvprintw(y + 1, x, "/   V   \\     /   V   \\     /   V   \\     /   V   \\");
    mvprintw(y + 2, x, "|       |     |       |     |       |     |       |");
    mvprintw(y + 3, x, " \\     /       \\     /       \\     /       \\     / ");
    mvprintw(y + 4, x, "   \\ /           \\ /           \\ /           \\ /  ");
    mvprintw(y + 5, x, "    *             *             *             *    ");
    attroff(COLOR_PAIR(100));

    refresh();

    getch();
    clear();
    endwin();
}

void robot_winner()
{

    initscr();

    start_color();

    init_color(COLOR_F, 434, 836, 617);
    init_pair(71, COLOR_F, COLOR_BLACK);

    init_color(COLOR_S, 270, 836, 550);
    init_pair(72, COLOR_S, COLOR_BLACK);

    init_color(COLOR_T, 140, 836, 465);
    init_pair(73, COLOR_T, COLOR_BLACK);

    init_color(COLOR_FF, 82, 836, 609);
    init_pair(74, COLOR_FF, COLOR_BLACK);

    init_color(COLOR_FFFF, 0, 836, 711);
    init_pair(75, COLOR_FFFF, COLOR_BLACK);

    init_color(COLOR_SIX, 74, 836, 773);
    init_pair(76, COLOR_SIX, COLOR_BLACK);

    init_color(COLOR_ROBO, 353, 543, 836);
    init_pair(77, COLOR_ROBO, COLOR_BLACK);

    curs_set(0);

    int x = 41;
    int y = 2;

    attron(COLOR_PAIR(COLOR_F));
    mvprintw(y, x, "_____.___.________   ____ ___  .____    ________    ____________________");
    attroff(COLOR_PAIR(COLOR_F));

    attron(COLOR_PAIR(COLOR_S));
    mvprintw(y + 1, x, "\\__  |   |\\_____  \\ |    |   \\ |    |   \\_____  \\  /   _____/\\_   _____/");
    attroff(COLOR_PAIR(COLOR_S));

    attron(COLOR_PAIR(COLOR_T));
    mvprintw(y + 2, x, " /   |   | /   |   \\|    |   / |    |    /   |   \\ \\_____  \\  |    __)_");
    attroff(COLOR_PAIR(COLOR_T));

    attron(COLOR_PAIR(COLOR_FF));
    mvprintw(y + 3, x, " \\____   |/    |    \\    |  /  |    |___/    |    \\/        \\ |        \\");
    attroff(COLOR_PAIR(COLOR_FF));

    attron(COLOR_PAIR(COLOR_FFFF));
    mvprintw(y + 4, x, " / ______|\\_______  /______/   |_______ \\_______  /_______  //_______  /");
    attroff(COLOR_PAIR(COLOR_FFFF));

    attron(COLOR_PAIR(COLOR_SIX));
    mvprintw(y + 5, x, " \\/               \\/                   \\/       \\/        \\/         \\/");
    attroff(COLOR_PAIR(COLOR_SIX));

    x = 20;
    y = 10;

    attron(COLOR_PAIR(77));
    mvprintw(y++, x, "          ");
    mvprintw(y++, x, "           o");
    mvprintw(y++, x, "           |");
    mvprintw(y++, x, "         ,'~'.");
    mvprintw(y++, x, "        /     \\");
    mvprintw(y++, x, "       |   ____|_");
    mvprintw(y++, x, "       |  '___,,_'         .----------------.");
    mvprintw(y++, x, "       |  ||(o |o)|       ( YOU ARE A LOSER! )");
    mvprintw(y++, x, "       |   -------         ,----------------'");
    mvprintw(y++, x, "       |  _____|         -'");
    mvprintw(y++, x, "       \\  '####,");
    mvprintw(y++, x, "        -------");
    mvprintw(y++, x, "      /________\\");
    mvprintw(y++, x, "    (  )        |)");
    mvprintw(y++, x, "    '_ ' ,------|\\        /|");
    mvprintw(y++, x, "   /_ /  |      |\\_\\     / |");
    mvprintw(y++, x, "  /_ /|  |     o| _\\    /__|__");
    mvprintw(y++, x, " /_ / |  |      |\\ _\\___\\____/");
    mvprintw(y++, x, "(  (  |  |      | (_,_,_,____/");
    mvprintw(y++, x, " \\ _\\ |   ------|        ");
    mvprintw(y++, x, "  \\ _\\|_________|");
    mvprintw(y++, x, "   \\ _\\ \\__\\\\__\\");
    mvprintw(y++, x, "   |__| |__||__|");
    mvprintw(y++, x, "  /__/  |__||__|");
    mvprintw(y++, x, "        |__||__|");
    mvprintw(y++, x, "        |__||__|");
    mvprintw(y++, x, "        /__)/__/");
    mvprintw(y++, x, "       /__//__/");
    mvprintw(y++, x, "      /__//__/");
    mvprintw(y++, x, "     /__//__/.");
    mvprintw(y++, x, "   .'    '.   '.");
    mvprintw(y++, x, "  (________)____)");

    attroff(COLOR_PAIR(77));

    y = 23;
    x = 70;

    int times = 0;
    while (1)
    {

        mvprintw(y, x, "                                       __  o");
        mvprintw(y + 1, x, "                                      /  |/");
        mvprintw(y + 2, x, "                                    _/___|___________");
        mvprintw(y + 3, x, "                                   /  _______      __\\");
        mvprintw(y + 4, x, "   _______                        /  /_o_||__|    |");
        mvprintw(y + 5, x, "    \\_\\_\\_\\______________________/___             |");
        mvprintw(y + 6, x, "             \\                       \\____________|______________");
        mvprintw(y + 7, x, "              \\     ||                                           |");
        mvprintw(y + 8, x, "               \\  +_||_+       () () ()                      ____|");
        mvprintw(y + 9, x, "                \\                                             |");
        mvprintw(y + 10, x, "                 \\     _  ,,          _                      /");
        mvprintw(y + 11, x, "  ^^^^^^^^^^^^^^^^ \\_.=\" )\"  \"-.____,' \";__________________ /_^^^^^^^^");
        mvprintw(y + 12, x, "    ^^^^  ^^^^                                              \\__|==% ^^");
        mvprintw(y + 13, x, "  ^^         ^^^^^^^^       ^^^^ ^^^ ^^^^^      ^^^^^^^^^^ ^      ^^^^");
        mvprintw(y + 14, x, "^^^   ^^^^          ^^^^^^^^^^^^          ^^^^     ^^       ^^^^^");

        refresh();
        napms(500);

        mvprintw(y, x, "                                                                                                 ");
        mvprintw(y + 1, x, "                                                                                      ");
        mvprintw(y + 2, x, "                                                                                         ");
        mvprintw(y + 3, x, "                                                                                      ");
        mvprintw(y + 4, x, "                                                                                   ");
        mvprintw(y + 5, x, "                                                                                                     ");
        mvprintw(y + 6, x, "                                                                                            ");
        mvprintw(y + 7, x, "                                                                                                           ");
        mvprintw(y + 8, x, "                                                                                                             ");
        mvprintw(y + 9, x, "                                                                                                         ");
        mvprintw(y + 10, x, "                                                                                                               ");
        mvprintw(y + 11, x, "                                                                                                 ");
        mvprintw(y + 12, x, "                                                                                                   ");
        mvprintw(y + 13, x, "                                                                                                   ");
        mvprintw(y + 14, x, "                                                                                                 ");

        refresh();
        napms(500);

        times++;

        if (times > 5)
        {
            break;
        }
    }

    mvprintw(y, x, "                                       __  o");
    mvprintw(y + 1, x, "                                      /  |/");
    mvprintw(y + 2, x, "                                    _/___|___________");
    mvprintw(y + 3, x, "                                   /  _______      __\\");
    mvprintw(y + 4, x, "   _______                        /  /_o_||__|    |");
    mvprintw(y + 5, x, "    \\_\\_\\_\\______________________/___             |");
    mvprintw(y + 6, x, "             \\                       \\____________|______________");
    mvprintw(y + 7, x, "              \\     ||                                           |");
    mvprintw(y + 8, x, "               \\  +_||_+       () () ()                      ____|");
    mvprintw(y + 9, x, "                \\                                             |");
    mvprintw(y + 10, x, "                 \\     _  ,,          _                      /");
    mvprintw(y + 11, x, "  ^^^^^^^^^^^^^^^^ \\_.=\" )\"  \"-.____,' \";__________________ /_^^^^^^^^");
    mvprintw(y + 12, x, "    ^^^^  ^^^^                                              \\__|==% ^^");
    mvprintw(y + 13, x, "  ^^         ^^^^^^^^       ^^^^ ^^^ ^^^^^      ^^^^^^^^^^ ^      ^^^^");
    mvprintw(y + 14, x, "^^^   ^^^^          ^^^^^^^^^^^^          ^^^^     ^^       ^^^^^");

    refresh();

    getch();
    clear();
    endwin();
}

void game(int rows, int columns, char field[columns][rows], char player_field[columns][rows],
          char robot_field[columns][rows], char empty_field[columns][rows])
{

    initscr();

    start_color();

    init_color(COLOR_RED, 492, 719, 422);
    init_pair(7, COLOR_RED, COLOR_BLACK);

    init_color(COLOR_BLUE, 488, 496, 719);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);


    curs_set(1);

    start_screen();

    int balance = 100;


    int player = 1;
    int player_score = 0;
    int robot_score = 0;

    initialization(rows, columns, field);
    initialization(rows, columns, player_field);
    initialization(rows, columns, robot_field);
    initialization(rows, columns, empty_field);

    player_ship_setting(rows, columns, field, player_field);

    robot_ship_setting(rows, columns, field, robot_field);

    print_fields(rows, columns, player_field, empty_field);

    additional_arsenal(balance);

    move(5, 48);

    attron(COLOR_PAIR(7));
    printw("+-------------------+");

    move(6, 48);
    printw("|       ");

    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(8));
    printw("Score       ");
    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(7));
    printw("|");

    move(7, 48);
    printw("+-------------------+");

    move(8, 48);
    printw("|   ");

    attroff(COLOR_PAIR(7));

    printw("Player  :");

    printw(" %2d    ", player_score);
    attron(COLOR_PAIR(7));
    printw("|");

    move(9, 48);
    printw("|   ");
    attroff(COLOR_PAIR(7));

    printw("Robot   : ");

    printw("%2d    ", robot_score);
    attron(COLOR_PAIR(7));
    printw("|");
    move(10, 48);
    printw("+-------------------+");
    attroff(COLOR_PAIR(7));
    while (1)
    {

        additional_arsenal(balance);

        if (player == 1)
        {

            move(25, 12);

            attron(COLOR_PAIR(8));
            printw("Enter your move: ");
            int x, y;
            scanw(" %lc %d", &y, &x);
            refresh();
            y = toupper(y);

            if ((y == 'Q' || y == 'q') && x == 1)
            {

                int score_before_attack = calculate_score(robot_field, rows, columns);

                int art;

                printw("\nSelect artillery (1-3): ");
                scanw("%d", &art);

                int i;
                int j;
                int f;

                if (art == 1)
                {

                    if (balance - 30 >= 0)
                    {
                        printw("\nEnter the coordinates of the area to BOMBER attack: ");
                        scanw(" %lc %d", &f, &j);
                        f = toupper(f);
                        i = (int)f - 'A';

                        if (empty_field[j][i] != 'X')
                        {
                            if (robot_field[j][i] == 'X')
                            {
                                robot_field[j][i] = '*';
                                empty_field[j][i] = 'X';
                            }
                            else
                            {
                                robot_field[j][i] = '>';
                                empty_field[j][i] = '>';
                            }
                        }

                        if (empty_field[j + 1][i + 1] != 'X')
                        {
                            if (robot_field[j + 1][i + 1] == 'X')
                            {
                                robot_field[j + 1][i + 1] = '*';
                                empty_field[j + 1][i + 1] = 'X';
                            }
                            else
                            {
                                robot_field[j + 1][i + 1] = '>';
                                empty_field[j + 1][i + 1] = '>';
                            }
                        }

                        if (empty_field[j + 2][i - 1] != 'X')
                        {
                            if (robot_field[j + 2][i - 1] == 'X')
                            {
                                robot_field[j + 2][i - 1] = '*';
                                empty_field[j + 2][i - 1] = 'X';
                            }
                            else
                            {
                                robot_field[j + 2][i - 1] = '>';
                                empty_field[j + 2][i - 1] = '>';
                            }
                        }

                        if (empty_field[j + 4][i - 2] != 'X')
                        {
                            if (robot_field[j + 4][i - 2] == 'X')
                            {
                                robot_field[j + 4][i - 2] = '*';
                                empty_field[j + 4][i - 2] = 'X';
                            }
                            else
                            {
                                robot_field[j + 4][i - 2] = '>';
                                empty_field[j + 4][i - 2] = '>';
                            }
                        }

                        if (empty_field[j + 4][i] != 'X')
                        {
                            if (robot_field[j + 4][i] == 'X')
                            {
                                robot_field[j + 4][i] = '*';
                                empty_field[j + 4][i] = 'X';
                            }
                            else
                            {
                                robot_field[j + 4][i] = '>';
                                empty_field[j + 4][i] = '>';
                            }
                        }

                        if (empty_field[j + 6][i + 1] != 'X')
                        {
                            if (robot_field[j + 6][i + 1] == 'X')
                            {
                                robot_field[j + 6][i + 1] = '*';
                                empty_field[j + 6][i + 1] = 'X';
                            }
                            else
                            {
                                robot_field[j + 6][i + 1] = '>';
                                empty_field[j + 6][i + 1] = '>';
                            }
                        }

                        if (empty_field[j + 3][i + 2] != 'X')
                        {
                            if (robot_field[j + 3][i + 2] == 'X')
                            {
                                robot_field[j + 3][i + 2] = '*';
                                empty_field[j + 3][i + 2] = 'X';
                            }
                            else
                            {
                                robot_field[j + 3][i + 2] = '>';
                                empty_field[j + 3][i + 2] = '>';
                            }
                        }

                        balance -= 30;
                        clear();
                        print_fields(rows, columns, player_field, empty_field);
                        additional_arsenal(balance);
                    }
                    else
                    {
                        printw("\nYou don't have enough money\n");
                    }
                }
                else if (art == 2)
                {

                    if (balance - 15 >= 0)
                    {
                        printw("\nEnter the coordinates of the area to MINE attack: ");
                        scanw(" %lc %d", &f, &j);
                        f = toupper(f);
                        i = (int)f - 'A';

                        if (empty_field[j][i] != 'X')
                        {
                            if (robot_field[j][i] == 'X')
                            {
                                robot_field[j][i] = '*';
                                empty_field[j][i] = 'X';
                            }
                            else
                            {
                                robot_field[j][i] = '>';
                                empty_field[j][i] = '>';
                            }
                        }

                        if (empty_field[j + 1][i] != 'X')
                        {
                            if (robot_field[j + 1][i] == 'X')
                            {
                                robot_field[j + 1][i] = '*';
                                empty_field[j + 1][i] = 'X';
                            }
                            else
                            {
                                robot_field[j + 1][i] = '>';
                                empty_field[j + 1][i] = '>';
                            }
                        }

                        if (empty_field[j - 1][i] != 'X')
                        {
                            if (robot_field[j - 1][i] == 'X')
                            {
                                robot_field[j - 1][i] = '*';
                                empty_field[j - 1][i] = 'X';
                            }
                            else
                            {
                                robot_field[j - 1][i] = '>';
                                empty_field[j - 1][i] = '>';
                            }
                        }

                        if (empty_field[j][i - 1] != 'X')
                        {
                            if (robot_field[j][i - 1] == 'X')
                            {
                                robot_field[j][i - 1] = '*';
                                empty_field[j][i - 1] = 'X';
                            }
                            else
                            {
                                robot_field[j][i - 1] = '>';
                                empty_field[j][i - 1] = '>';
                            }
                        }

                        if (empty_field[j][i + 1] != 'X')
                        {
                            if (robot_field[j][i + 1] == 'X')
                            {
                                robot_field[j][i + 1] = '*';
                                empty_field[j][i + 1] = 'X';
                            }
                            else
                            {
                                robot_field[j][i + 1] = '>';
                                empty_field[j][i + 1] = '>';
                            }
                        }

                        balance -= 15;
                        clear();
                        print_fields(rows, columns, player_field, empty_field);
                        additional_arsenal(balance);
                    }
                    else
                    {
                        printw("\nYou don't have enough money\n");
                    }
                }
                else if (art == 3)
                {

                    if (balance - 20 >= 0)
                    {

                        printw("\nEnter the coordinates of the area to ROCKET attack: ");
                        scanw(" %lc %d", &f, &j);
                        f = toupper(f);
                        i = (int)f - 'A';

                        if (empty_field[j][i] != 'X')
                        {
                            if (robot_field[j][i] == 'X')
                            {
                                robot_field[j][i] = '*';
                                empty_field[j][i] = 'X';
                            }
                            else
                            {
                                robot_field[j][i] = '>';
                                empty_field[j][i] = '>';
                            }
                        }

                        if (empty_field[j + 1][i - 1] != 'X')
                        {
                            if (robot_field[j + 1][i - 1] == 'X')
                            {
                                robot_field[j + 1][i - 1] = '*';
                                empty_field[j + 1][i - 1] = 'X';
                            }
                            else
                            {
                                robot_field[j + 1][i - 1] = '>';
                                empty_field[j + 1][i - 1] = '>';
                            }
                        }

                        if (empty_field[j - 1][i - 1] != 'X')
                        {
                            if (robot_field[j - 1][i - 1] == 'X')
                            {
                                robot_field[j - 1][i - 1] = '*';
                                empty_field[j - 1][i - 1] = 'X';
                            }
                            else
                            {
                                robot_field[j - 1][i - 1] = '>';
                                empty_field[j - 1][i - 1] = '>';
                            }
                        }

                        if (empty_field[j + 1][i + 1] != 'X')
                        {
                            if (robot_field[j + 1][i + 1] == 'X')
                            {
                                robot_field[j + 1][i + 1] = '*';
                                empty_field[j + 1][i + 1] = 'X';
                            }
                            else
                            {
                                robot_field[j + 1][i + 1] = '>';
                                empty_field[j + 1][i + 1] = '>';
                            }
                        }

                        if (empty_field[j - 1][i + 1] != 'X')
                        {
                            if (robot_field[j - 1][i + 1] == 'X')
                            {
                                robot_field[j - 1][i + 1] = '*';
                                empty_field[j - 1][i + 1] = 'X';
                            }
                            else
                            {
                                robot_field[j - 1][i + 1] = '>';
                                empty_field[j - 1][i + 1] = '>';
                            }
                        }

                        if (empty_field[j + 3][i] != 'X')
                        {
                            if (robot_field[j + 3][i] == 'X')
                            {
                                robot_field[j + 3][i] = '*';
                                empty_field[j + 3][i] = 'X';
                            }
                            else
                            {
                                robot_field[j + 3][i] = '>';
                                empty_field[j + 3][i] = '>';
                            }
                        }

                        if (empty_field[j - 3][i] != 'X')
                        {
                            if (robot_field[j - 3][i] == 'X')
                            {
                                robot_field[j - 3][i] = '*';
                                empty_field[j - 3][i] = 'X';
                            }
                            else
                            {
                                robot_field[j - 3][i] = '>';
                                empty_field[j - 3][i] = '>';
                            }
                        }

                        if (empty_field[j][i - 3] != 'X')
                        {
                            if (robot_field[j][i - 3] == 'X')
                            {
                                robot_field[j][i - 3] = '*';
                                empty_field[j][i - 3] = 'X';
                            }
                            else
                            {
                                robot_field[j][i - 3] = '>';
                                empty_field[j][i - 3] = '>';
                            }
                        }

                        if (empty_field[j][i + 3] != 'X')
                        {
                            if (robot_field[j][i + 3] == 'X')
                            {
                                robot_field[j][i + 3] = '*';
                                empty_field[j][i + 3] = 'X';
                            }
                            else
                            {
                                robot_field[j][i + 3] = '>';
                                empty_field[j][i + 3] = '>';
                            }
                        }

                        balance -= 20;

                        clear();
                        print_fields(rows, columns, player_field, empty_field);
                        additional_arsenal(balance);
                    }
                    else
                    {
                        printw("\nYou don't have enough money\n");
                    }
                }

                int score_after_attack = calculate_score(robot_field, rows, columns);

                int score_delta = score_after_attack - score_before_attack;
                if (score_delta > 0)
                {
                    player_score += score_delta;
                }
            }
            else if (x >= columns || x < 0 || y - 'A' >= rows || y - 'A' < 0)
            {
                printw("\nINVALID COORDINATES\n");
            }
            else
            {
                int initial_player_score = calculate_score(robot_field, rows, columns);

                shot(rows, columns, empty_field, x, y - 'A', robot_field);

                int updated_player_score = calculate_score(robot_field, rows, columns);

                if (updated_player_score > initial_player_score)
                {
                    player_score += (updated_player_score - initial_player_score);
                }

                clear();
                print_fields(rows, columns, player_field, empty_field);

                move(5, 48);

                attron(COLOR_PAIR(7));
                printw("+-------------------+");

                move(6, 48);
                printw("|       ");

                attroff(COLOR_PAIR(7));

                attron(COLOR_PAIR(8));
                printw("Score       ");
                attroff(COLOR_PAIR(8));

                attron(COLOR_PAIR(7));
                printw("|");

                move(7, 48);
                printw("+-------------------+");

                move(8, 48);
                printw("|   ");

                attroff(COLOR_PAIR(7));

                printw("Player  :");

                printw(" %2d    ", player_score);
                attron(COLOR_PAIR(7));
                printw("|");

                move(9, 48);
                printw("|   ");
                attroff(COLOR_PAIR(7));

                printw("Robot   : ");

                printw("%2d    ", robot_score);
                attron(COLOR_PAIR(7));
                printw("|");
                move(10, 48);
                printw("+-------------------+");
                attroff(COLOR_PAIR(7));
            }
        }
        else
        {
            printw("\nROBOT'S MOVE\n");

            int initial_robot_score = calculate_score(player_field, rows, columns);

            robot_shot(rows, columns, field, player_field);

            int updated_robot_score = calculate_score(player_field, rows, columns);

            if (updated_robot_score > initial_robot_score)
            {
                robot_score++;
            }

            clear();

            print_fields(rows, columns, player_field, empty_field);

            move(5, 48);

            attron(COLOR_PAIR(7));
            printw("+-------------------+");

            move(6, 48);
            printw("|       ");

            attroff(COLOR_PAIR(7));

            attron(COLOR_PAIR(8));
            printw("Score       ");
            attroff(COLOR_PAIR(8));

            attron(COLOR_PAIR(7));
            printw("|");

            move(7, 48);
            printw("+-------------------+");

            move(8, 48);
            printw("|   ");

            attroff(COLOR_PAIR(7));

            printw("Player  :");

            printw(" %2d    ", player_score);
            attron(COLOR_PAIR(7));
            printw("|");

            move(9, 48);
            printw("|   ");
            attroff(COLOR_PAIR(7));

            printw("Robot   : ");

            printw("%2d    ", robot_score);
            attron(COLOR_PAIR(7));
            printw("|");
            move(10, 48);
            printw("+-------------------+");
            attroff(COLOR_PAIR(7));
        }

        player = (player == 1) ? 2 : 1;

        if (check_win(rows, columns, robot_field) == true || player_score == 20)
        {

            clear();
            player_winner();

            return;
        }
        else if (check_win(rows, columns, player_field) == true || robot_score == 20)
        {

            clear();

            robot_winner();

            return;
        }
    }

    endwin();
}
