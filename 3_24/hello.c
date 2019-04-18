#include"stdio.h"
#include"string.h"

int main(){
  FILE* fp = fopen("myfile","r");
  if(!fp){
    printf("fopen error !\n");
  }
  char buf[1024];
  const char* msg = "hello bit!\n";
  while(1){
  size_t ret = fread(buf,1,strlen(msg),fp);
  if(ret > 0){
    buf[ret] = '\0';
    printf("%s",buf);
  }
  if(feof(fp)){
    break;
  }
  }
//  int count = 5;
//  while(count--){
//    fwrite(msg,strlen(msg),1,fp);
//  }
  fclose(fp);
  return 0;
}
