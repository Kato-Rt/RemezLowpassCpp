#pragma once
#include <vector>
#include <cmath>
#include <stdio.h>

class Type1Fir
{
    private:
    std::vector<double> a;

    public:
    Type1Fir(std::vector<double> a)
    {
        this->a = a;
        a.pop_back(); //今回渡される係数の一番最後は最大誤差だから捨てる
    }

    // 指定の周波数での振幅を得る
    double GetAmpitudeAt(double f)
    {
        double w = 2 * M_PI * f;
        double sum = 0;

        for(int i = 0; i < a.size(); i++)
        {
            sum += a[i] * cos(i*w);
        }

        return sum;
    }

    // 振幅特性全体を分割数Sで計算する
    std::vector<double> CalcAmplitudeResponce(int S)
    {
        std::vector<double> result(S);

        for(int i = 0; i < S; i++)
        {
            double f = i/(2.0 * S);
            result[i] = GetAmpitudeAt(f);
        }

        return result;
    }

    int DumpAmplitudeResponce(int S, const char* filename)
    {
        FILE* fp;
        fp = fopen(filename, "w");
        if(fp == nullptr) return -1;

        std::vector<double> res = CalcAmplitudeResponce(S);

        for(int i = 0; i < S; i++)
        {
            double f = i/(2.0*S);
            fprintf(fp, "%lf %lf\n", f, res[i]);
        }

        fclose(fp);
        return 0;
    }

};