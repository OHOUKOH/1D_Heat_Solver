#include "../Include/Heat_equation.hh"
#include "../Include/IO_handler.hh"


Heatequation1D::Heatequation1D(double& xmin, double& xmax, double& dt , double& diffusioncoefficient, vector<double>& initialcondition): grid(initialcondition.size()), x_min(xmin), x_max(xmax), delta_t(dt) , alpha(diffusioncoefficient), U(initialcondition) {
    // For grid points we have (grid-1) interval
    dx = (x_max - x_min)/ grid-1;
    // 
    U_t.resize(grid);

}

void Heatequation1D::step( ){

    //Before computing the centered-finite-differences
    // And first order explicit time stepping We check the stability condition
    //Courant–Friedrichs–Lewy condition
    double lambda = alpha*delta_t / (dx*dx);

    // We ensure Dirichlet condition
    U_t[0] = U[0];
    U_t[grid-1] = U_t[grid-1];

    if( lambda>0.5){
        // If the stability condition is not satisfy 
        //We print a warning a runing times
        cerr<< "Warning: Stability condition not satisfy"<< endl;
    }

    for(int i=1 ; i< grid-1; i++){

        U_t[i] = U[i] - alpha*lambda*(U[i+1] - 2*U[i] + U[i-1]);
    }

    
    // We update U for the next time t

    U= U_t;

}

const vector<double>& Heatequation1D::getsimulation() const{

    return U;
}


void Heatequation1D::Runsimulation( int step){

    for(int i=0 ; i< step; i++){

        Heatequation1D::step();

        if(i%10 == 0){

            vector<double> U_ = Heatequation1D::getsimulation();

            WriteOutput(U_, i);
        }
    }
}


