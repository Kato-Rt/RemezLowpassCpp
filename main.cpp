/*
* Program By Kato
* Calcuating Type-I FIR LPF with Remez algorithm
*/

#include <iostream>
#include <vector>

#include "remez.hpp"

int main(void)
{
    // ========== Filter Parameter ==========
    const int N = 50;  // FIR filter's order (should be a even number)
    const int M = N/2;
    const double Fp = 0.20;  // Passband edge normalized frequency
    const double Fs = 0.24;  // Stopband edge normalized frequency
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

    // Desired amplitude responce at the reference points
    for(int i = 0; i < M + 2; i++)
    {
        b[i] = IdealLpfResponse(Fp, Fs, x[i]);
    }

    // Matrix A form x[]
    CalculateAMatrix(A, x);

    // Solving Ax = b for initial x
    // ========== Initialize ==========

    // ========== Remez main loop ==========
    // ========== Remez main loop ==========

    return 0;
}