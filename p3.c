#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define M 9 //Teams that will be created by K-Means.
#define dimension 2 //dimension of the points of the dataset.
#define datasetValues 1200 //How many points on the dataset.

float datasetArray[datasetValues][dimension];//The values of the Dataset stored in an array.
float centersArray[M][dimension];//The center for every Team.
int whichTeam[datasetValues];//We will store here,the theam that  belongs every value on the dataset.
int teamChanged = 1;//flag to count the team changes.


void createDatasetII();
void createDatasetArray();
void createFirstCenters();
void Kmeans();
void calculateSfalmaOmadopoihshs();



int main(){
    createDatasetII();
    createDatasetArray();
    createFirstCenters();
    do{//while loop until no point changes team.
        teamChanged =0;
        Kmeans();
    }while(teamChanged);
    calculateSfalmaOmadopoihshs();
}


void createDatasetII(){
//Create the Dataset 2.
    int i=0;
    FILE *fp;
    fp = fopen("DatasetII","w");//Make the file of the Dataset
    srand(time(NULL));
    for (i=0;i<150;i++){
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (125 + 1 - 75) + 75)/100, (double)((rand() % (125 + 1 - 75) + 75))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (50 + 1 - 0) + 0)/100, (double)((rand() % (50 + 1 - 0) + 0))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (50 + 1 - 0) + 0)/100, (double)((rand() % (200 + 1 - 150) + 150))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (200 + 1 - 150) + 150)/100, (double)((rand() % (50 + 1 - 0) + 0))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (200 + 1 - 150) + 150)/100, (double)((rand() % (200 + 1 - 150) + 150))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (200 + 1 - 0) + 0)/100, (double)((rand() % (200 + 1 - 0) + 0))/100);
    }
    for (i=0;i<75;i++){
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (80 + 1 - 60) + 60)/100, (double)((rand() % (40 + 1 - 0) + 0))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (80 + 1 - 60) + 60)/100, (double)((rand() % (200 + 1 - 160) + 160))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (140 + 1 - 120) + 120)/100, (double)((rand() % (40 + 1 - 0) + 0))/100);
        fprintf(fp,"%1.3f %1.3f\n", (double)(rand() % (140 + 1 - 120) + 120)/100, (double)((rand() % (200 + 1 - 160) + 160))/100);
    }   
    fclose(fp);  
    
    
}

void createFirstCenters(){
    //Choose which points of the given Dataset will be the first random centers.
    int i=0,j=0,randomChoice;

    srand(time(NULL));
    for (i=0;i<M;i++){
        randomChoice = rand()%datasetValues;
        for (j=0;j<dimension;j++){
            centersArray[i][j]=datasetArray[randomChoice][j];
        }
    }
}

void createDatasetArray(){
    //Create an array with all the values of the datasetII.
    FILE *fp;
    int i,j;
    fp=fopen("DatasetII","r");
    for (i=0;i<datasetValues;i++){
        for (j=0;j<dimension;j++){
            fscanf(fp,"%f",&datasetArray[i][j]);
        }
    }
    fclose(fp);
}

void Kmeans(){
    //Mach every point in a team.
    int i,j,k;
    float newTeam,min,sum;
    int howManyInTeam[M] = {0};
    float sumArray[M][dimension] = {0};
    for (i=0;i<datasetValues;i++){//for every point.
        min=10000000;
        for (j=0;j<M;j++){//for every team-center. Find the Distance of the point from every center 
            sum=0;
            for (k=0;k<dimension;k++){
                sum += pow(centersArray[j][k]-datasetArray[i][k],2);
            }
            if(sqrt(sum)<min){
                min=sqrt(sum);
                newTeam = j;
            }
        }
        if(whichTeam[i]!=newTeam){
            teamChanged=1;
            whichTeam[i]=newTeam;
        }
    }//find new centers
    for (i =0;i<datasetValues;i++){
        howManyInTeam[whichTeam[i]]++;
        for (j=0;j<dimension;j++){
            sumArray[whichTeam[i]][j] +=   datasetArray[i][j];
        }
    }
    for (i =0;i<M;i++){
        for (j=0;j<dimension;j++){
            centersArray[i][j]= sumArray[i][j] / howManyInTeam[i];
        }
    }
}


void calculateSfalmaOmadopoihshs(){
    int i,j;
    float sfalma=0.0;
    for (i=0;i<datasetValues;i++){
        sfalma+=sqrt(pow(datasetArray[i][0]-centersArray[whichTeam[i]][0],2)+pow(datasetArray[i][1]-centersArray[whichTeam[i]][1],2));
    }
    sfalma = (float)sfalma/datasetValues;
    printf("Sfalma Omadopoihshs : %f\n",sfalma);
}