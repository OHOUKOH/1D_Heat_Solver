#include "../Include/IO_handler.hh"
#include<bits/stdc++.h>

using namespace std;
//We define Read and write function 
// Which will allow us to read initial conditions and parameters.

vector<double> Initial_Conditions(const string& filename){
        // We used input file stream to read from the filename
        //We open it in binary mode given that initial conditions are
        //in group of 64 bits
        ifstream file(filename , ios::binary);
        //We need to return a data structure which is the U(t=0,.).
        vector<double> data;

        if(file){
            // I need to point to the end of file 
            file.seekg(0 , ios::end);
            //I need to get the number of 64 bits elment
            int len = file.tellg()/ sizeof(double);
            file.seekg(0 , ios::beg);
            //The return data should have the same size
            data.resize(len);
            // We write to data by accessing the address
            file.read(reinterpret_cast<char*>( data.data()), len*sizeof(double));

        }
        else{
            //If file does not exist/inaccessible/ cannot be opened;

            cerr<<" Warining : Can not read initial condition"<< endl;
        }
        return data;
}


bool Problem_Parameters(const string& filename, double& x_min, double& x_max, double& delta_t, double& alpha){

    // We use input file stream to read data from filename.
    ifstream file(filename );

    if(file){
        // I need to read the content of my problem.ini.
        file>>  x_min >> x_max >> delta_t >> alpha ;
        return true;
    }
    else{
        // We print a runtime warning if the file cannot be opened.
        cerr<<" Warning : we cannot accessed parameters from "<< filename<< endl;
        return false;
    }

}

void Output_dat( vector<double>& U, int step){
    // We ensure we write the output back to the folder Output
    //with the specific format.
    string filename = "./Output/output_" + to_string(step) +".dat";
    // We create the file and open it to write in binary mode.
    ofstream file(filename , ios::binary);
    // The heat at the current ste size if fetch to ensure that 
    //writting in file is performed with the exact number of 64 bits element.
    int len = U.size();

    if(file){
        file.write(reinterpret_cast<char*>( U.data()), len*sizeof(double));
        file.close();
    }
    else{
        //Run time error if the file do not exist or is not opened. 
        cerr<<" Warning : we cannot write a output .dat file" << endl;
    }

}


