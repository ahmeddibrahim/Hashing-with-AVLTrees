#include "Hash.hpp"
#include <iostream>
using namespace std;

int main ()
{       
        // AVLTree<LogItem> avlTree;
        
        Hash<ChainItem,LogItem> hashtable;
        ifstream infile;
        infile.open("testcase.rtf");
        if(infile.is_open()){
                string s;
                int count=0;
                getline(infile,s);
                while(!infile.eof())
                {
                        count++;
                        LogItem line(s,count);
                        hashtable.Insert(line);
                       
                        getline(infile,s);
                
                }
                        infile.close();
        }
        else
       cout<<"Error"<<endl;

        hashtable.traverse();
        
        return 0;
}
