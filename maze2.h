/*
 * N.Satya Mounika CS12B020
 * maze_project maze.h file
 *
 */
typedef struct node2_ Node2;
struct node2_ {
int data;
Node2* next;
};
typedef struct Q_ {
Node2* head;
}Q;

int shortestDistance2(char** maze, int N,Q* ,Q* ,int** depth,int** visited,char searchsymbol);
void engine2(int** Maze,char** maze,int N,int score_U,int score_E,int ux,int uy,int ex,int ey,int ,int );
void printmaze2(char** maze,int N,int U_score,int E_score,int d, char cal_bot);
int bot2(int** Maze,char** maze,int N,int score1,int score2,int a1,int a2,int b1,int b2);
int SD2(char** maze,int N,int x,int y,char symbol);
void insertE2(char** ,int N,int );
void generateMaze2(char** maze,int N);
void get_intMaze2(int** Maze,char** maze,int N);
int best2(int pos1,int pos2,int x,int y,char** maze,int N,int l);
int SD_2(char** maze,int N,int x,int y,char symbol,int* m,int* n,int** v);
int shortestDistance_2(char** maze,int N,Q* qx,Q* qy,int** depth,int** visited,char searchsymbol,int* m,int* n,int** v);
Q* q_push( Q* q, int val );
Q* q_pop( Q* q );
int q_top( Q* );
int queue_size( Q* q );
void Initialise2(int** );
