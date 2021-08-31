#include<fstream>
using namespace std;

void testwrite(){
    ofstream outfile;
    outfile.open("E:\\Project\\QtProject\\study\\ceshi.txt",ios_base::openmode::_S_app);
    string s = "22";
    outfile<<s;
    outfile.close();

    ifstream infile;
    infile.open("E:\\Project\\QtProject\\study\\ceshi.txt",ios_base::openmode::_S_in);

    system("pause");
}
