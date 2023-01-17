#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitTab(int tab[][5]){

    int l, c;
    for(l=0; l<5;l++){

        for(c=0; c<5;c++){
            tab[l][c] = -1;
        }
    }
}
void ShowTab(int tab[][5]){

    int l, c;

    printf("\t1 \t2 \t3 \t4 \t5");
    printf("\n");
    for(l=0; l<5; l++){
        printf("%d",l+1);
        for(c=0; c<5; c++){

            if(tab[l][c] == -1){

                printf("\t~");
            }else if(tab[l][c] == 0){
                printf("\t*");
            }else if(tab[l][c] == 1){
                printf("\tX");
            }
        }
        printf("\n");
    }

}
void InitShips(int ships[][2]){
    srand(time(NULL));
    int ship, before; // before
    for(ship=0; ship < 3; ship++){
        ships[ship][0] = rand()%5;
        ships[ship][1] = rand()%5;

        for(before = 0; before < ship; before ++){

            if((ships[ship][0] ==ships[before][0]) &&(ships[ship][1] == ships[before][1]))
            do{
                ships[ship][0] = rand()%5;
                ships[ship][1] = rand()%5;
            }while( (ships[ship][0] == ships[before][0])&&(ships[ship][1] == ships[before][1]) );
        }
    }
}
void Shot(int shot[2]){

    printf("Line: ");
    scanf("%d",&shot[0]);
    shot[0] --;

    printf("column: ");
    scanf("%d",&shot[1]);
    shot[1] --;
}

int Hit(int shot[2], int ships[][2]){

    int ship;
    for(ship = 0; ship < 3; ship++){
        if(shot[0] == ships[ship][0] && shot[1] == ships[ship][1]){

            printf("You hit the shot (%d,%d)\n",shot[0]+1,shot[1]+1);
            return 1;

        }
    }
    return 0;

}
void Tip(int shot[2], int ships[][2], int tentativa )
{
    int l = 0, c = 0, queue;

    for(queue=0; queue <3; queue++){
        if(ships[queue][0] == shot[0]) l ++;
        if(ships[queue][1] == shot[1]) c ++;

    }
    printf("\n Tip %d: \n Line %d -> %d Ships\nColumn %d -> %d Ships\n",tentativa,shot[0]+1, l,shot[1]+1,c);


}
void ChangeTab(int shot[2], int ships[][2], int tab[][5]){

    if(Hit(shot, ships))
        tab[shot[0]][shot[1]]=1;
    else
        tab[shot[0]][shot[1]]=0;

}

int main(){

    printf("============================================================================\n");
    printf("Welcome To Battle Ships\n");
    printf("============================================================================\n");
    printf("\n");
    printf("LEGENDA\n ");
    printf(" ~ : Water on the block. No shot yet\n");
    printf(" * : Shot given, there's nothing there.\n");
    printf(" x : Shot given, there was a ship there.  \n");


    int tab[5][5];
    int ships[3][2];
    int shot[2];
    int tentativas=0, hits=0;

    InitTab(tab);
    InitShips(ships);
    printf("\n");

    do{
        ShowTab(tab);
        Shot(shot);
        tentativas++;

        if(Hit(shot,ships)){
            Tip(shot,ships,tentativas);
            hits++;
        }else
            Tip(shot,ships,tentativas);
        ChangeTab(shot,ships,tab);

    }while(hits!=3);

    printf("\n\n Finished, You hit all 3 ships in %d attempts",tentativas);
    ShowTab(tab);



    return 0;
}