#include"leet541.cpp"
#include<iterator>
#include<iostream>
int main(int argc, char *argv[]){
    Solution s;
    string res = s.reverseStr("abcdefghs",3);
    cout<<res;
//    ostream_iterator<string> o(std::cout," ");
//    copy(res.cbegin(),res.cend(),o);
    system("pause");
}
