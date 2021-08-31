#include<assert.h>
#include<cstring>
#include<iostream>

/**********************************************
****@projectName study
****@Author      yuwenchao
****@Describe    strcpy实现，不考虑内存重叠
****@Time        2021-07-08 14:52:24
**********************************************/
char* mystrcpy(char* dest,const char *source){
    assert(dest != nullptr && source!=nullptr);
    char *res = dest;
    //while((*res++=*source++)!='\0');
    //先赋值，在往后移一位,在判断当前res是否等于'\0'.
    //当走到'\0'时，赋值操作已经执行，此时结束循环。
    //此时res后也带'\0'
    //或者调用memecy
    char *mymemecy(char *,const char *,int);
    res = mymemecy(dest,source,strlen(source)+1);
    return res;
}

/**********************************************
****@projectName study
****@Author      yuwenchao
****@Describe    memecy，内存复制
****@Time        2021-07-16 14:46:52
**********************************************/
char *mymemecy(char *dest,const char *source, int count){
    assert(dest != nullptr && source!=nullptr);
    char *res = dest;
    if(dest>=source&&dest<=source+count-1){
        res = res+count-1;
        source = source+count-1;
        while(count--){
            *dest-- = *source--;
        }
    }
    else{
        while(count--){
            *dest++=*source++;
        }
    }
    return res;
}
