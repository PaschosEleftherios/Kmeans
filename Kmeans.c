#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define M 9 // Number of centers to represent each team.

struct point{
    float x1;
    float x2;
    int team;
    int previousTeam;

};


void readFile();//Reads the Dataset from the file and stores it into an Array of point Structs.
void randomCenters();//Chooses randomly the first centers.
void setFirstTeams();//Initiate the fields of the struct.

//The next two functions basically implement
//the K-Means Algorithm
void makeTeams();//Sets every point to a team
void setNewCenters();//Finds the location of the new centers

void computeError();

struct point points[1200];//Here we store the points of the Dataset
struct point centers[M];//Here we store the Centers.
int flag = 1;//Flag to know when we are ready to stop.
int teamCount[M];//How many points has each time.
float pointSumX1[M];//Sum of  "x1" points. 
float pointSumX2[M];//Sum of  "x1" points. 
float sfalma =0.0;

int main(){
    int i;
    FILE *fp;
    fp=fopen("Centers.txt","w");
    int times=0;
    readFile();
    randomCenters();
    setFirstTeams();
    while(flag==1){
        flag=0;
        makeTeams();
        setNewCenters();
        times++;
        printf("Changed Centers for %d times.\n",times);
    }
    computeError();
    printf("Found Error %f after changing Centers %d times.\n",(float)sfalma/1200,times);
    for(i=0;i<M;i++){
        fprintf(fp,"%f",centers[i].x1);
        fprintf(fp,"%f\n",centers[i].x2);
    }fclose(fp);
    fp=fopen("Teams.txt","w");
    for(i=0;i<1200;i++){
        fprintf(fp,"%d\n",points[i].team);
    }fclose(fp);
    return 0;
}

void readFile(){
    int i;
    FILE *fp;
    fp=fopen("Dataset.txt","r");
    for(int i=0;i<1200;i++){
        fscanf(fp,"%f",&(points[i].x1));
        fscanf(fp,"%f",&(points[i].x2));
    }
    fclose(fp);
}
void randomCenters(){
    int randomPoint;
    srand(time(NULL));
    for(int i=0;i<M;i++){
        randomPoint=rand()%1201;
        centers[i].x1=points[randomPoint].x1;
        centers[i].x2=points[randomPoint].x2;
    }
}

void setFirstTeams(){
    for(int i=0;i<1200;i++){
        points[i].team=-1;
        points[i].previousTeam=-2;
    }
}

void makeTeams(){
    int i,j,teamSelected;
    float min =100.0,sum=0.0,distance=0.0;
    for(i=0;i<1200;i++){
        for(j=0;j<M;j++){
            distance = sqrt(pow(centers[j].x1-points[i].x1,2)+pow(centers[j].x2-points[i].x2,2));
            if(distance<min){
                points[i].team=j;
                min=distance;
            }
        }if(points[i].team!=points[i].previousTeam){
            flag=1;
        }
        points[i].previousTeam=points[i].team;
        min=100.0;
    }
}

void setNewCenters(){
    int i,j;
    for(i=0;i<M;i++){
        pointSumX1[i]=0.0;
        pointSumX2[i]=0.0;
        teamCount[i]=0;
    }
    for (i=0;i<1200;i++){
        teamCount[points[i].team]++;
        pointSumX1[points[i].team]+= points[i].x1;
        pointSumX2[points[i].team]+= points[i].x2;
    }
    for (i=0;i<M;i++){
        centers[i].x1=pointSumX1[i]/teamCount[i];
        centers[i].x2=pointSumX2[i]/teamCount[i];
    }
}

void computeError(){
    int i;
    for (i=0;i<1200;i++){
        sfalma += sqrt(pow(centers[points[i].team].x1-points[i].x1,2)+pow(centers[points[i].team].x2-points[i].x2,2));
    }
}
