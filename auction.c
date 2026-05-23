#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct players{
  char name[40];
  char country[30];
  int jersey;
  char position[20];
  int price;
 };

struct team{
  char teamname[30];
  int budget;
  char coach[20];
 };

struct bid{
  int jersey;
  char team[30];
  int amt;
 };

void Register();
void team();
void bid();
void results();
void viewteam();

int main()
{
  int choice;
  while(1){
  printf("========================================\n");
  printf("PLAYER AUCTION AND TEAM ALLOCATION SYSTEM\n");
  printf("\n==========================================");
  printf("\nYou can:\n");
  printf("1]Register a player\n");
  printf("2]Register a team\n");
  printf("3]Place a Bid\n");
  printf("4]View auction results\n");
  printf("5]View team squad\n");
  printf("6]Exit\n");
  printf("Make a choice!\n");
  scanf("%d",&choice);
   switch(choice){
      case 1: Register();
              break;
      case 2: team();
              break;
      case 3: bid();
              break;
      case 4: results();
              break;
      case 5: viewteam();
              break;
      case 6: exit(0);

     default: printf("Invalid choice\n");
   }

}
}

void Register()
{
   struct players p;
   int n,roles,ch;
   printf("enter the number players to Register:\n");
   scanf("%d",&n);
   for(int i=0;i<n;i++){
   printf("----Register a Player----\n");
   printf("Enter player's name: \n");
   scanf("%s",p.name);

   printf("Enter player's country:\n");
   scanf("%s",p.country);

   printf("Enter jersey number of player:\n");
   scanf("%d",&p.jersey);

   printf("Choose position For the player:\n");
   printf("Available positions:\n");
   printf("1.Batsman 2.Bowler 3.All-Rounder 4.Wicket-Keeper\n");
   printf("make a choice: \n");
   scanf("%d",&ch);
   switch(ch){
   case 1:
       strcpy(p.position,"Batsman");
       break;
   case 2:
       strcpy(p.position,"Bowler");
       break;
   case 3:
       strcpy(p.position,"All-Rounder");
       break;
   case 4:
       strcpy(p.position,"Wicket Keeper");
       break;
   default:
       printf("Invalid position!\n");
       return;
   }

   printf("Enter Base Price of player (in Lakhs):\n");
   scanf("%d",&p.price);
   if(p.price<=0){
     printf("Enter price valid price\n");
     return;
    }


   FILE *fptr=fopen("players.csv","a");
   if(fptr==NULL){
      printf("Error saving player\n");
      return;
    }
fprintf(fptr,"%s|%s|%d|%s|%d\n",p.name,p.country,p.jersey,p.position,p.price);
 }
   printf("players registered!\n");
}

void team(){

  struct team t;
  int n;

  printf("enter number of teams:\n");
  scanf("%d",&n);
  for(int i=0;i<n;i++){
  printf("----teams registration----\n");
  printf("enter team name:\n");
  scanf("%s",t.teamname);

  printf("enter team budget:\n");
  scanf("%d",&t.budget);

  printf("enter coach name:\n");
  scanf("%s",t.coach);

  FILE *fp= fopen("teams.csv","a");
  if(fp==NULL){
    printf("error saving team\n");
    return;
   }
  fprintf(fp,"%s|%d|%s\n",t.teamname,t.budget,t.coach);
  }
  printf("teams registered!\n");
}

void bid(){

  struct bid b;
  int n;
  printf("enter number of players to bid\n");
  scanf("%d",&n);
  for(int i=0;i<n;i++){
  printf("----AUCTION STARTS----\n");
  printf("Enter player's jersey number\n");
  scanf("%d",&b.jersey);

  printf("enter team name:\n");
  scanf("%s",b.team);

 printf("Enter bid amount\n");
 scanf("%d",&b.amt);

 FILE *fptr=fopen("bids.csv","a");
 if(fptr==NULL){
     printf("No bids have been made yet!\n");
     return;
 }

 fprintf(fptr,"\n%d|%s|%d\n",b.jersey,b.team,b.amt);
 }
 printf("Bid saved!\n");

}

void results(){
 FILE *fp=fopen("bids.csv","r");
 if(fp==NULL){
     printf("No players added yet\n");
     return;
     }

 char line[100];

  printf("\n-----AUCTION RESULTS-----\n");
  while(fgets(line,sizeof(line),fp))
    {
     printf(" %s\n",line);
   }
}

void viewteam()
{
  char tname[30];
  printf("enter team name: \n");
  scanf("%s",tname);

  FILE *fptr=fopen("bids.csv","r");
  if(fptr==NULL){
    printf("no bids placed yet\n");
    return;
  }

printf("\n=======SQUAD=======\n");
int total= 0;
int found= 0;

int bjersey,bamt;
char bteam[30];

while(fscanf(fptr,"%d|%[^|]|%d\n",&bjersey,bteam,&bamt)==3){
    if(strcmp(bteam,tname)==0){
       printf("jersey: %d | bid: %d lakhs|\n",bjersey,bamt);
       total+=bamt;
       found=1;
     }
   }
 if(found==0)
    printf("no players bought yet\n");
    else
    printf("total spent:%d lakhs\n",total);
}

