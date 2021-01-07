#pragma once
#include <vector>
#include <cmath>
#include "Type1Fir.hpp"

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

// 振幅特性から次の参照点を求める
std::vector<double> GetNextRefPoints(std::vector<double> x, int S)
{
    // フィルタ係数より振幅特性を計算
    Type1Fir filter(x);
    auto res = filter.CalcAmplitudeResponce(S);

    // 参照点位置保存場所
    std::vector<double> result;

    // ピーク探索
    for(int i = 1; i < S - 1; i++)
    {
        // 点iの前後の振幅で差を見る
        double front = i - 1;
        double back = i + 1;
        double dFront = res[i] - res[front];
        double dBack = res[i] - res[back];

        // 頂点であれば両方の差分の符号が一致する (積が+)
        if(dFront*dBack > 0)
        {
            double f = i / (2.0 * S);
            result.push_back(f);
        }
    }

    return result;
}
