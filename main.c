#include<stdio.h>
#include<conio.h>
#include<process.h>
#include <windows.h>
#include <stdlib.h>

int i,j,ec,fg,ec2;
char fn[20],e,c;
FILE *fp1,*fp2,*fp;
void Kaydet();
void kaydetdosya();
void Duzenle();
void DosyaSil();
void Goruntule();
void gotoXY(int x, int y);
void getCursorXY(int *x, int *y);
void yazdir();
void ekle(char harfAl,int x,int y);
void XYsizEkle(char harfAl);
void silme(int x, int y);
void bosalt();

typedef struct list{
    char harf;
    struct list *sonraki;
    struct list *onceki;
    int x_ko;
    int y_ko;
    int elemansirasi;
}Kelime;
    Kelime *bas = NULL,*son = NULL;
int elemanSayisi=0;


void main(){
 do {
  system("cls");
  printf("\n\t\t***** TEXT EDITOR *****");
  printf("\n\n\tMENU:\n\t-----\n ");
  printf("\n\t1.KAYDET\n\t2.GORUNTULE\n\t3.DUZENLE\n\t4.SIL\n\t5.CIK\n");
  printf("\n\tSecimini gir: ");
  scanf("%d",&ec);
  switch(ec)
  {
   case 1:
     Kaydet();
     bosalt();
     break;
   case 2:
     Goruntule();
     bosalt();
     break;
   case 3:
     Duzenle();
     bosalt();
     break;
   case 4:
     DosyaSil();
     break;
   case 5:
     exit(0);
  }
 }while(1);
}

void yazdir(){
    system("cls");
    Kelime *gecici=bas;
    Kelime *gecici1=bas;
    Kelime *enBuyuk=bas;
    while(gecici!=NULL)
    {
        gotoXY(gecici->x_ko,gecici->y_ko);
        printf("%c",gecici->harf);
        gecici=gecici->sonraki;

    }
    while(gecici1!=NULL){
        if(enBuyuk->elemansirasi < gecici1->elemansirasi){
            enBuyuk=gecici1;
        }
        gecici1=gecici1->sonraki;
    }
    gotoXY(enBuyuk->x_ko+1,enBuyuk->y_ko);

}

void silmeyazdir(int silmex,int silmey){
    system("cls");
    Kelime *gecici=bas;
    while(gecici!=NULL)
    {
        gotoXY(gecici->x_ko,gecici->y_ko);
        printf("%c",gecici->harf);
        gecici=gecici->sonraki;

    }
    gotoXY(silmex,silmey);

}

void ekle(char harfAl,int x,int y){

    int i=0,j=0;
    Kelime *yeni= (struct list*) malloc (sizeof (struct list));
    Kelime *gecici=bas;
    Kelime *gecici1=bas;
    yeni->harf=harfAl;
    yeni->elemansirasi=elemanSayisi;
    elemanSayisi++;

    if(bas==NULL)
    {
        yeni->onceki=NULL;
        bas=yeni;
        son=yeni;
        son->sonraki=NULL;
        son->onceki=NULL;
        bas->x_ko=0;
        bas->y_ko=0;

    }

    else if(x==0 && y==0)
    {

        yeni->sonraki=bas;
        bas->onceki=yeni;
        bas= yeni;
        bas->onceki=NULL;
        son->sonraki=NULL;

    }



    else
    {
        int kontrol=0;
        while(gecici!=NULL)
        {
            gecici->x_ko=i%80;
            gecici->y_ko=i/80;
            if(gecici->x_ko==x && gecici->y_ko==y)
            {
                yeni->onceki=gecici->onceki;
                gecici->onceki->sonraki=yeni;
                gecici->onceki=yeni;
                yeni->sonraki=gecici;
                bas->onceki=NULL;
                son->sonraki=NULL;
                kontrol=1;
            }
            gecici=gecici->sonraki;
            i++;
        }
        if(kontrol==0){

            yeni->onceki=son;
            son->sonraki=yeni;
            son= yeni;
            bas->onceki=NULL;
            son->sonraki=NULL;

        }
    }
    while(gecici1!=NULL){

        gecici1->x_ko=j%80;
        gecici1->y_ko=j/80;
        gecici1=gecici1->sonraki;
        j++;


    }

    yazdir();

}

void bosalt(){
    Kelime *gecici=bas;
    while(gecici){
        Kelime *gecici1=gecici->sonraki;
        free(gecici);
        gecici=gecici1;
    }
    bas=NULL;
    son=NULL;
}

void silme(int x, int y){

    int i=0;
    Kelime *sil= (struct list*) malloc (sizeof (struct list));
    Kelime *gecici=bas;
    Kelime *gecici1=bas;
    int silmex=x;
    int silmey=y;

    while(gecici!=NULL){

        if(gecici->x_ko==x && gecici->y_ko==y){
            sil = gecici;
            gecici = gecici->onceki;
            gecici->sonraki = sil->sonraki;
            sil->sonraki->onceki = gecici;
            free(sil);
        }
        else{
            gecici=gecici->sonraki;

        }

    }

    while(gecici1!=NULL){

        gecici1->x_ko=i%80;
        gecici1->y_ko=i/80;
        gecici1=gecici1->sonraki;
        i++;

    }

   silmeyazdir(silmex,silmey);
}

void gotoXY(int x, int y) {
	HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position={x, y};

    SetConsoleCursorPosition(Screen, Position);

}

void getCursorXY(int *x, int *y) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;


	}
}

void kaydetdosya(){
      int i=0;
      char ch;
      Kelime *gecici=bas;
      fp1=fopen("temp.txt","w");
      while(gecici!=NULL){
        fputc(gecici->harf,fp1);
        gecici=gecici->sonraki;
        i++;
      }

       fclose(fp1);
       printf("\n\tDosya Adini Gir: ");
       scanf("%s",fn);
       strcat(fn,".txt");
       fp1=fopen("temp.txt","r");
       fp2=fopen(fn,"w");
       while((c = getc(fp1)) != EOF)
       {
        putc(c,fp2);
       }
       fclose(fp2);

}

void Kaydet(){
 int x=0,y=0,kontrol=0;
 system("cls");
 while(1)
 {

    c=_getch();
    getCursorXY(&x,&y);
    if(c==','){
        getCursorXY(&x,&y);
        silme(x,y);
    }
    else if(GetAsyncKeyState(VK_DOWN)){
        if(kontrol==0){
            gotoXY(x,y+1);
            getCursorXY(&x,&y);
            if(y>son->y_ko){
                gotoXY(son->x_ko,son->y_ko);
            }

        }
        kontrol++;
        if(kontrol==2){
            kontrol=0;
        }

    }
    else if(GetAsyncKeyState(VK_UP)){
        if(kontrol==0){
           gotoXY(x,y-1);
           getCursorXY(&x,&y);
        }
        kontrol++;
        if(kontrol==2){
            kontrol=0;
        }

    }
    else if(GetAsyncKeyState(VK_LEFT)){
            if(kontrol==0){
                gotoXY(x-1,y);
                getCursorXY(&x,&y);
                if(x==0){
                    gotoXY(79,y-1);
                }
            }
            kontrol++;
            if(kontrol==2){
                kontrol=0;
            }


    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        if(kontrol==0){
           gotoXY(x+1,y);
            getCursorXY(&x,&y);
            if(x==79){
                gotoXY(0,y+1);
            }
        }
        kontrol++;
        if(kontrol==2){
            kontrol=0;
        }

    }
    else{
       ekle(c,x,y);
    }

    if(c=='.'){
        kaydetdosya();
        break;
    }
 }

}

void XYsizEkle(char harfAl){

    int i=0;
    Kelime *yeni= (struct list*) malloc (sizeof (struct list));
    Kelime *gecici=bas;
    yeni->harf=harfAl;
    yeni->elemansirasi=elemanSayisi;
    elemanSayisi++;

    if(bas==NULL)
    {
        yeni->onceki=NULL;
        bas=yeni;
        son=yeni;
        son->sonraki=NULL;
        son->onceki=NULL;
        elemanSayisi++;
        bas->x_ko=0;
        bas->y_ko=0;

    }

    else{

        yeni->onceki=son;
        son->sonraki=yeni;
        son= yeni;
        bas->onceki=NULL;
        son->sonraki=NULL;
        elemanSayisi++;

    }
    while(gecici!=NULL){

        gecici->x_ko=i%80;
        gecici->y_ko=i/80;
        gecici=gecici->sonraki;
        i++;
    }


}

void Goruntule(){
  printf("\n\tDosya adini gir: ");
  scanf("%s",fn);
  strcat(fn,".txt");
  fp1=fopen(fn,"r");
  if(fp1==NULL)
  {
   printf("\n\tDosya Bulunamadi!");
   goto end1;
  }
  while((c = getc(fp1)) != EOF)
  {
   XYsizEkle(c);
  }
  yazdir();
end1:
  fclose(fp1);
  printf("\n\n\tDevam etmek icin bir tusa basiniz...");
  getch();

}

void DosyaSil(){
  printf("\n\tDosya Adini Giriniz: ");
  scanf("%s",fn);
  strcat(fn,".txt");
  fp1=fopen(fn,"r");
  if(fp1==NULL)
  {
   printf("\n\tDosya bulunamadi!");
   goto end2;
  }
  fclose(fp1);
  if(remove(fn)==0)
  {
   printf("\n\n\tDosya Basarili Bir Sekilde Silindi!");
   goto end2;
  }
  else
   printf("\n\tHata!\n");
end2:
  printf("\n\n\tDevam etmek icin bir tusa basiniz...");
  getch();
}

void Duzenle(){

  printf("\n\tDosya adini gir: ");
  scanf("%s",fn);
  strcat(fn,".txt");
  fp1=fopen(fn,"r");
  system("cls");
  if(fp1==NULL)
  {
   printf("\n\tDosya Bulunamadi!");
   goto end1;
  }
  while((c = getc(fp1)) != EOF)
  {
   XYsizEkle(c);
  }
    yazdir();
  fclose(fp1);

     int x=0,y=0,kontrol=0;
     while(1)
     {

        c=_getch();
        getCursorXY(&x,&y);
        if(c==','){
            getCursorXY(&x,&y);
            silme(x,y);
        }
        else if(GetAsyncKeyState(VK_DOWN)){
            if(kontrol==0){
                gotoXY(x,y+1);
                getCursorXY(&x,&y);
                if(y>son->y_ko){
                    gotoXY(son->x_ko,son->y_ko);
                }

            }
            kontrol++;
            if(kontrol==2){
                kontrol=0;
            }

        }
        else if(GetAsyncKeyState(VK_UP)){
            if(kontrol==0){
               gotoXY(x,y-1);
               getCursorXY(&x,&y);
            }
            kontrol++;
            if(kontrol==2){
                kontrol=0;
            }

        }
        else if(GetAsyncKeyState(VK_LEFT)){
                if(kontrol==0){
                    gotoXY(x-1,y);
                    getCursorXY(&x,&y);
                    if(x==0){
                        gotoXY(79,y-1);
                    }
                }
                kontrol++;
                if(kontrol==2){
                    kontrol=0;
                }


        }
        else if(GetAsyncKeyState(VK_RIGHT)){
            if(kontrol==0){
               gotoXY(x+1,y);
                getCursorXY(&x,&y);
                if(x==79){
                    gotoXY(0,y+1);
                }
            }
            kontrol++;
            if(kontrol==2){
                kontrol=0;
            }

        }
        else{
           ekle(c,x,y);
        }

        if(c=='.'){
            kaydetdosya();
            break;
        }
     }
 end1:
     printf("\n\n\tDevam etmek icin bir tusa basiniz...");
     getch();
}
