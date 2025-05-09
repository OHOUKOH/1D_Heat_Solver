#include "Heat_equation.cpp"
#include "IO_handler.cpp"

using namespace std;

int main(){

    //We define the path 
    string initial = "./setup/init.dat";
    string parameters = "./setup/problem.ini";

    vector<double> initialcondition = ReadInitialConditions(initial);

    if(initialcondition.empty()){
        cout<<"No initial Condition"<< endl;
        return 1;
    }

  
    double x_min , x_max , delta_t, alpha , dx;

    bool b= ReadProblemParameters( parameters, x_min,  x_max, delta_t, alpha );

    if(!b){
        cout<<"Cannot read problem parameters"<< endl;
        return 1;
    }

    Heatequation1D solver(x_min, x_max, delta_t , alpha,  initialcondition);
    printf("1111111111111");
    solver.Runsimulation(110);
}