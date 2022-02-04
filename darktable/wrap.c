#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#define PREFIX "/usr/bin/"

void main(int argc , char *argv[]) {
char temp[4096];
char temp2[4096];
char *v[256];
char *path=PREFIX;
char **p;
char *e;
char *t;
char *lastt;
int i;
int d=0;
struct stat sb;

if (argc >= 2 ) {
  strncpy(temp,getenv("APPDIR"),4095);
  strncat(temp,PREFIX,4095-strlen(temp));
  strncat(temp,argv[1],4095-strlen(temp));
  temp[4095]='\0';

  if (stat(temp,&sb) == 0 && sb.st_mode & S_IXUSR ) {
   v[0]=temp;
   d=1;
  }
} 
  
if (v[0] == NULL && (e = getenv("ARGV0")) ) {
  /* Find the last element */
  strncpy(temp2,e,4095);
  temp2[4095] = '\0';
  t = strtok(temp2,"/");
  while(t != NULL) {
   lastt=t;
   t=strtok(NULL,"/");
  };
  if (lastt == NULL) {
    lastt=e;
  }
  
  strncpy(temp,getenv("APPDIR"),4095);
  strncat(temp,PREFIX,4095-strlen(temp));
  strncat(temp,lastt,4095-strlen(temp));
  temp[4095]='\0';

  if (stat(temp,&sb) == 0 && sb.st_mode & S_IXUSR ) {
   v[0]=temp;
}
}
if (v[0] == NULL ) {
  strncpy(temp,getenv("APPDIR"),4095);
  strncat(temp,PREFIX,4095-strlen(temp));
  strncat(temp,BIN,4095-strlen(temp));
  temp[4095]='\0';
  v[0]=temp;
}
   for (i=1+d;(i<argc && i<254);i++)  {
     v[i-d]=argv[i];
   }
printf("%d\n",i-d);
   v[i-d]=NULL;
   execv(v[0],v);

fprintf(stderr,"Unable to execute: %s within appimage\n",v[0]);

};
