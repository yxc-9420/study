#include "mystring.h"
#include<cstring>
mystring::mystring(const char *str)
{
    if(str == nullptr){
        m_data = new char[1];
        *m_data='\0';
    }
    else{
        int length = strlen(str);
        m_data = new char[length+1];
        strcpy(m_data,str);
    }
}

mystring::mystring(const mystring &other)
{
    m_data = new char[strlen(other.m_data)+1];
    strcpy(m_data,other.m_data);
}

mystring::~mystring()
{
    delete [] m_data;
}

mystring &mystring::operator =(const mystring &other)
{
    if(this == &other)
        return *this;
    delete [] m_data;//释放原内存
    int length = strlen(other.m_data);
    m_data = new char[length+1];
    strcpy(m_data,other.m_data);
    return *this;
}

