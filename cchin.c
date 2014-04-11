#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 256
#define PAGE_LENGTH 999999

int main(int argc, char *argv[]){
	
	char *home = getenv("HOME");
	
	if(argc<=2){
		printf("Usage: cchin URL DIR\n\nDownloads all images off specified 4chan board to ~/cchin/DIR.\nURL is a link to the board without / at end, I.E.  4chan.org/g\nDIR is directory name inside ~/cchin/\n");
		return 0;
	}
	
	
	int i=strlen(argv[1])-1,j=0;
		while (argv[1][i]!='/'){
		j++;
		i--;
	} 
	
	i=0;
	
	char boardname[LENGTH]={};
	while (j>=0){
		boardname[i]=argv[1][strlen(argv[1])-j];
		i++;j--;
	} 

	
	/* Downloads page's catalog to specific folder, TO BE CHANGED */
	char buff[LENGTH]={};
	sprintf(buff,"wget -N -q -P %s/cchin/%s %s/catalog",home,argv[2],argv[1]);
	system(buff); 
	
		
	char catalog[LENGTH]={};
	sprintf(catalog,"%s/cchin/%s/catalog",home,argv[2]);
	
	/* Opens catalog file, reads it into char array, removes it */
	char page[PAGE_LENGTH]={}; 
	FILE *f=fopen(catalog,"r"); 
	fgets(page,PAGE_LENGTH,f); 
	sprintf(buff,"rm %s",catalog); 
	system(buff); 

	char link[LENGTH]={};
	
	/* i is starting point at which cchin starts looking for thread numbers */
	i=5000;
	j=0; 

	while(i<strlen(page)){
		if(page[i]=='['&&page[i-1]==':'&&page[i-2]=='"'&&page[i-3]=='t')
			break;	
		i++;	
	} 
	while(i<strlen(page)){i++;
		
		while(page[i+j]!=','&&page[i+j]!=']'){
			link[j]=page[i+j];
			j++;
		}
		
		i+=j;
		j=0;
		sprintf(buff,"chin https://boards.4chan.org/%s/res/%s ../cchin/%s/%s",boardname, link,argv[2],link);
		system(buff);
		if(page[i]==']') 
			break;
	}

	return 0;
}
