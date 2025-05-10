#include<bits/stdc++.h>

int main() {

    std::ofstream file("Setup/problem.ini");
    if (!file) {
        std::cerr << "Warning: failed to open 'Setup/problem.ini' for writing.\n";
        return 1;
    }

    double x_min = 0.0;
    double x_max = 1.0;
    double delta_t = 0.5 / 110.0;
    double diffusion_coefficient = 1.0;

    file << "x_min = " << x_min << "\n";
    file << "x_max = " << x_max << "\n";

    std::cout<<delta_t<< std::endl;
    
    file << "delta_t = " << delta_t << "\n";

    
    file << "diffusion_coefficient = " << diffusion_coefficient << "\n";

    file.close();
    std::cout << "The Setup/problem.ini file is written successfully.\n";

    return 0;
}
