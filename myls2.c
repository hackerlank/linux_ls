/*************************************************************************
	> File Name: myls.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 19 Jun 2014 08:21:40 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
void timeformat(char **lstime)
{
  char *a;
  a=(*lstime)+4;
  while(**lstime)
  {
   (*lstime)++;
  }
  while((**lstime)!=':')
	(*lstime)--;
  **lstime='\0';
  *lstime=a;
}
void mode_to_str(mode_t md,char * str)
{
	strcpy(str,"----------");
	if(S_ISDIR(md))
	str[0]='d';
	if(md&S_IRUSR)
		str[1]='r';
	if(md&S_IWUSR)
		str[2]='w';
	
	if(md&S_IXUSR)
		str[3]='x';
	
	if(md&S_IRGRP)
		str[4]='r';

	if(md&S_IWGRP)
		str[5]='w';
	
	if(md&S_IXGRP)
		str[6]='x';
	
	if(md&S_IROTH)
		str[7]='r';
	
	if(md&S_IWOTH)
		str[8]='w';

	if(md&S_IXOTH)
		str[9]='x';
}
int main(int argc,char *argv[])
{
	DIR *pDir;
	struct stat mystat;
	char modestr[11];
	char *lstime;
	char *path=(char *)calloc(100,sizeof(char));
	int count=0,i=0;
	struct dirent* myent;
	if(argc==1)
	{
		pDir=opendir(".");
	}else
	{
		pDir=opendir(argv[1]);
	}
	if(pDir==NULL)
	{
		perror("open fail:");
		exit(-1);
	}
    while((myent=readdir(pDir))!=NULL)		
	{
		i=0;
		memset(&mystat,0,sizeof(mystat));
		if(argc==1)
		stat(myent->d_name,&mystat);
		else
		{
        sprintf(path,"%s/%s",argv[1],myent->d_name);
		stat(path,&mystat);
		}
		mode_to_str(mystat.st_mode,modestr);
		if(strcmp(myent->d_name,".")==0||strcmp(myent->d_name,"..")==0)
		continue;
	//	strcpy(lstime,ctime(&mystat.st_atime));
	    lstime=ctime(&mystat.st_atime);
		timeformat(&lstime);
		printf("%-10s.%2d %5s %5s %5d %s %s\n",modestr,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name,getgrgid(mystat.st_gid)->gr_name,mystat.st_size,lstime,myent->d_name);
		count++;
	}
	closedir(pDir);
	return 0;
}
