#ifndef __IO_handler_HH__
#define __IO_handler_HH__

#include<bits/stdc++.h>

using namespace std;
//We define Read and write function 
// Which will allw us to read initial condition and parameter

vector<double> Initial_Conditions(const string& filename);

bool Problem_Parameters(const string& filename,int& grid, double& x_min, double& x_max, double& delta_t, double& alpha);

void Output_dat( vector<double>& U, int step);

#endif