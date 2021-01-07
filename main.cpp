/*
* Program By Kato
* Calcuating Type-I FIR LPF with Remez algorithm
*/

#include <iostream>
#include <vector>
#include <algorithm>

#include "remez.hpp"
#include "Type1Fir.hpp"
#include "gaussJordan.h"

int main(void)
{
    // ========== Filter Parameter ==========
    const int N = 20;  // FIR filter's order (should be a even number)
    const int M = N/2;
    const double Fp = 0.20;  // Passband edge normalized frequency
    const double Fs = 0.30;  // Stopband edge normalized frequency
    const int S = N*20;  // Frequency split count
    // ========== Filter Parameter ==========

    // ========== Variables ==========
    std::vector<double> refPoints(M + 2);  // Design variables
    std::vector<double> b(M + 2);  // Desired responce vector
    std::vector<std::vector<double>> A(M + 2, std::vector<double>(M + 2));  // Square matrix for simultaneous equation
    // ========== Variables ==========

    // ========== Initialize ==========
    // Calculate the initial reference points
    int PassBandRefPointNum = int((M + 2)/2);
    int StopBandRefPointNum = (M + 2) - PassBandRefPointNum;
    InitRefPoint(refPoints, Fp, Fs, PassBandRefPointNum, StopBandRefPointNum);

    // Desired amplitude responce at the reference points
    for(int i = 0; i < M + 2; i++)
    {
        b[i] = IdealLpfResponse(Fp, Fs, refPoints[i]);
    }

    // Matrix A form x[]
    CalculateAMatrix(A, refPoints);

    // Solving Ax = b for initial x
    gaussJordan(A, b);
    // ========== Initialize ==========

    // 初期値検証
    Type1Fir filter(b);
    filter.DumpAmplitudeResponce(S, "initialRes");

    // ========== Remez main loop ==========

    // Step 1: 参照点を振幅特性をもとに選択
    refPoints = GetNextRefPoints(b, S);
    // 決め打ちの参照点
    refPoints.push_back(0.0);
    refPoints.push_back(Fp);
    refPoints.push_back(Fs);
    refPoints.push_back(0.5);

    // Sortで並べ直す
    std::sort(refPoints.begin(), refPoints.end());

    for(int i = 0; i < refPoints.size(); i++)
    {
        printf("%3d %lf\n", i, refPoints[i]);
    }


    // ========== Remez main loop ==========

    return 0;
}