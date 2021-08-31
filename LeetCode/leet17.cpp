#include<string>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if(digits.empty()) return res;
        map<char,string> kv{
            {'2',"abc"},{'3',"def"},{'4',"ghi"},
            {'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
            {'8',"tuv"},{'9',"wxyz"}
        };
        queue<string> q;
        q.push("");
        for(char a : digits){
            int size = q.size();
            for(int i=0;i<size;i++){
                string temp = q.front();
                q.pop();
                for_each(kv[a].begin(),kv[a].end(),[temp,&q](char v){q.push(temp+v);});
            }
        }
        while (!q.empty()) {
            res.emplace_back(q.front());
            q.pop();
        }
        return res;
    }
};
