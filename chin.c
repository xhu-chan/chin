#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 256
#define PAGE_LENGTH 999999

int main(int argc, char *argv[]){
setbuf(stdout, NULL); //Disables line buffering
char *home = getenv("HOME"); 
char text[LENGTH]={},buff[LENGTH]={},postnum[LENGTH];
if(argc<=1){printf("Usage: chin [URL] [DIR]\n\nDownloads images off specified 4chan thread to ~/chin/[DIR]\nUses thread number as default directory name\n");return 0;} else
sprintf(buff,"wget -N -q -P %s/chin/ ", home);
{strcat(text,argv[1]);
strcat(buff,text); 
int j=0,thrlen=strlen(text),i,count=0;	i=thrlen-1;
while (text[i]!='/'){count++;i--;} i=0;
while (count>=0){
	postnum[i]=text[thrlen-count];
	i++;count--;
	}

printf("\nThe thread number is: %s",postnum); 

	system(buff); //Downloads page source

printf("\nThe page source has been (hopefully) downloaded. Please wait...");
sprintf(buff,"%s/chin/%s",home,postnum); //buff is a path to download directory now
FILE *f=fopen(buff,"r");
char whole[PAGE_LENGTH];fgets(whole,PAGE_LENGTH,f); //length of page, to be changed
char link[LENGTH]={};char wget[LENGTH]={},link2[LENGTH]={};
i=20;					//Starting offset, to be changed
int total=0; 

if (argv[2]!=NULL) sprintf(buff,"%s/chin/%s",home,argv[2]); //Changes download folder according to second argument
while(i<strlen(whole)){
	if(whole[i]=='i' && whole[i+1]=='.' && whole[i+2]=='4' && whole[i+3]=='c' && whole[i+4]=='d' && whole[i+5]=='n'){ //looks for i.4cdn in webpage's source
			sprintf(link2,"%s",link);
		while(whole[i+j]!='"'){
			link[j]=whole[i+j];
			j++;
			}if(strcmp(link2,link)!=0){total++;printf("\nDownloading image %d: %s",total,link);sprintf(wget,"wget -nc -P %s -q %s ",buff,link);printf("..."); system(wget); printf(" Done!"); i+=strlen(link);} 
		}
	i++;j=0;
	}
printf("\nTotal images downloaded: %d\n", total);
if (argv[2]!=NULL) {sprintf(buff,"rm %s/chin/%s",home,postnum);system(buff);} //Removes webypage file if custom folder name is used
return 0;
}
}
