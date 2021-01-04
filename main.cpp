#include <iostream>
#include <vector>

#include <remez.hpp>

int main(void)
{
    // ========== Filter Parameter ==========
    const int N = 50;  // FIR filter's order (should be a even number)
    const int M = N/2;
    const int Fp = 0.20;  // Passband edge normalized frequency
    const int Fs = 0.30;  // Stopband edge normalized frequency
    const int S = N*20;  // Frequency split count
    // ========== Filter Parameter ==========

    // ========== Variables ==========
    std::vector<double> x(M + 2);  // Design variables
    std::vector<double> b(M + 2);  // Desired responce vector
    std::vector<std::vector<double>> A(M + 2, std::vector<double>(M + 2));  // Square matrix for simultaneous equation
    // ========== Variables ==========

    // ========== Initialize ==========

    // Calculate the initial reference points
    int PassBandRefPointNum = int((M + 2) * (Fp/(Fp + Fs))) + 1;
    int StopBandRefPointNum = (M + 2) - PassBandRefPointNum;
    InitRefPoint(x, Fp, Fs, PassBandRefPointNum, StopBandRefPointNum);

    
    // ========== Initialize ==========

    return 0;
}