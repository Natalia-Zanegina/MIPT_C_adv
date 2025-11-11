#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>

#define MIN_Y 2
#define START_TAIL_SIZE 3
#define MAX_TAIL_SIZE 100
#define CONTROLS 3
#define MAX_FOOD_SIZE 20
#define FOOD_EXPIRE_SECONDS 10 
double DELAY = 0.1;

enum {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = KEY_F(10)
};

struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
};

struct control_buttons default_controls[CONTROLS] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}, {'S', 'W', 'A', 'D'}, {'s', 'w', 'a', 'd'}};

typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t* tail;
    struct control_buttons* controls;
} snake_t;


typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

void initTail(tail_t t[], size_t size)
{
    tail_t init_t = {0, 0};
    for (size_t i = 0; i < size; i++)
        t[i] = init_t;
}

void initHead(snake_t* head, int x, int y)
{
    head -> x = x;
    head -> y = y;
    head -> direction = RIGHT;
}

void initSnake(snake_t* head, size_t size, int x, int y)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head -> tail = tail;
    head -> tsize = size + 1;
    head -> controls = default_controls;
}

void go(snake_t* head)
{
    char ch = '@';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(head -> y, head -> x, " ");
    switch (head -> direction)
    {
        case LEFT:
            if (head -> x <= 0)
                head -> x = max_x;
            mvprintw(head -> y, --(head -> x), "%c", ch);
            break;
        case RIGHT:
            if (head -> x >= max_x)
                head -> x = 0;
            mvprintw(head -> y, ++(head -> x), "%c", ch);
            break;
        case UP:
            if (head -> y <= MIN_Y)
                head -> y = max_y;
            mvprintw(--(head -> y), head -> x, "%c", ch);
            break;
        case DOWN:
            if (head -> y >= max_y)
                head -> y = MIN_Y;
            mvprintw(++(head -> y), head -> x, "%c", ch);
            break;
        default:
            break;
    }
    refresh();
}

void goTail(snake_t* head)
{
    char ch = '*';
    mvprintw(head -> tail[head -> tsize - 1].y,head -> tail[head -> tsize - 1].x, " ");
    for (size_t i = head -> tsize - 1; i > 0; i--)
    {
        head -> tail[i] = head -> tail[i - 1];
        if ((head -> tail[i].y) || (head -> tail[i].x))
            mvprintw(head -> tail[i].y, head -> tail[i].x, "%c", ch);
    }
    head -> tail[0].x = head -> x;
    head -> tail[0].y = head -> y;
}

int checkDirection(snake_t* snake, int32_t key) // функция, проверяющая корректность выбранного направления
{
    for (int i = 0; i < CONTROLS; i++)
    {    
        if ((key == snake -> controls[i].down && snake -> direction == UP) || // запрет на перемещение сверху вниз
        (key == snake -> controls[i].up && snake -> direction == DOWN) ||     // запрет на перемещение снизу вверх
        (key == snake -> controls[i].left && snake -> direction == RIGHT) ||  // запрет на перемещение справа налево
        (key == snake -> controls[i].right && snake -> direction == LEFT))    // запрет на перемещение слева направо
            return 0;
    }
    return 1;
}

void changeDirection(snake_t* snake, const int32_t key)
{
    if (!checkDirection(snake, key))
        return;

    for (int i = 0; i < CONTROLS; i++)
    {
        if (key == snake -> controls[i].down)
            snake -> direction = DOWN;
        else if (key == snake -> controls[i].up)
            snake -> direction = UP;
        else if (key == snake -> controls[i].right)
            snake -> direction = RIGHT;
        else if (key == snake -> controls[i].left)
            snake -> direction = LEFT;
    }
}

_Bool isCrush(snake_t* snake) // проверка, не врезалась ли змейка сама в себя
{
    for (size_t i = 1; i < snake->tsize; i++)
    {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y)
            return 1;
    }
    return 0;
}

void printCrush() // печать сообщения об аварии
{
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(max_y / 2 - 1, max_x / 2 - 5, "Crash!");
    refresh();
    getchar();
}

void initFood(struct food f[], size_t size)
{
    struct food init = {0, 0, 0, 0, 0};
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);
    for(size_t i = 0; i < size; i++)
        f[i] = init;
}

void putFoodSeed(struct food* fp)
{
    int max_x = 0, max_y = 0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 2;
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp -> point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

void putFood(struct food f[], size_t number_seeds)
{
    for(size_t i = 0; i < number_seeds; i++)
        putFoodSeed(&f[i]);
}


void refreshFood(struct food f[], int nfood)
{
    int max_x = 0, max_y = 0;
    //char
    getmaxyx(stdscr, max_y, max_x);
    for(size_t i = 0; i < nfood; i++)
    {
        if(f[i].put_time)
        {
            if(!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
                putFoodSeed(&f[i]);
        }
    }
}

_Bool haveEat(struct snake_t *head, struct food f[]){ // Проверка того, является ли какое-то из зерен съеденным
    for (size_t i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if (f[i].enable && head->x == f[i].x && head->y == f[i].y)
        {
            f[i].enable = 0;
            return 1;
        }
    }    
    return 0;
}

void addTail(struct snake_t *head){ // Увеличение хвоста на 1 элемент
    if (head == NULL || head -> tsize > MAX_TAIL_SIZE)
    {
        mvprintw(0, 0, "Can't add tail");
        return;
    }
    head -> tsize++;
}

void update(struct snake_t* head, struct food f[], const int32_t key){
    clock_t begin = clock(); 
    go(head);
    goTail(head);
    if(checkDirection(head, key))
        changeDirection(head, key);
    refreshFood(f, MAX_FOOD_SIZE);
    if(haveEat(head, f)) // проверка на съедение
            addTail(head);
    refresh();
    while ((double) (clock() - begin) / CLOCKS_PER_SEC < DELAY)
    {}    
}

void repairSeed(struct food f[], size_t nfood, struct snake_t* head) // проверка корректности выставления еды
{
    for (size_t i = 0; i < head->tsize; i++) // если хвост совпадает с едой
    {
        for (size_t j = 0; j < nfood; j++)
        {
            if (f[j].x == head->tail[i].x && f[j].y == head->tail[i].y && f[j].enable)
            {
                mvprintw(2, 0, "Repair tail seed %zu", j);
                putFoodSeed(&f[j]);
            }
        }
    }

    for (size_t i = 0; i < nfood; i++) // если еда дважды на одной точке
    {
        for (size_t j = 0; j < nfood; j++)
        {
            if (i != j && f[i].enable && f[j].enable && f[j].x == f[i].x && f[j].y == f[i].y)
            {
                mvprintw(1, 1, "Repair same food %zu", j); 
                putFoodSeed(&f[j]);
            }
            
        }
    }
    
}

int main(void)
{
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    struct food food[MAX_FOOD_SIZE];

    initSnake(snake, START_TAIL_SIZE, 10, 10);
    initFood(food, MAX_FOOD_SIZE);

    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    mvprintw(0, 1, "Use arrows or WASD keys for control. Press 'F10' for EXIT.");
    timeout(0);
    int key_pressed = 0;

    putFoodSeed(food);
    putFood(food, MAX_FOOD_SIZE);

    while (key_pressed != STOP_GAME)
    {
        key_pressed = getch();
        if (isCrush(snake))
        {
            printCrush();
            break;
        }
        go(snake);
        goTail(snake);
        timeout(100);
        refreshFood(food, MAX_FOOD_SIZE);
        if(haveEat(snake, food)) // проверка на съедение
            addTail(snake);
        changeDirection(snake, key_pressed);
        // repairSeed(food, MAX_FOOD_SIZE, snake); - добавить функцию
    }
    
    free(snake -> tail);
    free(snake);
    endwin();
    return 0;
}