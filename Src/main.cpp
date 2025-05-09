#include "Heat_equation.cpp"
#include "IO_handler.cpp"

using namespace std;

int main(){

    //We define the path for our init.dat and problem.ini files
    string initial = "./setup/init.dat";
    string parameters = "./setup/problem.ini";
    
    // We read the initial conditon from ini.dat
    vector<double> initialcondition = ReadInitialConditions(initial);

    // If the initial condition is an empty vector then we signal 
    // an error.
    if(initialcondition.empty()){
        cout<<"Initial condition vector is empty."<< endl;
        return 1;
    }

    // We define the parameters that we will pass to the constructor
    double x_min , x_max , delta_t, alpha;
    // A bool which hold value true if we read the value fo problem.ini
    bool b= ReadProblemParameters( parameters, x_min,  x_max, delta_t, alpha );
    if(!b){
        cout<<"Cannot read problem parameters"<< endl;
        return 1;
    }

    // We create an instance heat equation
    Heatequation1D heat_equation_1D(x_min, x_max, delta_t , alpha,  initialcondition);
    
    //We run 110 simulation
    heat_equation_1D.Runsimulation(110);
    
}