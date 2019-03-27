

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int centerExpend(char *s, int left, int right)
{
    int L = left;
    int R = right;
   
    while( L >= 0 && R < strlen(s) && s[L] == s[R] )
    {
        L -- ;
        R ++ ;
    }

    return  R - L - 1;
}

char* longestPalindrome(char* s) 
{
    char    *pRet;              
    int     len = 0, i = 0;
    int     start = 0 , end = 0;
    int     loc = 0; 
    int     maxlen = 1;    
    int     lenOdd = 0;
    int     lenEven = 0;
    
    if(NULL == s)                             
    {   
        goto out;                                    
    } 

    len = strlen(s);
    if(len <= 1 )  
    {   
        maxlen = len;          
        goto out;                             
    }

    for(i = 0; i < len; i++)              
    {                            
        lenOdd = centerExpend(s, i, i);
        lenEven = centerExpend(s, i, i+1);
        maxlen = lenOdd > lenEven ? lenOdd : lenEven ;
        if( maxlen >  end -start)
        {
            start = i - (maxlen - 1) / 2;
            end = i + maxlen / 2;
        }

    }
    loc = start;
	maxlen = end - start + 1;
out:
    pRet = (char *)malloc(maxlen * sizeof(char) + 1);  
    memset(pRet, 0, maxlen * sizeof(char) + 1);
    if(pRet == NULL)                     
    {                                    
        printf("Error malloc ");         
        return NULL;                                  
    }    

    if(maxlen > 0)
    {
        memcpy(pRet, s + loc , maxlen);     
    }

    return pRet;
}   

int main(int argc, char **argv)
{
    char str[] = "babad";
    //char str[] = "cbbd";
    //char str[] = "cd";
    //char str[] = "";
    //char *str = NULL;
    //char *str = "e";
    char *pRet ;

    pRet = longestPalindrome(str);

    if(pRet != NULL)
    {
        printf("pRet: %s \n", pRet);
    }
    else
    {
        printf("pRet is NULL \n");
    }

    free(pRet);
    return 0;
}






