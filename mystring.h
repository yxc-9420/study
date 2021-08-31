#ifndef MYSTRING_H
#define MYSTRING_H


class mystring
{
public:
    mystring(const char *str = nullptr);//普通构造
    mystring(const mystring &other);//拷贝构造
    ~mystring();
    mystring& operator =(const mystring &other);//赋值函数

private:
    char * m_data;
};

#endif // MYSTRING_H
