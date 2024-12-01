#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int width = 40;
    int heigth = 20;
    //score counter
    int score = 0;

    //initialise the screen
    //WINDOW is a structure in ncurses
    //initscr() is a function in the ncurses library used to initialize the library and set up the terminal for ncurses operations. It is the starting point for any ncurses program.
    WINDOW *win = initscr();
    //take player input
    //The keypad() function in ncurses is used to enable or disable the processing of special keys
    //keypad(*win, boolean)
    keypad(win, true);
        //The no delay() function in ncurses is used to control the behavior of getch() when waiting for user input
    //when true getchar() returns if no input is there
    //nodelay(*win, boolean)
    //the game continues even when the user isnt inputing, only takes when the user types in another key
    nodelay(win, true);
    //position of charater
    //use rand, with seed for a different input everytime
    //
    curs_set(0);
    srand(time(0));
    char grid[heigth][width];

    int posX = rand() %(width-2) + 1;
    int posY = rand() %(heigth-2) + 1;

    int foodX = rand() %(width-2) + 1;
    int foodY = rand() %(heigth-2) + 1;

    //using an array to store the length of the snake
    int snakeX[50] = {posX};
    int snakeY[50] = {posY};
    int snakelength = 1;

    //1 for right
    int dirX = 1;
    int dirY = 0;

    while (true){
        //wgetch get arg of the window
        //wgetch(*win);
        int pressed = wgetch(win);
        if (pressed == KEY_LEFT){
            dirX = -1;
            dirY = 0;
        }
        if (pressed == KEY_RIGHT){
            dirX = 1;
                 dirY = 0;
        }
        if (pressed == KEY_UP){
            dirX = 0;
            dirY = -1;
        }
        if (pressed == KEY_DOWN){
            dirX = 0;
            dirY = 1;
        }
        if (pressed == 'q'){
            printf("Game quit!, Your score is:%d ",score);
            break; 
        }
        posX += dirX;
        posY += dirY;

        // Exit game loop if bounday crossed
        if (posX <=0 || posX >= width-1 || posY <=0 || posY >= heigth-1) {
            printf("you crossed the boundary, Game over! Your score is: %d",score);
             break;
        }

        //snake position update for the entire array
        for(int i=snakelength-1;i>0;i--){
            snakeX[i]=snakeX[i-1];
            snakeY[i]=snakeY[i-1];
        }
        snakeX[0] = posX;
        snakeY[0] = posY;

        clear();

    // Boundaries and food drawing
    for (int y = 0; y < heigth; y++) {
        for (int x = 0; x < width; x++) {
        // Set boundaries
            if (y == 0 || y == heigth - 1 || x == 0 || x == width - 1) {
                grid[y][x] = '#';
            } else {
                grid[y][x] = ' ';
            }
        }
    }

    // Place food
    grid[foodY][foodX] = '@';

    // Draw boundary and food
    for (int y = 0; y < heigth; y++) {
        for (int x = 0; x < width; x++) {
            mvaddch(y, x, grid[y][x]);
        }
    }

        //dynamic snake length
        mvaddch(posY,posX,'0');
        for(int i=0;i<snakelength;i++){
            mvaddch(snakeY[i], snakeX[i],'o');
        }

        //if snake touches food, the food regenerates soemwhere random
        if (foodX == posX && foodY == posY){
            foodX = rand() % (width-2)+1;
            foodY = rand() % (heigth-2)+1;
            score++;
            snakelength++;
        }


        //snake self collision
        for(int i=1;i<snakelength; i++){
            if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
                endwin();
                printf("Seld collision! Game over! Your score is:%d",score);
                return 0;
            }
        }

        //mv add str enables you to position a string on the window
        // //mvhline(y, x, ch, n)--horizontal  || mvvline(y, x, ch, n)--vertical
        // mvhline(0,0,'#',width);// top
        // mvvline(0,0,'|', heigth);//left
        // mvhline(heigth-1,0,'#',width);//bottom
        // mvvline(0,width-1,'|',heigth);//right
        //mvaddstr(int y, int x, const char *str);

        //like mvaddstr, mvprintw -- for printing on window
        mvprintw(0,0,"score: %d  ", score);
        mvaddstr(heigth,0, "Press q to quit");
        refresh();

        //usleep suspends execution for an interval(microseconds)
        usleep(400000 - (score * 10000));
    }


    endwin();
    return 0;

}










