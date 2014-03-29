#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 256
#define PAGE_LENGTH 999999
// EXAMPLE OF THREAD "2196658":{"date":1395996371,"r":16,"i":15,"lr":{"id":2197052,"date":1396050694,"author":"Anonymous"},"author":"Anonymous","imgurl":"1395996371777","tn_w":250,"tn_h":187,"sub":"Shirasaka Koume thread","teaser":"Happy birthday Koume-chan !"}
int main(int argc, char *argv[]){
if(argc<=2){printf("Usage: cchin [URL] [DIR]\n\nDownloads all images off specified 4chan board to ~/cchin/[DIR].\n[URL] is the link to board's catalog\n[DIR] is directory name inside ~/cchin/");return 0;}
char *home = getenv("HOME");
char catalog[LENGTH]={}; sprintf(catalog,"%s/cchin/%s/catalog",home,argv[2]);
char boardname[LENGTH]={};
int i=strlen(argv[1])-1,j=0;
while (argv[1][i]!='/'){j++;i--;} i=0;
while (j>=0){
	boardname[i]=argv[1][strlen(argv[1])-j];
	i++;j--;
	} 

char buff[LENGTH]={};
sprintf(buff,"wget -N -q -P %s/cchin/%s %s/catalog",home,argv[2],argv[1]);system(buff); //Downloads page's catalog to specific folder, TO BE CHANGED
char page[PAGE_LENGTH]={}; FILE *f=fopen(catalog,"r"); fgets(page,PAGE_LENGTH,f); sprintf(buff,"rm %s",catalog); system(buff); //Opens catalog file, reads it into char array, removes it
//printf("%s\n%s\n%s\n",home,catalog,buff); //debug stuff

char link[LENGTH]={};
i=50000,j=0; //i is starting offset, to be changed
while(i<strlen(page)){
	if(page[i]=='['&&page[i-1]==':'&&page[i-2]=='"'&&page[i-3]=='t') break;	
	i++;	
	} //i is the start position of thread numbers in page source right now
while(i<strlen(page)){i++;
	while(page[i+j]!=','&&page[i+j]!=']'){
		link[j]=page[i+j];
		j++;
	}i+=j;j=0;sprintf(buff,"chin https://boards.4chan.org/%s/res/%s ../cchin/%s/%s",boardname, link,argv[2],link);system(buff);
	if(page[i]==']') break;
}

return 0;
}
