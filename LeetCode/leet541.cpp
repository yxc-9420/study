#include<string>
#include<algorithm>
using namespace std;
class Solution {
public:
    string reverseStr(string s, int k) {
        for(int i = 0,size = s.size();i<size;i = i+k*2){
            reverse(s.begin()+i,s.begin()+i+ min(size-i,k));
        }
        return s;
    }
};
