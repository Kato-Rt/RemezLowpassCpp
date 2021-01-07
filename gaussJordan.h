#ifndef _GAUSSJORDAN_H_
#define _GAUSSJORDAN_H_

#include <vector>

/* GaussJordan Elimination */
/* double A[]: N*N square matrix. Indexed as [i + N*j] */
/* double b[]: N vector */
// for c++ vector
std::vector<double> gaussJordan(std::vector<std::vector<double>> a, std::vector<double>& b)
{
    int size = b.size();

    int i, j;

    int ipv;
    double invPiv;

    double tmp;

    for(ipv = 0; ipv < size; ipv++)
    {
        /* set diagonal elements to 1 */
        //invPiv = 1.0 / a[(ipv * size) + ipv];
        invPiv = 1.0 / a[ipv][ipv];

        for(i = 0; i < size; i++)
        {
            //a[(ipv * size) + i] = a[(ipv * size) + i] * invPiv;
            a[ipv][i] = a[ipv][i] * invPiv;
        }
        
        b[ipv] = b[ipv] * invPiv;

        /* set all elements to 0 except diagonal elements */
        for(i = 0; i < size; i++)
        {
            /* ipv stay */
            if(i != ipv)
            {
                //tmp = a[(i*size) + ipv];
                tmp = a[i][ipv];

                for(j = 0; j < size; j++)
                {
                    //a[(i*size) + j] = a[(i*size) + j] - tmp*a[(ipv*size) + j];
                    a[i][j] = a[i][j] - tmp*a[ipv][j];
                }
                b[i] = b[i] - tmp*b[ipv];
            }
        }

    }

    return b;
}

#endif
