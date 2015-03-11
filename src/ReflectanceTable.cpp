//
//  ReflectanceTable.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/10/15.
//
//

#include "ReflectanceTable.h"

void ReflectanceTable::init_table(){
    //set up the table
    lookup_table["Brass"].insert({{"AMBIENT", {0.329412, 0.223529, 0.027451, 1.000000}}, {"DIFFUSE", {0.780392, 0.568627, 0.113725, 1.000000}}, {"SPECULAR", {0.992157, 0.941176, 0.807843, 1.000000}}, {"SHININESS", {27.897400}}});
    
    lookup_table["Bronze"].insert({{"AMBIENT", {0.212500, 0.127500, 0.054000, 1.000000}}, {"DIFFUSE", {0.714000, 0.428400, 0.181440, 1.000000}}, {"SPECULAR", {0.393548, 0.271906, 0.166721, 1.000000}}, {"SHININESS", {25.600000}}});
    
    lookup_table["Polished Bronze"].insert({{"AMBIENT", {0.250000, 0.148000, 0.064750, 1.000000}}, {"DIFFUSE", {0.400000, 0.236800, 0.103600, 1.000000}}, {"SPECULAR", {0.774597, 0.458561, 0.200621, 1.000000}}, {"SHININESS", {76.800003}}});
    
    lookup_table["Chrome"].insert({{"AMBIENT", {0.250000, 0.250000, 0.250000, 1.000000}}, {"DIFFUSE", {0.400000, 0.400000, 0.400000, 1.000000}}, {"SPECULAR", {0.774597, 0.774597, 0.774597, 1.000000}}, {"SHININESS", {76.800003}}});
    
    lookup_table["Copper"].insert({{"AMBIENT", {0.191250, 0.073500, 0.022500, 1.000000}}, {"DIFFUSE", {0.703800, 0.270480, 0.082800, 1.000000}}, {"SPECULAR", {0.256777, 0.137622, 0.086014, 1.000000}}, {"SHININESS", {12.800000}}});
    
    lookup_table["Polished Copper"].insert({{"AMBIENT", {0.229500, 0.088250, 0.027500, 1.000000}}, {"DIFFUSE", {0.550800, 0.211800, 0.066000, 1.000000}}, {"SPECULAR", {0.580594, 0.223257, 0.069570, 1.000000}}, {"SHININESS", {51.200001}}});
    
    lookup_table["Gold"].insert({{"AMBIENT", {0.247250, 0.199500, 0.074500, 1.000000}}, {"DIFFUSE", {0.751640, 0.606480, 0.226480, 1.000000}}, {"SPECULAR", {0.628281, 0.555802, 0.366065, 1.000000}}, {"SHININESS", {51.200001}}});
    
    lookup_table["Polished Gold"].insert({{"AMBIENT", {0.247250, 0.224500, 0.064500, 1.000000}}, {"DIFFUSE", {0.346150, 0.314300, 0.090300, 1.000000}}, {"SPECULAR", {0.797357, 0.723991, 0.208006, 1.000000}}, {"SHININESS", {83.199997}}});
    
    lookup_table["Pewter"].insert({{"AMBIENT", {0.105882, 0.058824, 0.113725, 1.000000}}, {"DIFFUSE", {0.427451, 0.470588, 0.541176, 1.000000}}, {"SPECULAR", {0.333333, 0.333333, 0.521569, 1.000000}}, {"SHININESS", {9.846150}}});
    
    lookup_table["Silver"].insert({{"AMBIENT", {0.192250, 0.192250, 0.192250, 1.000000}}, {"DIFFUSE", {0.507540, 0.507540, 0.507540, 1.000000}}, {"SPECULAR", {0.508273, 0.508273, 0.508273, 1.000000}}, {"SHININESS", {51.200001}}});
    
    lookup_table["Polished Silver"].insert({{"AMBIENT", {0.231250, 0.231250, 0.231250, 1.000000}}, {"DIFFUSE", {0.277500, 0.277500, 0.277500, 1.000000}}, {"SPECULAR", {0.773911, 0.773911, 0.773911, 1.000000}}, {"SHININESS", {89.599998}}});
    
    lookup_table["Emerald"].insert({{"AMBIENT", {0.021500, 0.174500, 0.021500, 0.550000}}, {"DIFFUSE", {0.075680, 0.614240, 0.075680, 0.550000}}, {"SPECULAR", {0.633000, 0.727811, 0.633000, 0.550000}}, {"SHININESS", {76.800003}}});
    
    lookup_table["Jade"].insert({{"AMBIENT", {0.135000, 0.222500, 0.157500, 0.950000}}, {"DIFFUSE", {0.540000, 0.890000, 0.630000, 0.950000}}, {"SPECULAR", {0.316228, 0.316228, 0.316228, 0.950000}}, {"SHININESS", {12.800000}}});
    
    lookup_table["Obsidian"].insert({{"AMBIENT", {0.053750, 0.050000, 0.066250, 0.820000}}, {"DIFFUSE", {0.182750, 0.170000, 0.225250, 0.820000}}, {"SPECULAR", {0.332741, 0.328634, 0.346435, 0.820000}}, {"SHININESS", {38.400002}}});
    
    lookup_table["Pearl"].insert({{"AMBIENT", {0.250000, 0.207250, 0.207250, 0.922000}}, {"DIFFUSE", {1.000000, 0.829000, 0.829000, 0.922000}}, {"SPECULAR", {0.296648, 0.296648, 0.296648, 0.922000}}, {"SHININESS", {11.264000}}});
    
    lookup_table["Ruby"].insert({{"AMBIENT", {0.174500, 0.011750, 0.011750, 0.550000}}, {"DIFFUSE", {0.614240, 0.041360, 0.041360, 0.550000}}, {"SPECULAR", {0.727811, 0.626959, 0.626959, 0.550000}}, {"SHININESS", {27.897400}}});
    
    lookup_table["Turquoise"].insert({{"AMBIENT", {0.100000, 0.187250, 0.174500, 0.800000}}, {"DIFFUSE", {0.396000, 0.741510, 0.691020, 0.800000}}, {"SPECULAR", {0.297254, 0.308290, 0.306678, 0.800000}}, {"SHININESS", {12.800000}}});
    
    lookup_table["Black Plastic"].insert({{"AMBIENT", {0.000000, 0.000000, 0.000000, 1.000000}}, {"DIFFUSE", {0.010000, 0.010000, 0.010000, 1.000000}}, {"SPECULAR", {0.500000, 0.500000, 0.500000, 1.000000}}, {"SHININESS", {32.000000}}});
    
    lookup_table["Black Rubber"].insert({{"AMBIENT", {0.020000, 0.020000, 0.020000, 1.000000}}, {"DIFFUSE", {0.010000, 0.010000, 0.010000, 1.000000}}, {"SPECULAR", {0.400000, 0.400000, 0.400000, 1.000000}}, {"SHININESS", {10.000000}}});
}



const map<string, map<string, vector<float>>> ReflectanceTable::get_table()
{
    return lookup_table;
}

const vector<float> ReflectanceTable::get_comp(string material, string comp){
    
    return lookup_table[material][comp];
}