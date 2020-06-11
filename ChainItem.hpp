
#ifndef _ChainItem_hpp
#define _ChainItem_hpp
#include <iostream>
#include <string>
#include <fstream>
#include "AVLTree.hpp"
#include "LogItem.hpp"
using namespace std;


class ChainItem
{
    private:
    string ip;// ip of logItem
    AVLTree<LogItem> * DataTree;// DataTree that has the item of logItem
    public:
    ChainItem();// Constructor
    ChainItem (LogItem &item);// Constructor with a parameter-> O(1)
    void InsertData( LogItem item);// Inserting into DataTree O(log n)
    AVLNode<LogItem>* get_insideRoot();// returning the root of DataTree-> O(1)
    string get_ip();
    bool  operator>(const ChainItem& it);// Overloading operators-> O(1)
    bool operator<(const ChainItem& it);// Overloading operators-> O(1)
    bool operator !=(const ChainItem& it);// Overloading operators-> O(1)
    bool operator ==(const ChainItem& it);// Overloading operators-> O(1)
    bool operator <=(const ChainItem& it);// Overloading operators-> O(1)
    bool operator >=(const ChainItem& it);// Overloading operators-> O(1)
    ~ChainItem();// Deconstructor
};



ChainItem::ChainItem()// Constructor
{
    ip = "";// setting default ip
    DataTree = new AVLTree<LogItem>;// setting DataTree to NULL
}

ChainItem::ChainItem(LogItem &item):ChainItem()
{// constructor with parameter 
    ip=item.getIp(); //for returning ip of the logitem
}

string ChainItem::get_ip()
{
    return ip;
}
bool  ChainItem:: operator< (const ChainItem &it) // Overloading operators
{
    if(ip<it.ip)// Less Than
        return true;
    else
        return false;
           
}

bool  ChainItem :: operator> (const ChainItem &it)// Overloading Operators
{
    if(ip > it.ip)// Greater Than
        return true;
    
    else
        return false;
}
bool ChainItem:: operator!=(const ChainItem &it)// Overloading operators
{
    if(ip!=it.ip)// not equal
        return true;
    else
        return false;
}
bool ChainItem:: operator==(const ChainItem & it){// Overloading operators
    if(ip==it.ip)// equal
        return true;
    else
        return false;
}
bool ChainItem:: operator>=(const ChainItem & it){// Overloading operators
    if((ip>it.ip)||(ip==it.ip))// Less than or equal
        return true;
    else
        return false;
}
bool ChainItem:: operator<=(const ChainItem & it){// Overloading operators
   if((ip<it.ip)||(ip==it.ip))// Greater than or equal
        return true;
    else
        return false;
}

AVLNode<LogItem>* ChainItem::get_insideRoot()
{//To get the root of the DataTree 
   return  DataTree->getRoot();// Returning the root
}
void ChainItem:: InsertData(LogItem item)// Inserting into the DataTree
{
        DataTree->insert(item);// else if it's not empty, insert into the already made tree
}


ChainItem::~ChainItem()
{// deconstructor
}

/****************************************************************************************/
/*                           LogItem Prototype                                */
/****************************************************************************************/




// ChainItem* LogItem::getKey()
// {
//     ChainItem* c= new ChainItem(*this);
//     return c;
// }
// int LogItem:: hash(int size)
// {// hashing fuction
//     int hash=0;
//     for(int i=0;i<ip.length();i++)// looping through the characters of the ip
//         hash+=ip[i];// summing the ascii of each character
    
//     return hash%size;// mod size to fit in the hashtable
// }


// ostream & operator << (ostream &out,  LogItem & it)// overloading cout operator
// {
//     return out;
// }

// string LogItem :: getIp()
// {// ip getter
//     return ip;
// }
// string LogItem :: getDate()
// {// Date getter
//     return date;
// }
// string LogItem :: getTime()
// {// Time getter
//     return Time;
// }
// int LogItem :: getIndex()
// {// Index getter
//     return index;
// }
// void LogItem :: setIndex(int i)
// {// Index setter
//     index=i;
// }

// LogItem:: LogItem()
// {// constructor
//     index=0;
// }

// LogItem::LogItem(string &line,int i):LogItem()
// {// contructor with parameter
//     int pos= line.find(',');// finding delimeter
//     ip= line.substr(0,pos);//cutting line till the delimter setting it to ip
//     line.erase(0,pos+1);// erasing what we just cut

//     pos= line.find(',');
//     date= line.substr(0,pos);//cutting line till the delimter setting it to Date
//     line.erase(0,pos+1);

//     pos= line.find(',');
//     Time= line.substr(0,pos);//cutting line till the delimter setting it to Time
//     line.erase(0,pos+1);

    
//     setIndex(i);
// }
// bool  LogItem:: operator< (const LogItem &it)const
// {// overloading operator
//     if(ip<it.ip)// Less than
//         return true;
//     else if(ip==it.ip)
//     {// if they are equal take check index to avoid removing dublicate ip
//         if(index<it.index)
//             return true;
//     }
//         else
//             return false;
// }

// bool  LogItem :: operator> (const LogItem &it)const
// {// Overloading operator
//     if(ip > it.ip)// greater than
//         return true;
//     else if(ip==it.ip)
//     { // if they are equal take check index to avoid removing dublicate ip
//         if(index>it.index)
//             return true;
//     }
//     else
//         return false;
// }
// bool LogItem:: operator!=(const LogItem &it)const
// {// Overloading operator
//     if(ip!=it.ip)// not equal
//         return true;
//     else
//         return false;
// }
#endif