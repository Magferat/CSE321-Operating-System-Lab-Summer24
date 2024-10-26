
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<stdlib.h>



int main(int args,char *arg[])
{
    FILE *fp=fopen(arg[1],"w");
    
    char str[200];

    scanf("%s",str);
    while (true){
        
        bool flag=true;

        for(int i=0;i<strlen(str)-1;i++){

            if(str[i]=='-' && str[i+1]=='1'){
                    flag=false;
                    break;
                }             
        }
        if(flag==false) break;
        else {
	        fprintf(fp,"%s\n",str);
	        scanf("%s",str);

	        }

        
    }
    fclose(fp);
    return 0;  


}


