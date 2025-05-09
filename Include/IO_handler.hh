#ifndef __IO_handler_HH__
#define __IO_handler_HH__

#include<bits/stdc++.h>

using namespace std;
//We define Read and write function 
// Which will allw us to read initial condition and parameter

vector<double> ReadInitialConditions(const string& filename);

bool ReadProblemParameters(const string& filename,int& grid, double& x_min, double& x_max, double& delta_t, double& alpha);

void WriteOutput( vector<double>& U, int step);

#endif