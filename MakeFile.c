#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void makeFile();
float generateRandomNumber(int min,int max);

int main(){
    makeFile();
    return 0;
}
void makeFile(){
    int i=0;
    float x1=0.0;
    float x2=0.0;
    FILE *fp;
    fp=fopen("Dataset.txt","w");
    srand(time(NULL));
    for (i=0;i<150;i++){
        x1=generateRandomNumber(75,125);
        x2=generateRandomNumber(75,125);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<150;i++){
        x1=generateRandomNumber(0,50);
        x2=generateRandomNumber(0,50);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<150;i++){
        x1=generateRandomNumber(0,50);
        x2=generateRandomNumber(150,200);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<150;i++){
        x1=generateRandomNumber(150,200);
        x2=generateRandomNumber(0,50);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<150;i++){
        x1=generateRandomNumber(150,200);
        x2=generateRandomNumber(150,200);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<150;i++){
        x1=generateRandomNumber(0,200);
        x2=generateRandomNumber(0,200);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<75;i++){
        x1=generateRandomNumber(60,80);
        x2=generateRandomNumber(0,40);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<75;i++){
        x1=generateRandomNumber(60,80);
        x2=generateRandomNumber(160,200);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<75;i++){
        x1=generateRandomNumber(120,140);
        x2=generateRandomNumber(0,40);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    for (i=0;i<75;i++){
        x1=generateRandomNumber(120,140);
        x2=generateRandomNumber(160,200);
        fprintf(fp,"%f\t%f\n",x1,x2);
    }
    fclose(fp);
}
float generateRandomNumber(int min,int max){
    return (float)(rand()%(max + 1 - min)+ min)/100;
}
