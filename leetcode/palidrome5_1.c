

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* longestPalindrome(char* s) {
    char    *pRet;              
    int     len = 0, i = 0, k = 0, loc = 0; 
    int     sublen = 0, maxlen = 1;    
    char*   pTail;  
    char*   pHead;                                                                                        
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
        for(k = len - 1; k > i; k--)     
        {                                 
            pHead = &s[i];                
            pTail = &s[k];                 
            sublen = ( k - i + 1)/2;      
            while(sublen > 0)             
            {                             
                if(*pHead != *pTail)    
                {                       
                    break;             
                }                                                                                                                             
                pHead ++;                 
                pTail --;                 
                sublen --;               
            }                                                                                                                                 
            if(sublen == 0 && (maxlen < k - i + 1) ) 
            {                     
                loc = i;                   
                maxlen = k - i + 1;       
            }                                                                                                                                 
        }                                                                                                                                  
    }                                                                                               

out:
    pRet = (char *)malloc(maxlen * sizeof(char) + 1);  
    memset(pRet, 0, maxlen * sizeof(char) + 1);
    if(pRet == NULL)                     
    {                                    
        printf("Error malloc ");         
        return NULL;                                  
    }    

    if(len > 0)
    {
        memcpy(pRet, s + loc , maxlen);     
    }

    return pRet;
}   

/*
char* longestPalindrome(char* s) 
{
   char *  pRet = NULL;
   int     len = 0, i = 0, k = 0, loc = 0;
   int     sublen = 0, maxlen = 1;
   char*   pTail;
   char*   pHead;

   if(NULL == s)
   {
   goto out;
   }

   len = strlen(s);
   if(len == 0 )
   {
   goto out; 
   }

   if(len == 1)
   {
   pRet = (char *)malloc(len * sizeof(char) + 1);
   if(pRet == NULL)
   {
   printf("Error malloc ");
   goto out;
   }
   memcpy(pRet, s, len);
   }
   else
   {
   for(i = 0; i < len; i++)
   {
   for(k = len - 1; k > i; k--)
   {
   pHead = &s[i];
   pTail = &s[k];
   sublen = ( k - i + 1)/2;
   while(sublen > 0)
   {
   if(*pHead != *pTail)
   {
   break;
   }
   pHead ++;
   pTail --;
   sublen --;
   }
   if(sublen == 0 &&  maxlen < k - i + 1 )
   {
   loc = i;
   maxlen = k - i + 1;
   }
   }

   }

   pRet = (char *)malloc(maxlen * sizeof(char) + 1);
   if(pRet == NULL)
   {
   printf("Error malloc ");
   goto out;
   }
   memcpy(pRet, s + loc , maxlen);
   }

out:
return pRet;
}
*/


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






