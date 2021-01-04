#pragma once
#include <vector>
#include <cmath>

void InitRefPoint(std::vector<double>& x, double Fp, double Fs, int PassBandRefPointNum, int StopBandRefPointNum)
{
    // Step width for passband
    double StepPassBand = Fp / (PassBandRefPointNum - 1.0);
    // Step width for stopband
    double StepStopBand = (0.5 - Fs) / (StopBandRefPointNum - 1.0);

    for(int i = 0; i < PassBandRefPointNum; i++)
    {
        x[i] = StepPassBand * i;
    }

    for(int i = 0; i < StopBandRefPointNum; i++)
    {
        int index = i + PassBandRefPointNum;
        x[index] = Fs + StepStopBand * i;
    }
}

int IdealLpfResponse(double Fp, double Fs, double f)
{
    if((f >= 0) && (f <= Fp))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CalculateAMatrix(std::vector<std::vector<double>>& A, std::vector<double> x)
{
    int size = x.size();

    for(int i = 0; i < size; i++)
    {
        double f = x[i];
        for(int j = 0; j < size; j++)
        {
            A[i][j] = cos(j * 2 * M_PI * f);
        }
    }

    for(int i = 0; i < size; i++)
    {
        A[i][size - 1] = i % 2 ? -1 : 1;
    }
}
