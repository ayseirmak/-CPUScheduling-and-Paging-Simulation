#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <time.h>
#define FNAME	"tasks.txt"
#define ROUND 10
#define frame_size 500
char PM[frame_size][255];
struct process {
    int start;
    int kalan;
    int middle;
    int line_size;
     int pt_size;
     int size;
     char name[255];
     char* content;
     int* page_table;
     int* read_byte;
};
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void randomize (int arr[], int n)
{
    srand (time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

 
int main(int argc, char * argv[]) 
{  
  for (int s=0;s<frame_size;s++)
    sprintf(PM[s],"%s","emp");
	FILE * fp = fopen(FNAME, "r");
  //Satir sayisi
  char c;
  int count =1;
  int c_new;
	if (fp == NULL) return 1; 
	char sword[255];
  for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') 
            count = count + 1;
    fclose(fp);
  //process list olusumu  
	//printf("count:%d\n",count);
  struct process p_list[count];
  int lineSize[count];
  for(int i=0;i<count;i++)
    lineSize[i]=0;
  fp = fopen(FNAME, "r"); 
  int index  =0;
 
   while(!feof(fp))
   {
     fscanf(fp,"%s",sword);
     if(strchr(sword,'.')){
      sprintf(p_list[index].name,"%s",sword);
      index++;
     }
     else{
      // printf("%s\n",sword);
       lineSize[index-1]=lineSize[index-1]+1;
     }
    }
  fclose(fp);
 
 for(int i=0;i<count;i++)
    p_list[i].line_size=lineSize[i];
    

  fp = fopen(FNAME, "r"); 
  index  =0;
  int index_line=0;
  int new_line;
  while(!feof(fp))
  {
    fscanf(fp,"%s",sword);
    if(strchr(sword,'.')){
      sprintf(p_list[index].name,"%s",sword);
      p_list[index].read_byte=(int *)malloc(p_list[index].line_size*sizeof(int)); 
      index_line=0;
      index++;
    }
    else{
      p_list[index-1].read_byte[index_line]=atoi(sword);
      index_line++;
    }
  }
  fclose(fp);
  /*for(int i=0;i<count;i++){
    printf("%s\n",p_list[i].name);
    for(int j=0; j<p_list[i].line_size;j++)
      printf("Deger: %d\n",p_list[i].read_byte[j]);
  }*/
 
  for(int i=0;i<count;i++){
    //printf("%s\n",p_list[i].name);
    fp = fopen(p_list[i].name, "r");
    fseek(fp, 0L, SEEK_END);
    p_list[i].size = ftell(fp);
    //printf("%d\n",p_list[i].size);
    fclose(fp);
  }
  for(int i=0;i<count;i++){
    //printf("%s,\n",p_list[i].name);
    p_list[i].pt_size= ceil(p_list[i].size/2048);
    //printf("%d\n",p_list[i].pt_size);
    int empty_frame=0;
    int len_pm=sizeof(PM) / sizeof(PM[0]);
    for(int j=0;j<len_pm;j++)
      if(strcmp(PM[j],"emp")==0)
        empty_frame++;
    //printf("empty frame:%d\n",empty_frame);
    if(empty_frame>=p_list[i].pt_size){
      int PM_e_frames[empty_frame];
      int index_ef=0;
      for(int j=0;j<len_pm;j++)
        if(strcmp(PM[j],"emp")==0){
          PM_e_frames[index_ef]=j;
          index_ef++;
      }
      int n = sizeof(PM_e_frames) / sizeof(PM_e_frames[0]);
      randomize (PM_e_frames, n);
      int pageTable[p_list[i].pt_size];
      for (int k=0;k<p_list[i].pt_size;k++)
      {
        pageTable[k]=PM_e_frames[k];
        sprintf(PM[PM_e_frames[k]],"%s",p_list[i].name);
      }
      p_list[i].page_table=pageTable;
      printf("%s page table:\n",p_list[i].name);
      for(int m=0;m<p_list[i].pt_size;m++)
        printf("%d.index-> %d\n",m,p_list[i].page_table[m]);
    }
    else
      sprintf(p_list[i].name,"%s","emp");
  }
  printf("Physical memory:\n");
  for(int i=0;i<frame_size;i++)
    printf("%s\n",PM[i]);
  c_new=0;
  for(int i=0;i<count;i++)
    if(strcmp(p_list[i].name,"emp")!=0)
       c_new++;
  struct process p_list_a[c_new];
  int in=0;
  for(int i=0;i<count;i++)
    if(strcmp(p_list[i].name,"emp")!=0){
      p_list_a[in]=p_list[i];
      p_list_a[in].start=0;
      p_list_a[in].kalan=p_list_a[in].line_size;
      if(p_list_a[in].line_size>ROUND)
        p_list_a[in].middle=ROUND;
      else
        p_list_a[in].middle=p_list_a[in].line_size;
      in++;
    }
  FILE *fileptr;
  for(int b=0;b<c_new;b++){
    fileptr = fopen(p_list_a[b].name, "rb");                              
    p_list_a[b].content= (char *)malloc((p_list_a[b].size+1)*sizeof(char)); 
    for(int i = 0; i < p_list_a[b].size; i++) 
       fread(p_list_a[b].content+i, 1, 1, fileptr); 
    fclose(fileptr); // Close the file
  }
  //SCHEDULAR:
  int ls;

  int byt;
  while(1){
    for(int i=0;i<c_new;i++){
      if(p_list_a[i].kalan<=0)
        i++;
      else{
        for(int j=p_list_a[i].start;j<p_list_a[i].middle;j++){ 
          byt=p_list_a[i].read_byte[j];
          if(byt>p_list_a->size)
            printf("Adress that tried to be accessed is bigger than size of the file!\n");
          else
              printf("File name:%s, access caharacter:%c\n",p_list_a[i].name,p_list_a[i].content[byt]); 
              }
        p_list_a[i].start=p_list_a[i].start+ROUND;
        p_list_a[i].kalan= p_list_a[i].kalan-ROUND;
        if(p_list_a[i].kalan>0 && p_list_a[i].kalan<ROUND)
          p_list_a[i].middle=p_list_a[i].start+p_list_a[i].kalan;
        else
          p_list_a[i].middle=p_list_a[i].start+ROUND;
      }
    }
    int c=0;
    for(int k=0;k<c_new;k++)
      if(p_list_a[k].kalan<=0)
        c++;
    if(c==c_new)
      break;
  }
  /*FILE *fileptr;
  for(int b=0;b<c_new;b++){
    fileptr = fopen(p_list_a[b].name, "rb");                              
    p_list_a[b].content= (char *)malloc((p_list_a[b].size+1)*sizeof(char)); 
    for(int i = 0; i < p_list_a[b].size; i++) 
       fread(p_list_a[b].content+i, 1, 1, fileptr); 
    
    printf("%s File len: %c\n",p_list_a[b].name,*(p_list_a[b].content+129));
    fclose(fileptr); // Close the file
  }*/
  
  return 0;
}



  

