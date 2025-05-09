#ifndef __HEATEQUATION1D__
#define __HEATEQUATION1D__

#include<bits/stdc++.h>

using namespace std;

// We need to define a class for encapsulation

class Heatequation1D{

    private:
        
        int grid;
        double x_min , x_max , delta_t, alpha , dx;
        vector<double> U, U_t;
    
    
    public:

        Heatequation1D(double& xmin, double& xmax, double& dt , double& diffusioncoefficient, vector<double>& initialcondition);
        //Defining a single simulation
        void step();
        // Runing simulation given time step
        void Runsimulation( int step);
        // Retruning the temperature without modification 
        const vector<double>& getsimulation() const;
};

#endif