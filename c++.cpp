#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>


int size = 15;
int shape = 0;
int map_size[] = {size + 2, size - shape};
int x = map_size[0] / 2;
int y = map_size[1] / 2;
int ball_cord[] = {x, y + 1};
int direction[] = {-1, 0};
int player[3][2] = {
    {1 ,map_size[1] / 2 - 1},
    {1, map_size[1] / 2},
    {1, map_size[1] / 2 + 1}
};
int enemy[3][2] = {
    {map_size[0] - 1 ,map_size[1] / 2 - 1},
    {map_size[0] - 1, map_size[1] / 2},
    {map_size[0] - 1, map_size[1] / 2 + 1}
};

int score_p;
int score_r;


void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void restart(){
    player[0][1] = map_size[1] / 2 - 1;
    player[1][1] = map_size[1] / 2;
    player[2][1] = map_size[1] / 2 + 1;
    enemy[0][1] = map_size[1] / 2 - 1;
    enemy[1][1] = map_size[1] / 2;
    enemy[2][1] = map_size[1] / 2 + 1;
    ball_cord[0] = map_size[0] / 2;
    ball_cord[1] = map_size[1] / 2;
    direction[0] = 1;
    direction[1] = 0;
    score_p++;
    system("cls");
    sleep(1000);
}

void ai(){
    if (ball_cord[1] >= 2 && ball_cord[1] <= map_size[1] - 2){
        enemy[0][1] = ball_cord[1] - 1;
        enemy[1][1] = ball_cord[1];
        enemy[2][1] = ball_cord[1] + 1;
    }

}

void move(){
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w') {
            if (player[0][1] > 1){
                for (int i = 0; i < 3; i++){
                    player[i][1] -= 1;
                }
            }
            
        } 
        else if (key == 's') {
            if (player[2][1] < map_size[1] - 1){
                for (int i = 0; i < 3; i++){
                    player[i][1] += 1;
                }
            }
        } 
    }
}


void calculations(){
    
    if (ball_cord[0] == 2){
        if (ball_cord[1] >= player[0][1] && ball_cord[1] <= player[2][1]){
            direction[0] *= -1;
            if (ball_cord[1] == player[0][1]){
                direction[1] = -1;
            }
            else if (ball_cord[1] == player[2][1]){
                direction[1] = 1;
            }
            else{
                direction[1] = 0;
            }
        }
    }
    else if (ball_cord[0] == map_size[0] - 2){
        if (ball_cord[1] >= enemy[0][1] && ball_cord[1] <= enemy[2][1]){
            direction[0] *= -1;
            if (ball_cord[1] == enemy[0][1]){
                direction[1] = -1;
            }
            else if (ball_cord[1] == enemy[2][1]){
                direction[1] = 1;
            }
             else{
                direction[1] = 0;
            }
        }
    }
    if (ball_cord[1] - 1 == 0 && direction[1] == -1){
        direction[1] *= -1;
    }
    else if (ball_cord[1] + 1 == map_size[1] && direction[1] == 1){
        direction[1] *= -1;
    }
    ball_cord[0] += direction[0];
    ball_cord[1] += direction[1];
    if (ball_cord[0] == 0 || ball_cord[0] == map_size[0]){
        restart();
    }
}


void draw(){
    std::cout << "\x1b[H"; 
    std:: cout << " ";
    for (int i = 0; i <= map_size[1];i++){
        for (int j = 0; j <= map_size[0];j++){
            if (j == 1 && i >= player[0][1] && i <= player[2][1]){
                std::cout << "G";
            }
            else if (j == map_size[0] - 1 && i >= enemy[0][1] && i <= enemy[2][1]){
                std::cout << "G";
            }
            else if (j == ball_cord[0] && i == ball_cord[1]){
                std::cout << "@";
            }
            else if (i == 0 || i == map_size[1]){
                if (j == map_size[0]){
                    std::cout << "#" << std::endl;
                }
                else{
                    std::cout << "#";
                }
                
            }
            else if (j == 0 || j == map_size[0]){
                if (j == map_size[0]){
                    std::cout << "#" << std::endl;
                }
                else{
                    std::cout << "#";
                }
                
            }
            else{
                std::cout << ".";
            }
            std::cout << " ";
        }

    }
    
    sleep(100);

}

int main(){
    while (true){
        move();
        ai();
        calculations();
        draw();
    }
    return 0;
}
