#pragma once
#include <vector>

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