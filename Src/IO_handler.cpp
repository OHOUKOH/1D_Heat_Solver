#include "../Include/IO_handler.hh"
#include<bits/stdc++.h>

using namespace std;
//We define Read and write function 
// Which will allw us to read initial condition and parameter

vector<double> ReadInitialConditions(const string& filename){

        ifstream file(filename , ios::binary);
        vector<double> data;

        if(file){
            // I need to point to the end of file 
            file.seekg(0 , ios::end);
            //I need to get the number of 64 bits elment
            int len = file.tellg()/ sizeof(double);
            file.seekg(0 , ios::beg);
            data.resize(len);
            // We write to data by accessing the address
            file.read(reinterpret_cast<char*>( data.data()), len*sizeof(double));

        }
        else{
            cerr<<" Warining : Can not read initial condition"<< endl;
        }
        return data;
}


bool ReadProblemParameters(const string& filename, double& x_min, double& x_max, double& delta_t, double& alpha){

    ifstream file(filename );

    if(file){
        // I need to point to the end of file 
        file>>  x_min >> x_max >> delta_t >> alpha ;
        return true;
    }
    else{
        cerr<<" Warining Parameters from "<< filename<< endl;
        return false;
    }

}

void WriteOutput( vector<double>& U, int step){
    
    string filename = "./Output/output_" + to_string(step) +".dat";
    ofstream file(filename , ios::binary);
    int len = U.size();

    if(file){
        std::cout << "Writing output to " << filename << "\n";
        file.write(reinterpret_cast<char*>( U.data()), len*sizeof(double));
        
        file.close();
    }
    else{
        
        cerr<<" Warining cannot write output" << endl;
    }

}


