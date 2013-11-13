/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : engine2.c

* Purpose : engine of Maze game

* Creation Date : 2-11-2013

* Last Modified : Wednesday 13-11-2013 6:30 PM

* Created By : N Satya Mounika CS12B020

_._._._._._._._._._._._._._._._._._._._._.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/


#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char *argv[])
{   
    int i1=atoi(argv[1]);//player 1
    int i2=atoi(argv[2]);//player 2
    int N,i,j;
    N=42;
    srand(time(NULL));
    char** maze=malloc(N*sizeof(char*));
    int** Maze=malloc(N*sizeof(int*));
    for(i=0;i<N;i++){
        maze[i]=malloc(N*sizeof(char));
        Maze[i]=malloc(N*sizeof(int));
    }
    generateMaze2(maze,N);           //generates random maze
    get_intMaze2(Maze,maze,N);       //creates the corresponding integer maze
    printmaze2(maze,N,0,0,0,'U');
    int score_U,score_E;
    score_U=score_E=0;          
    int count=0;             //count is the number of elements in the maze other than U and E
    int ux,uy,ex,ey;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(maze[i][j]=='U')
            {
                ux=i;
                uy=j;
            }
            else if(maze[i][j]=='E')
            {
                ex=i;
                ey=j;
            }
            else count++;
        }
    }
    
    if(count!=(N*N -2))//to check if E and U are at same positions
    {
        ux=ex;          //If U and E are at same position U can't be seen in the maze.So,it assigns the position of E to U.
        uy=ey;
    }
    
    switch(i1){
        case 1:Initialise1(Maze);
        case 2:Initialise2(Maze);
        case 3:Initialise3(Maze);
    }
    switch(i2){
        case 1:Initialise1(Maze);
        case 2:Initialise2(Maze);
        case 3:Initialise3(Maze);
    }
    
    
    
    engine2(Maze,maze,N,score_U,score_E,ux,uy,ex,ey,i1,i2);
}


/******************************************************************
 *ux,uy coordinates of U 
 *ex,ey coordinates of E
 *engine2 controls game play ,calls bot, changes position of bot and 
 *                            makes the new maze ready for the next player.
 *done =0 till R is not visited
 *      1 if R is reached(Game over)
 ************************************************************************/
void engine2(int** Maze,char** maze,int N,int score_U,int score_E,int ux,int uy,int ex,int ey, int bot_num1, int bot_num2){
    int done=0;
    int p;
    switch(bot_num1){   //calls the respective bots
        case(1): p=bot1(Maze,maze,N,score_U,score_E,ux,uy,ex,ey);
                break;
        case(2): p=bot2(Maze,maze,N,score_U,score_E,ux,uy,ex,ey);
                break;
        case(3): p=bot3(Maze,maze,N,score_U,score_E,ux,uy,ex,ey);
                break;
    }
    //making changes in maze by moving U to the new position
    if(ux==ex && uy==ey)
        maze[ux][uy]='E';//case when U and E overlap
    else
        maze[ux][uy]='.';
    if(p==0)
        ux--;
    else if(p==1)
        uy++;
    else if(p==2)
        ux++;
    else 
        uy--;
    score_U += Maze[ux][uy];
    Maze[ux][uy]=0;
    
    if(maze[ux][uy]=='R')    //check if the game is over
        done=1;
    maze[ux][uy]='U';
    printmaze2(maze,N,score_U,score_E,done,'U');
    if(done==0)//if the game is not done calls next player
    {
        
        switch(bot_num2){
                case(1): p=bot1(Maze,maze,N,score_U,score_E,ex,ey,ux,uy);
                        break;
                case(2): p=bot2(Maze,maze,N,score_U,score_E,ex,ey,ux,uy);
                        break;
                case(3): p=bot3(Maze,maze,N,score_U,score_E,ex,ey,ux,uy);
                        break;
        }        
        //making changes in maze by moving E to the new position
        if(ex==ux && ey== uy)
            maze[ex][ey]='U';
        else
            maze[ex][ey]='.';
            
        if(p==0)     ex--;
        else if(p==1)ey++;
        else if(p==2)ex++;
        else         ey--;
        
        score_E += Maze[ex][ey];
        Maze[ex][ey]=0;
        if(maze[ex][ey]=='R')
        done=1;
        maze[ex][ey]='E';
        printmaze2(maze,N,score_U,score_E,done,'E');
        if(done!=1)//continue the game if its not done
            engine2(Maze,maze,N,score_U,score_E,ux,uy,ex,ey,bot_num1,bot_num2);
    }
}


// prints maze and scores of U and E
void printmaze2(char** maze,int N,int U_score,int E_score,int d, char cal_bot){
    int i,j;
    sleep(1);
    system("clear");
    for(i=0;i<N;i++)
    {
        printf("\t\t\t");
        for(j=0;j<N;j++)
            printf("%c ",maze[i][j]);
        printf("\n");
    }
    
    printf("\tSCORE BOARD");
    printf("\tU score : %d",U_score);
    printf("\tE score : %d\n",E_score);

    if(d==1){
        printf("\n");
        if(U_score>E_score)
            printf("    U has won the game.\n");
        else if(U_score<E_score)
            printf("    E has won the game.\n");
        else if(U_score==E_score){  //if both bots have same score ,then the bot which catches the Reward wins
            if(cal_bot=='U')
                printf("    U has won the game.\n");
            else
                printf("    E has won the game.\n");
        }
        sleep(2);
        printf("\n.*.*.*.*.*.*.*  GAME OVER  *.*.*.*.*.*.*.*.\n");printf("\n");
    }
}


/***************************************************************************
 *returns position to which bot should move
 *a1,a2 coordinates of our bot 
 *b1,b2 coordinates of enemy bot
 *positions 0(UP)
            1(RIGHT)
            2(DOWN)
            3(LEFT)
 ********************************************************************************/
int bot2(int** Maze,char** maze,int N,int score1,int score2,int a1,int a2,int b1,int b2)
{   int x=a1;
    int y=a2;
    int p;
    char c1,c2,c3,c0;
    c1=maze[x][y+1];
    c3=maze[x][y-1];
    c0=maze[x-1][y];
    c2=maze[x+1][y];
    int sd[4];//sd : shortest distance from each points to R    
    if(c1=='R')     
        return 1;
    else if(c2=='R')
        return 2;
    else if(c3=='R')
        return 3;
    else if(c0=='R')
        return 0;
    
    if(c1!='#')
         sd[1]=SD2(maze,N,x,y+1,'R');
    else
         sd[1]=N*N;//N*N is maximum distance possible
    if(c2!='#') 
        sd[2]=SD2(maze,N,x+1,y,'R');
    else
         sd[2]=N*N;
    if(c3!='#')
         sd[3]=SD2(maze,N,x,y-1,'R');
    else 
        sd[3]=N*N;
    if(c0!='#')
         sd[0]=SD2(maze,N,x-1,y,'R');
    else
         sd[0]=N*N;

     
     
     
    //comparing shortest distances
    if(sd[1]<sd[2])
        p=1;
    else if(sd[1]>sd[2])
        p=2;     
    else if(sd[1]==sd[2] && sd[1]<=sd[3] && sd[1]<=sd[0])
        p=best2(1,2,x,y,maze,N,sd[1]);// Call for the best of two possible positions
    else {
        p=1; 
        sd[p]=N*N;
        }
    if(sd[3]<sd[p])
        p=3;
    else if(sd[3]==sd[p] && sd[3]<=sd[0])
        p=best2(p,3,x,y,maze,N,sd[3]);
    
    if(sd[0]<sd[p])
        p=0;
    else if(sd[0]==sd[p])
        p=best2(0,p,x,y,maze,N,sd[0]);
    return p;
        
}



/***********************************************************************
 *from positions 1 and 2 shortest distance to R is same
 *count1 has the number of points in the shortest path from pos1 to R 
 *count2 has the number of points in the shortest path from pos2 to R
 *returns position with maximum number of count.
 ***********************************************************************/
int best2(int pos1,int pos2,int x,int y,char** maze,int N,int l){
    int a1,a2,b1,b2,count1,count2,i,j,first1,sec1,first2,sec2;
    a1=a2=x;
    b1=b2=y;
    if(pos1==0)a1--;
    else if(pos1==1)b1++;
    else if(pos1==2)a1++;
    else if(pos1==3)b1--;
    if(pos2==0)a2--;
    else if(pos2==1)b2++;
    else if(pos2==2)a2++;
    else if(pos2==3)b2--;
    int *m = malloc(sizeof(int));// m,n store temporarily visited B coordinates
    int *n = malloc(sizeof(int));
    int** v= malloc(N*sizeof(int*));//visited matrix only for B's
    for(i=0; i<N ;i++){         
    v[i] = malloc(N*sizeof(int));
    }
    for(i=0 ; i<N ;i++){
        for(j=0 ; j<N ;j++)
            v[i][j]=0;                
    }
    if(maze[a1][b1]=='B')
    {
        count1=1;
        v[a1][b1]=1;
        *m=a1,*n=b1;
    }
    else count1=0;
    first1 = SD_2(maze,N,a1,b1,'B',m,n,v);
    while(first1!=-1 )
    {
        sec1=SD2(maze,N,*m,*n,'R');
        if(first1+sec1==l)
            count1++;
        first1 = SD_2(maze,N,a1,b1,'B',m,n,v);
    }
    for(i=0 ; i<N ;i++){
        for(j=0 ; j<N ;j++)
            v[i][j]=0;                //initially all elements are non visited
    }
    if(maze[a2][b2]=='B')
    {
        count2=1;
        v[a2][b2]=1;
        *m=a2;*n=b2;
    }
    else count2=0;
    first2 = SD_2(maze,N,a2,b2,'B',m,n,v);
    while(first2!=-1 )
    {
        sec2=SD2(maze,N,*m,*n,'R');
        if(first2+sec2==l)
            count2++;
        first2 = SD_2(maze,N,a2,b2,'B',m,n,v);
    }
        
    if(count1>=count2)
    return pos1;
    else 
    return pos2;
    
    
}    


//pointers m,n store temporary coordinates of B
int SD_2(char** maze,int N,int x,int y,char symbol,int* m,int* n,int** v){

    int** visited = malloc(N*sizeof(int*));
    int** depth = malloc(N*sizeof(int*));
    int i,j;                                          //memory allocation for 2D matrices
    for(i=0; i<N ;i++){         
    visited[i] = malloc(N*sizeof(int));
    depth[i] = malloc(N*sizeof(int));
    }
    depth[x][y]=0;
    Q* q1= malloc(sizeof(Q));q1->head = NULL;
    Q* q2 =malloc(sizeof(Q));q2->head = NULL;
    q_push(q1,x);
    q_push(q2,y);

    for(i=0 ; i<N ;i++){
        for(j=0 ; j<N ;j++)
            visited[i][j]=0;                //initially all elements are non visited
    }
    visited[x][y]=1;
    depth[x][y]=0;
    int distance= shortestDistance_2(maze,N,q1,q2,depth,visited,symbol,m,n,v);
    free(visited);
    free(depth);
    free(q1);
    free(q2);
    return distance;
    
}

//m,n pointers temporarily store adress of B until another B is visited
int shortestDistance_2(char** maze,int N,Q* qx,Q* qy,int** depth,int** visited,char searchsymbol,int* m,int* n,int** v){

    while(qx->head!=NULL){ 
        int x = q_top(qx);
        int y = q_top(qy);
        
        if(x<0||x>N-1||y<0||y>N-1){
            q_pop(qx);
            q_pop(qy);
            return shortestDistance_2(maze,N,qx,qy,depth,visited,searchsymbol,m,n,v);
        }
        
        else if(maze[x][y] == searchsymbol && v[x][y]==0){
            v[x][y]=1;//mark B visited
            *m=x;*n=y;//store adress of coordinates of B
            return depth[x][y];
        }
        else if(maze[x][y] == '#'){
            q_pop(qx);
            q_pop(qy);
            return shortestDistance_2(maze,N,qx,qy,depth,visited,searchsymbol,m,n,v);
        }
        
        else {
            q_pop(qx);q_pop(qy);
            if(visited[x][y+1]==0){                         //pushes adjacent vertices which are non visited into the queue
            q_push(qx,x);q_push(qy,y+1);visited[x][y+1]=1;}
            if(visited[x][y-1]==0){
            q_push(qx,x);q_push(qy,y-1);visited[x][y-1]=1;}
            if(visited[x-1][y]==0){
            q_push(qx,x-1);q_push(qy,y);visited[x-1][y]=1;}
            if(visited[x+1][y]==0){
            q_push(qx,x+1);q_push(qy,y);visited[x+1][y]=1;}
            depth[x][y+1]=depth[x][y-1]=depth[x-1][y] =depth[x+1][y] =1+depth[x][y];
            return shortestDistance_2(maze,N,qx,qy,depth,visited,searchsymbol,m,n,v);
        }
    }    
    return -1;      //if there is no path returns -1
}



//returns shortest distance from maze[x][y] to the symbol.
int SD2(char** maze,int N,int x,int y,char symbol){

    int** visited = malloc(N*sizeof(int*));
    int** depth = malloc(N*sizeof(int*));
    int i,j;                                          //memory allocation for 2D matrices
    for(i=0; i<N ;i++){         
    visited[i] = malloc(N*sizeof(int));
    depth[i] = malloc(N*sizeof(int));
    }
    depth[x][y]=0;
    Q* q1= malloc(sizeof(Q));q1->head = NULL;
    Q* q2 =malloc(sizeof(Q));q2->head = NULL;
    q_push(q1,x);
    q_push(q2,y);

    for(i=0 ; i<N ;i++){
        for(j=0 ; j<N ;j++)
            visited[i][j]=0;                //initially all elements are non visited
    }
    visited[x][y]=1;
    depth[x][y]=0;
    int distance= shortestDistance2(maze,N,q1,q2,depth,visited,symbol);
    free(visited);
    free(depth);
    free(q1);
    free(q2);
    return distance;
    
}

//used in SD,from coordinates at qx_top qy_top to searchsymbol(bfs) 
int shortestDistance2(char** maze,int N,Q* qx,Q* qy,int** depth,int** visited,char searchsymbol){

    while(qx->head!=NULL){ 
        int x = q_top(qx);
        int y = q_top(qy);
        
        if(x<0||x>N-1||y<0||y>N-1){
            q_pop(qx);
            q_pop(qy);
            return shortestDistance2(maze,N,qx,qy,depth,visited,searchsymbol);
        }
        
        else if(maze[x][y] == searchsymbol)
            return depth[x][y];
        
        else if(maze[x][y] == '#'){
            q_pop(qx);
            q_pop(qy);
            return shortestDistance2(maze,N,qx,qy,depth,visited,searchsymbol);
        }
        
        else {
            q_pop(qx);q_pop(qy);
            if(visited[x][y+1]==0){                         //pushes adjacent vertices which are non visited into the queue
            q_push(qx,x);q_push(qy,y+1);visited[x][y+1]=1;}
            if(visited[x][y-1]==0){
            q_push(qx,x);q_push(qy,y-1);visited[x][y-1]=1;}
            if(visited[x-1][y]==0){
            q_push(qx,x-1);q_push(qy,y);visited[x-1][y]=1;}
            if(visited[x+1][y]==0){
            q_push(qx,x+1);q_push(qy,y);visited[x+1][y]=1;}
            depth[x][y+1]=depth[x][y-1]=depth[x-1][y] =depth[x+1][y] =1+depth[x][y];
            return shortestDistance2(maze,N,qx,qy,depth,visited,searchsymbol);
        }
    }    
    return -1;      //if there is no path returns -1
}

Q* q_push( Q* q, int val ){//q -> head points to back of the queue
    Node2* new = malloc(sizeof(Node2));
    new -> data = val;
    new -> next = q -> head;
    q -> head = new;
    return q;
}

Q* q_pop( Q* q ){       //pops from front of the queue
    int size =queue_size(q );
    int i =1;
    Node2* temp = q -> head;
    if(temp -> next == NULL)
        q -> head = NULL;
    else{
        while(i < size-1){
            temp = temp -> next;
            i++;
        }
        Node2* ptr = temp-> next;
        free(ptr);
        temp -> next = NULL;
    }
    return q;
        
}

int queue_size( Q* q ){     //gives size of the queue
    int i =0;
    Node2* temp;
    temp = q -> head;
    while(temp != NULL){
        temp = temp -> next;
        i++;
    }
    return i;
}

int q_top( Q* q){           //returns element at front of the queue
    int s= queue_size(q);
    int i;
    Node2* temp = q->head;
    for(i = 1;i<s;i++){
    temp = temp->next;
    }
    return temp->data;
}



/***********************************************************
 *generates random maze  with
 * 50 bonuses(B)
 * R(reward),E,U bots
 * 400 walls #
 ***********************************************************/
void generateMaze2(char** maze,int N){
    int i,j,k;
    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
        maze[i][j]='.';
    //boundary walls
    for(j=0;j<N;j++)
    {
        maze[0][j]='#';
        maze[N-1][j]='#';
    }
    for(i=1;i<N-1;i++)
    {
        maze[i][0]='#';
        maze[i][N-1]='#';
    }
    k=1;// places 400 walls
    while(k<=400){
        i=1+ (rand()%40);
        j=1+ (rand()%40);
        if(maze[i][j]!='#')
        {
            maze[i][j]='#';
            k++;
        }
    }
    maze[N-2][N-2]='R';
    k=0;
    //generates 50 bonus points
    while(k<50){
        i=1+ (rand()%40);
        j=1+ (rand()%40);
        if(maze[i][j]=='.')
        {
            maze[i][j]='B';
            k++;
        }
    }


        i=1+ (rand()%40);
        j=1+ (rand()%40);
        if(maze[i][j]=='.')
            maze[i][j]='U';
        int d = SD2(maze,N,i,j,'R');
        if(d!=-1){
            insertE2(maze,N,d);//To place E at same distance as U from R  
        }
        else
        {
            generateMaze2(maze,N);//regenerate maze if no path from U to R
        
        }
      
}



//Puts E in the maze from same distance as U from R.
//Makes bfs from reward for l moves,where l is the shortest distance of R from U.

void insertE2(char** maze,int N,int d){
    int** visited = malloc(N*sizeof(int*));
    int** depth = malloc(N*sizeof(int*));
    int i,j;
    int x=N-2;
    int y=N-2;                                          
    for(i=0; i<N ;i++){         
    visited[i] = malloc(N*sizeof(int));
    depth[i] = malloc(N*sizeof(int));
    }
    Q* q1= malloc(sizeof(Q));q1->head = NULL;
    Q* q2 =malloc(sizeof(Q));q2->head = NULL;
    q_push(q1,x);
    q_push(q2,y);

    for(i=0 ; i<N ;i++){
        for(j=0 ; j<N ;j++)
            visited[i][j]=0;                
    }
    visited[x][y]=1;
    depth[x][y]=0;
    //breadth first search
    while(q1->head!=NULL&&depth[q_top(q1)][q_top(q2)]<d){
        x=q_top(q1);
        y=q_top(q2);
        q_pop(q1);
        q_pop(q2);
        if((maze[x-1][y])!='#' && visited[x-1][y]==0){
        q_push(q1,x-1);
        q_push(q2,y);
        visited[x-1][y]=1;
        depth[x-1][y]=depth[x][y]+1;
        }

       
        if(maze[x+1][y]!='#'&&visited[x+1][y]==0){
        q_push(q1,x+1);
        q_push(q2,y);
        visited[x+1][y]=1;
        depth[x+1][y]=depth[x][y]+1;
        }

        if(maze[x][y+1]!='#'&&visited[x][y+1]==0){
        q_push(q1,x);
        q_push(q2,y+1);
        visited[x][y+1]=1;
        depth[x][y+1]=depth[x][y]+1;
        }

        if(maze[x][y-1]!='#'&&visited[x][y-1]==0){
        q_push(q1,x);
        q_push(q2,y-1);
        visited[x][y-1]=1;
        depth[x][y-1]=depth[x][y]+1;
        }

    }
    maze[q_top(q1)][q_top(q2)]='E';
    free(visited);
    free(depth);
    free(q1);
    free(q2);

}


//generates an integer maze from character maze
void get_intMaze2(int** Maze,char** maze,int N){
    int i,j;
    char c;
    for(i=0;i<N;i++)   
        for(j=0;j<N;j++)
        {
            c=maze[i][j];
            
            if(c=='#')
                Maze[i][j]=-1;
            else if(c=='B')
                Maze[i][j]=10;
            else if(c=='R')
                Maze[i][j]=50;
            else
                Maze[i][j]=0;
        }
        
}

//Nothing to do with my code.Added it as other groups use it in their engine
void Initialise2(int** Maze){
}
