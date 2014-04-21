#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#define LENGTH 256
#define PAGE_LENGTH 999999


/* Required by CURL */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


int main(int argc, char *argv[]){

	/* Disables line buffering */
	setbuf(stdout, NULL);

	/* Gets location of home folder */
	char *home = getenv("HOME");
	
	/* Various variables */
	char 
	threadURL[LENGTH]={},
	threadnum[LENGTH]={},
	jsonURL[LENGTH]={},
	filepath[LENGTH]={},
	wget[LENGTH]={},
	extension[LENGTH]={},
	imagenumber[LENGTH]={},
	whole[PAGE_LENGTH]={},
	downloadfolder[LENGTH]={},
	imgpath[LENGTH]={},
	mkdir[LENGTH]={},
	backup[LENGTH]={};
	
	int j=0,
	i=0,
	count=0,
	thrlen=0,
	skipped=0;
		
	
	
	
	/* Checks for presence of arguments */
	if(argc<=2)
	{
		printf(
			"Usage: chin URL DIR\n\nDownloads images off specified 4chan thread to ~/chin/DIR\n");
		return 0;
	} 
	
	/* Writes first argument and its length to 'threadURL' and 'thrlen' accordingly */
	strcat(threadURL,argv[1]);  
	thrlen=strlen(threadURL);
		
	
	/*I don't like those three blocks, will replace them sometime in the future */	
		
		/* Extracts thread number and writes it to 'threadnum' */
		i=thrlen-1;
		while (threadURL[i]!='/')
		{
			count++;
			i--;
		} 
		i=0;
		while (count>=0)
		{
			threadnum[i]=threadURL[thrlen-count];
			i++;
			count--;
		}
		
		 /* Extracts board's name */
		char boardname[LENGTH]={};
		j=strlen(threadnum);
		i=thrlen-8-j-1;
		count=0;
		while (threadURL[i]!='/')
		{
			count++;
			i--;
		}
		i=0; 
		while (count-1>=0)
		{
			boardname[i]=threadURL[thrlen-count-j-8];
			i++;
			count--;
		}
		/* Workaroung for namespace changes */
		if(strcmp("boards.4chan.or",boardname)==0 || strcmp("boards.4chan.org",boardname)==0)
		{
			sprintf(boardname," ");
			j=strlen(threadnum);
			i=thrlen-5-j-1;
			count=0;
			while (threadURL[i]!='/')
			{
				count++;
				i--;
			}
			i=0; 
			while (count-1>=0)
			{
				boardname[i]=threadURL[thrlen-count-j-5];
				i++;
				count--;
			}
			
		}
		
	printf("\nDownloading thread  #%s on /%s/, please wait...",threadnum,boardname); 
	
	/* Forms .json URL */
	sprintf(jsonURL, "http://a.4cdn.org/%s/thread/%s.json",boardname,threadnum);
	
	/* Old section that uses wget */	
	/*
	sprintf(wget,"wget -N -q -P %s/chin/%s/ ", home, argv[2]); 
 	sprintf(wget,"%s%s",wget,jsonURL); 
	system(wget); 
	*/

	/* If you want to use wget instead of libcurl when downloading .json file,
	 * you could remove following section and uncomment section above.*/
	
	
	/* Beginning of CURL section */
	{
		CURL *curl;
		FILE *img;
		curl = curl_easy_init();
		if(curl) 
		{
			sprintf(mkdir,"mkdir -p %s/chin/%s",home,argv[2]);
			system(mkdir);
			
			/* The following two lines form a workaround that does 2 things:
			 * 1. Prevents .json file from being erased locally by CURL if it doesn't exist on server
			 * 2. Preserves old versions which may contain deleted replies
			 * If you do not want to clobber your local archive with old .json's or
			 * do not care about text archiving at all, you could safely remove them. */
			sprintf(backup,"mv --backup=t %s/chin/%s/%s.json %s/chin/%s/%s.json.old 2>/dev/null",home,argv[2],threadnum,home,argv[2],threadnum);
			system(backup);
			
			
			sprintf(imgpath,"%s/chin/%s/%s.json",home,argv[2],threadnum);
			img = fopen(imgpath, "wb");
			printf("\nDownloading .json... ");
			curl_easy_setopt(curl,CURLOPT_URL,jsonURL);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_data); 
			curl_easy_setopt(curl, CURLOPT_WRITEDATA,img);
			curl_easy_perform(curl);
			printf("Finished!");
			curl_easy_cleanup(curl);
			fclose(img);
		}
	}
	/* End of CURL section */
	
		
	/* Writes path to downloaded file to 'filepath' */
	sprintf(filepath,"%s/chin/%s/%s.json",home, argv[2], threadnum);

	/* Opens downloaded file */
	FILE *f=fopen(filepath,"r"); 
	
	/* Writes entire file to char array 'whole' */
	fgets(whole,PAGE_LENGTH,f);
	
	/* i is starting offset */
	i=10;

	/* Resets counter */
	count=0;

	/* Writes path to download folder to 'downloadfolder' */
	sprintf(downloadfolder,"%s/chin/%s",home,argv[2]);
	
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
			
			while(whole[i+j]!='"')
			{
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
			printf("\nDownloading image %d: i.4cdn.org/%s/%s%s...",count,boardname,imagenumber,extension);
			
			/* Old wget section */
			
			/* 
				sprintf(wget,"wget -nc -P %s -q i.4cdn.org/%s/src/%s%s",downloadfolder,boardname,imagenumber,extension);
				system(wget);
				printf("Done!");
			*/
			
			
			/* If you want to use wget instead of libcurl to download images
			 * you could remove following CURL section and uncomment section above */
			
			/* CURL section */
			{	CURL *curl;
				FILE *img;
				curl = curl_easy_init();
				if(curl) 
				{
					sprintf(imgpath,"%s/chin/%s/%s%s",home,argv[2],imagenumber,extension);
					
					if((img=fopen(imgpath,"r"))==NULL)
					{
						img = fopen(imgpath, "wb");
						sprintf(wget,"i.4cdn.org/%s/%s%s",boardname,imagenumber,extension);
						curl_easy_setopt(curl,CURLOPT_URL,wget);
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_data); 
						curl_easy_setopt(curl, CURLOPT_WRITEDATA,img);
						curl_easy_perform(curl);
						printf("Done!");
						curl_easy_cleanup(curl);
					} 
					else 
					{
						printf("Skipping.");
						skipped++;
					}
					fclose(img);
				}
			}
			/* End of CURL section */
			
			i+=180;
		}	
		i++;j=0;
	}
	printf("\nTotal images: %d", count);
	printf("\nNew images downloaded: %d", count-skipped);
	printf("\nImages skipped: %d\n", skipped);
	return 0;
}
