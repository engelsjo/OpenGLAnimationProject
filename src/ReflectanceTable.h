//
//  ReflectanceTable.h
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/10/15.
//
//

#ifndef __ProjectTwo__ReflectanceTable__
#define __ProjectTwo__ReflectanceTable__

#include <stdio.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>


using namespace std;
class ReflectanceTable
{
    
public:
    map<string, map<string, vector<float>>> lookup_table;
    void init_table();
    const map<string, map<string, vector<float>>> get_table();
    const vector<float> get_comp(string material, string comp);
};


#endif /* defined(__ProjectTwo__ReflectanceTable__) */


