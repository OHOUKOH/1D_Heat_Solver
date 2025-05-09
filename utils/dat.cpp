#include <bits/stdc++.h>


int main() {
    const int N = 100;
    std::vector<double> data(N);

    // Fill with 100 points from 0 to 1 (inclusive)
    for (int i = 0; i < N; ++i) {
        data[i] = static_cast<double>(i) / (N - 1);
    }

    std::ofstream outfile("Setup/init.dat", std::ios::binary);
    if (!outfile) {
        std::cerr << "Error: could not open file for writing.\n";
        return 1;
    }

    outfile.write(reinterpret_cast<const char*>(data.data()), N * sizeof(double));
    outfile.close();

    std::cout << "File 'Setup/init.dat' written successfully.\n";
    return 0;
}
