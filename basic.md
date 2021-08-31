一、负数
    以补码形式存在
    
    unsinged short int i=0;
    i = i-1  相当于 i= i+(-1)// i= 65535
    -1: 
        原码:1000 0000 0000 0001
        反码:1111 1111 1111 1110  符号位不变，其余位取反
        补码:1111 1111 1111 1111  反码+1
二、atomic_flag
    “属性”                        描述
    clear               将存储的标志设置为 false 。
    test_and_set	将存储的标志设置为 true 并返回初始标志值。

三、forward
    当参数是左值引用时，直接返回原参数
    当参数不是左值引用时，返回右值引用
    template <class T> T&& forward (typename remove_reference<T>::type& arg) noexcept;
    template <class T> T&& forward (typename remove_reference<T>::type&& arg) noexcept;
