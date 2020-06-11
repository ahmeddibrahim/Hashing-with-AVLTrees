#ifndef _LogItem_hpp
#define _LogItem_hpp
#include "ChainItem.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/****************************************************************************************/
/*                           LogItem Prototype                                */
/****************************************************************************************/
class LogItem 
{ 
private:
    string ip;
    string date;
    string Time;
    int index;
public:
    LogItem();
    LogItem(string &line,int index);//O(1)
    bool  operator>(const LogItem &it)const;//O(1)
    bool operator<(const LogItem &it)const;//O(1)
    bool operator !=(const LogItem &it)const;//O(1)
    bool operator ==(const LogItem &it)const;

    string  getIp();//O(1)
    string  getDate();//O(1)
    string getTime();//O(1)
    int  getIndex();//O(1)
    void setIndex(int i);//O(1)
    int hash(int size);//O(n), n being the length of the string being hashed
    // ChainItem* getKey();// O(1)
    
};

// ChainItem* LogItem::getKey()
// {
//     ChainItem* c= new ChainItem(*this);
//     return c;
// }
int LogItem:: hash(int size)
{// hashing fuction
    int hash=0;
    for(int i=0;i<ip.length();i++)// looping through the characters of the ip
        hash+=ip[i];// summing the ascii of each character
    
    return (int)hash%size;// mod size to fit in the hashtable
}


ostream & operator << (ostream &out,  LogItem & it)// overloading cout operator
{
    return out;
}

string LogItem :: getIp()
{// ip getter
    return ip;
}
string LogItem :: getDate()
{// Date getter
    return date;
}
string LogItem :: getTime()
{// Time getter
    return Time;
}
int LogItem :: getIndex()
{// Index getter
    return index;
}
void LogItem :: setIndex(int i)
{// Index setter
    index=i;
}

LogItem:: LogItem()
{// constructor
    index=0;
}

LogItem::LogItem(string &line,int i):LogItem()
{// contructor with parameter
    int pos= line.find(',');// finding delimeter
    ip= line.substr(0,pos);//cutting line till the delimter setting it to ip
    line.erase(0,pos+1);// erasing what we just cut

    pos= line.find(',');
    date= line.substr(0,pos);//cutting line till the delimter setting it to Date
    line.erase(0,pos+1);

    pos= line.find(',');
    Time= line.substr(0,pos);//cutting line till the delimter setting it to Time
    line.erase(0,pos+1);

    
    setIndex(i);
}
bool  LogItem:: operator< (const LogItem &it)const
{// overloading operator
    if(ip<it.ip)// Less than
        return true;
    else if(ip==it.ip)
    {// if they are equal take check index to avoid removing dublicate ip
        if(index<it.index)
            return true;
    }
        else
            return false;
}

bool  LogItem :: operator> (const LogItem &it)const
{// Overloading operator
    if(ip > it.ip)// greater than
        return true;
    else if(ip==it.ip)
    { // if they are equal take check index to avoid removing dublicate ip
        if(index>it.index)
            return true;
    }
    else
        return false;
}
bool LogItem:: operator!=(const LogItem &it)const
{// Overloading operator
    if(ip!=it.ip)// not equal
        return true;
    else
        return false;
}
bool LogItem:: operator ==(const LogItem &it)const
{
    if(ip==it.ip)
        return true;
    else
        return false;

}
#endif




