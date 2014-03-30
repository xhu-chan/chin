#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 256
#define PAGE_LENGTH 999999

int main(int argc, char *argv[]){

	//Disable line buffering
	setbuf(stdout, NULL); 

	//Get location of home folder
	char *home = getenv("HOME"); 


	char text[LENGTH]={},buff[LENGTH]={},postnum[LENGTH];

	//Check for presence of arguments
	if(argc<=2){
		printf(
			"Usage: chin URL DIR\n\nDownloads images off specified 4chan thread to ~/chin/DIR\n");
		return 0;
	} 

	//Forms initial wget command without the link to thread
	sprintf(buff,"wget -N -q -P %s/chin/ ", home); 

	//Writes first argument (download link) to 'text'
	strcat(text,argv[1]);   

	// Appends download link to the end of wget command
	strcat(buff,text);     

	int j=0,thrlen=strlen(text),i,count=0;
	i=thrlen-1;

	//Counts amount of symbols before '/',
	//resulting amount is thread number's length
	while (text[i]!='/'){
		count++;
		i--;
	} 
	i=0;

	//Extracts thread number and writes it to 'postnum'
	while (count>=0){
		postnum[i]=text[thrlen-count];	
		i++;
		count--;
	}

	printf("\nThe thread number is: %s",postnum); 

	//Downloads page source using resulting wget command
	system(buff); 

	printf("\nThe page source has been (hopefully) downloaded. Please wait...");

	//Writes path to downloaded file to 'buff'
	sprintf(buff,"%s/chin/%s",home,postnum); 

	//Opens downloaded file
	FILE *f=fopen(buff,"r");		 

	//Writes entire file to char array 'whole'
	char whole[PAGE_LENGTH];
	fgets(whole,PAGE_LENGTH,f); 

	//Removes webpage file
	sprintf(buff,"rm %s/chin/%s",home,postnum);
	system(buff);

	//Default link length is 34 symbols long
	char link[34]={},old_link[34]={};
	char wget[LENGTH]={};

	//i is starting offset in page's HTML code, to be changed
	i=20;
						
	//Resets counter 
	count=0; 

	//Writes path to download folder to 'buff'
	sprintf(buff,"%s/chin/%s",home,argv[2]);
	 
	 
	while(i<strlen(whole)){
		
		//Looks for i.4cdn in webpage's source
		if(  whole[i]=='i' 
		&& whole[i+1]=='.' 
		&& whole[i+2]=='4' 
		&& whole[i+3]=='c' 
		&& whole[i+4]=='d' 
		&& whole[i+5]=='n')
		{ 
			//Writes previous image's URL to 'old_link'
			sprintf(old_link,"%s",link);
			
			//Writes image's URL to 'link'	
			while(whole[i+j]!='"'){
				link[j]=whole[i+j];
				j++;
			}
				
			//Checks if download link is different from previous one 
			//to prevent downloading same image twice in a row
			//and then downloads it
			if(strcmp(old_link,link)!=0){
				count++;
				printf("\nDownloading image %d: %s...",count,link);
				sprintf(wget,"wget -nc -P %s -q %s ",buff,link);
				system(wget);
				printf(" Done!");
				i+=strlen(link);
			} 
		}	
		i++;j=0;
	}
	printf("\nTotal images downloaded: %d\n", count);
	return 0;
}
