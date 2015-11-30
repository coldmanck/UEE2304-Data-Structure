#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
char maze[10][12] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,0,1,0,1,0,1},
	{1,1,1,0,1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,1,1,1,0,1},
	{1,1,0,1,1,1,1,1,1,1,0,0},
	{1,1,0,1,0,1,1,1,1,1,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
	};
int size_row = 10, size_col = 12;
char dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
typedef struct _point{
  int x, y;
  char d;
  struct _point *prev;
} point;
int main(){
    int x, y, i, j;
    point *stack = NULL;
    for(i = 0; i < size_row; i++){
      for(j = 0; j < size_col; j++){
        printf("%d ", maze[i][j]);
      }
      printf("\n");
    }

    fprintf(stdout, "input where to start (e.g. '2 3' means row 2, col 3), exit = (4, 11): ");
    fscanf(stdin, "%d %d", &x, &y);
	printf("Path (reverse): ");

    point *p = (point*)malloc(sizeof(point));
    p->x = x;
    p->y = y;
    p->d = -1;
    p->prev = stack;
    stack = p;

    while(1){
      int find = 0, x_, y_;
      for(i=stack->d+1; i<4; ++i){
        x_ = stack->x+dirs[i][0];
        y_ = stack->y+dirs[i][1];
        if(maze[x_][y_] == 0){
          if(stack->prev && x_ == stack->prev->x && y_ == stack->prev->y)
            continue;
          point *p = (point*)malloc(sizeof(point));
          stack->d = i;
          p->d = -1;
          p->x = stack->x+dirs[i][0];
          p->y = stack->y+dirs[i][1];
          p->prev = stack;
          stack = p;
          find = 1;
          break;
        }
      }
      if(!find){
        point *p = stack;
        stack = stack->prev;
        free(p);
      }
      if(stack->x == 0 || stack->x == size_row-1 ||
         stack->y == 0 || stack->y == size_col-1){
        point *p = stack, *p_;
        while(p_ = p){
          printf("(%d, %d) ", p->x, p->y);
          maze[p->x][p->y] = 2;
          p = p->prev;
          free(p_);
        }
        break;
      }
    }
    printf("\n");
	/*
    for(i = 0; i < size_row; i++){
      for(j = 0; j < size_col; j++){
        printf("%s ", (maze[i][j]==2));
      }
      printf("\n");
    }
	*/

    return 0;
}
