#include <stdio.h>
#include <stdlib.h>
struct node{
    int row;
    int col;
    struct node *next;
    struct node *prew;
};
struct node* newNode(int i,int j){
    struct node* dugum=(struct node*)malloc(sizeof(struct node));
    dugum->row=i;
    dugum->col=j;
    dugum->next=NULL;
    dugum->prew=NULL;
    return dugum;
}
struct node* kok = NULL;
void addStack(struct node** kok,int i,int j){
    struct node* dugum= newNode(i,j);
    dugum->next=*kok;
    dugum->prew=NULL;
    *kok=dugum;
    printf("(%d,%d) yoluna sahip dugum eklendi\n",i+1,j+1);
}
int isEmpty(struct node *kok){
    return !kok;
}
void delStack(struct node** kok,int x,int y,int matris[x][y]){
    if(isEmpty(*kok)){
        printf("Cikis yolu yoktur!!\n");
        writeMatris(x,y,matris);
        return -1;
    }
    struct node* alinacak = *kok;
    *kok = (*kok)->next;
    //(*kok)->prew=*kok;
    int alinani = alinacak->row;
    int alinanj = alinacak->col;
    printf("(%d,%d) yoluna sahip dugum alindi\n",alinani+1,alinanj+1);
    free(alinacak);
}
void writeMatris(int x,int y,int matris[x][y]);
void isExit(int gX,int gY,int cX,int cY,int x,int y,int matris[x][y]);
void foundRotate(int x,int y,int matris[x][y],int gX,int gY,int cX,int cY);
int main()
{
        srand(time(NULL));
    int satir,sutun;
    hata0:
    printf("Matrisin satir sayisini girin:");
    scanf("%d",&satir);
    printf("Matrisin sutun sayisini girin:");
    scanf("%d",&sutun);
    if(satir>25 || sutun>25){
        printf("Lutfen satir ve sutun sayisini 25'ten buyuk girmeyin!\n");
        goto hata0;
    }
    int labirent[satir][sutun];
    int i,j;
    printf("      ");
    for(i=0;i<sutun;i++){
        printf("    %d",i+1);
    }
    printf("\n\n");
    for(i=0;i<satir;i++){
        printf("%-2d -->",i+1);
        for(j=0;j<sutun;j++){
            labirent[i][j]=rand()%2;
            printf("    %d",labirent[i][j]);
        }
        printf("    <-- %2d",i+1);
        printf("\n");
    }
    printf("\n\n");
    printf("      ");
    for(i=0;i<sutun;i++){
        printf("    %d",i+1);
    }
    printf("\n\n");
    int gX,gY;
    int cX,cY;
    printf("1'ler yol 0'lar duvardir!!\n");
    hata1:
    printf("Labirente satir giris degeri giriniz:");
    scanf("%d",&gX);
    gX--;
    printf("Labirente sutun giris degeri giriniz:");
    scanf("%d",&gY);
    gY--;
    if(labirent[gX][gY]==0){
        printf("Duvardan giremezsin!!\n");
        goto hata1;
    }
    hata3:
    printf("Labirente satir cikis degeri giriniz:");
    scanf("%d",&cX);
    cX--;
    printf("Labirente sutun cikis degeri giriniz:");
    scanf("%d",&cY);
    cY--;
    if(labirent[cX][cY]==0){
        printf("Duvardan cikamazsin!!\n");
        goto hata3;
    }
    printf("gX=%d\ngY=%d\ncX=%d\ncY=%d\n",gX,gY,cX,cY);
    /****/
    int index=(gX*sutun)+gY;
    labirent[gX][gY]=2;
    foundRotate(satir,sutun,labirent,gX,gY,cX,cY);
    return 0;
}
void foundRotate(int x,int y,int matris[x][y],int gX,int gY,int cX,int cY){
    isExit(gX,gY,cX,cY,x,y,matris);
     //sag
    if(matris[gX][gY+1] == 1)
    {
        matris[gX][gY+1]=2;
        addStack(&kok,gX,gY+1);
        foundRotate(x,y,matris,gX,gY+1,cX,cY);
    }
    //asagi
    if(matris[gX+1][gY] == 1)
    {
        matris[gX+1][gY]=2;
        addStack(&kok,gX+1,gY);
        foundRotate(x,y,matris,gX+1,gY,cX,cY);
    }
    //yukari
    if(matris[gX-1][gY] == 1)
    {
        matris[gX-1][gY]=2;
        addStack(&kok,gX-1,gY);
        foundRotate(x,y,matris,gX-1,gY,cX,cY);
    }
    //sol
    if(matris[gX][gY-1] == 1)
    {
        matris[gX][gY-1]=2;
        addStack(&kok,gX,gY-1);
        foundRotate(x,y,matris,gX,gY-1,cX,cY);
    }
    if(matris[gX+1][gY] != 1 && matris[gX][gY+1] != 1 && matris[gX-1][gY] != 1 && matris[gX][gY-1] != 1)
    {
        matris[gX][gY]=3;
        delStack(&kok,x,y,matris);
    }
}
void isExit(int gX,int gY,int cX,int cY,int x,int y,int matris[x][y]){
    if(gX==cX && gY==cY){
        printf("Cikisa geldin!\n");
        writeMatris(x,y,matris);
    }
}
void writeMatris(int x,int y,int matris[x][y]){
    /**Matrisin yollu hali**/
    int i,j;
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            printf("%5d",matris[i][j]);
        }
        printf("\n");
    }
    exit(1);
}
