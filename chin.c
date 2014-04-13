#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 256
#define PAGE_LENGTH 999999

int main(int argc, char *argv[]){

	/* Disables line buffering */
	setbuf(stdout, NULL);

	/* Gets location of home folder */
	char *home = getenv("HOME");
	char text[LENGTH]={},buff[LENGTH]={},postnum[LENGTH];

	/* Checks for presence of arguments */
	if(argc<=2){
		printf(
			"Usage: chin URL DIR\n\nDownloads images off specified 4chan thread to ~/chin/DIR\n");
		return 0;
	} 
	/* Writes second argument to 'text' */
	strcat(text,argv[1]);  

	int j=0,thrlen=strlen(text),i,count=0;
	
	
	/*I don't like those two blocks, will replace them sometime in the future */	
		
		/* Extracts thread number and writes it to 'postnum' */
		i=thrlen-1;
		while (text[i]!='/'){
			count++;
			i--;
		} 
		i=0;
		while (count>=0){
			postnum[i]=text[thrlen-count];
			i++;
			count--;
		}
		
		 /* Extracts board's name */
		char boardname[LENGTH]={};
		j=strlen(postnum);
		i=thrlen-6-j;
		count=0;
		while (text[i]!='/')
		{
			count++;
			i--;
		}
		i=0; 
		while (count-1>=0){
			boardname[i]=text[thrlen-count-j-5];
			i++;
			count--;
		}
		
	printf("\nDownloading thread  #%s on /%s/, please wait...",postnum,boardname); 
	
	/* Forms initial wget command */
	sprintf(buff,"wget -N -q -P %s/chin/%s/ ", home, argv[2]); 
 
	/* Appends thread link to the end of wget command */
	strcat(buff,text);     

	/* Appends .json to the end, part of API integration */
	strcat(buff,".json");
	
	/* Downloads page using resulting wget command */
	system(buff);

	/* Writes path to downloaded file to 'buff' */
	sprintf(buff,"%s/chin/%s/%s.json",home, argv[2], postnum);

	/* Opens downloaded file */
	FILE *f=fopen(buff,"r"); 
	
	/* Writes entire file to char array 'whole' */
	char whole[PAGE_LENGTH];
	fgets(whole,PAGE_LENGTH,f);
	
	char wget[LENGTH]={};
	char extension[LENGTH]={};
	char imagenumber[LENGTH]={};

	/* i is starting offset */
	i=10;

	/* Resets counter */
	count=0;

	/* Writes path to download folder to 'buff' */
	sprintf(buff,"%s/chin/%s",home,argv[2]);
	
	/* Sign compare warning fix */
	thrlen=strlen(whole);
	
	while(i<thrlen){ 
		/* Looks for '"ext":' */
		if(whole[i-7]=='"'
		&& whole[i-6]=='e'
		&& whole[i-5]=='x'
		&& whole[i-4]=='t'
		&& whole[i-3]=='"'
		&& whole[i-2]==':'
		&& whole[i-1]=='"')
		{	
			/* Dirty webm workaround */			
			extension[4]='\0';
			
			while(whole[i+j]!='"'){
				extension[j]=whole[i+j];
				j++;
			}
			j=0;
		}
		
		/* Looks for '"tim":' */
		if(whole[i-6]=='"'
		&& whole[i-5]=='t'
		&& whole[i-4]=='i'
		&& whole[i-3]=='m'
		&& whole[i-2]=='"'
		&& whole[i-1]==':')
		{
			/* Writes image's number to 'imagenumber' */
			while(whole[i+j]!=','){
				imagenumber[j]=whole[i+j];
				j++;
			}
			
			/* Downloads the image */
			count++;
			printf("\nDownloading image %d: i.4cdn.org/%s/src/%s%s...",count,boardname,imagenumber,extension);
			sprintf(wget,"wget -nc -P %s -q i.4cdn.org/%s/src/%s%s",buff,boardname,imagenumber,extension);
			system(wget);
			printf(" Done!");
			i+=180;
		}	
		i++;j=0;
	}
	printf("\nTotal images downloaded: %d\n", count);
	return 0;
}
