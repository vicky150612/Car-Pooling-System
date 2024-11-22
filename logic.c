#include <stdio.h>

int route(int xsa, int ysa, int xea, int yea)
{
    if ((xsa == 0 && ysa <= 0 && yea <= 0 && xea > 0 && yea > ysa && xea > xsa) || (xsa > 0 && ysa == 0 && xea > 0 && yea == 0 && xea > xsa)) // S to E
    {
        return 1;
    }
    else if ((xsa == 0 && ysa <= 0 && yea <= 0 && xea < 0 && yea > ysa && xea < xsa) || (xsa < 0 && ysa == 0 && xea < 0 && yea == 0 && xea < xsa)) // S to W
    {
        return 2;
    }
    else if ((xsa == 0 && ysa >= 0 && yea >= 0 && xea < 0 && yea < ysa && xea < xsa) || (xsa < 0 && ysa == 0 && xea < 0 && yea == 0 && xea < xsa)) // N to W
    {
        return 3;
    }
    else if ((xsa == 0 && ysa >= 0 && yea >= 0 && xea > 0 && yea < ysa && xea > xsa) || (xsa > 0 && ysa == 0 && xea > 0 && yea == 0 && xea > xsa)) // N to E
    {
        return 4;
    }
    else if ((xea == 0 && yea <= 0 && ysa <= 0 && xsa > 0 && ysa > yea && xsa > xea) || (xea > 0 && yea == 0 && xsa > 0 && ysa == 0 && xsa > xea)) // E to S
    {
        return 5;
    }
    else if ((xea == 0 && yea <= 0 && ysa <= 0 && xsa < 0 && ysa > yea && xsa < xea) || (xea < 0 && yea == 0 && xsa < 0 && ysa == 0 && xsa < xea)) // W to S
    {
        return 6;
    }
    else if ((xea == 0 && yea >= 0 && ysa >= 0 && xsa < 0 && ysa < yea && xsa < xea) || (xea < 0 && yea == 0 && xsa < 0 && ysa == 0 && xsa < xea)) // W to N
    {
        return 7;
    }
    else if ((xea == 0 && yea >= 0 && ysa >= 0 && xsa > 0 && ysa < yea && xsa > xea) || (xea > 0 && yea == 0 && xsa > 0 && ysa == 0 && xsa > xea)) // E to N
    {
        return 8;
    }
    else if ((xsa == 0 && xea == 0 && ysa < yea)) // N to S
    {
        return 9;
    }
    else if ((xsa == 0 && xea == 0 && ysa > yea)) // S to N
    {
        return 10;
    }
    else if ((ysa == 0 && yea == 0 && xsa < xea)) // E to W
    {
        return 11;
    }
    else if ((ysa == 0 && yea == 0 && xsa > xea)) // W to E
    {
        return 12;
    }
    else
    {
        return 0;
    }
}
int mod(int x)
{
    if (x >= 0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}
int maxarray(int *x, int n)
{
    int max = x[0];
    for (int i = 0; i < n; i++)
    {
        if (max < x[i])
        {
            max = x[i];
        }
    }
    return max;
}
int minarray(int *x, int n)
{
    int max = x[0];
    for (int i = 0; i < n; i++)
    {
        if (max > x[i])
        {
            max = x[i];
        }
    }
    return max;
}
void fare_calculate(int c, int *x, int noofcust)
{
    if (noofcust == 1)
    {
        int xsa = x[0], xea = x[1], ysa = x[2], yea = x[3], fare;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        fare = maxarray(sa, 2) + maxarray(ea, 2);
        fare = fare * c;
        *(x + 0) = fare;
        *(x + 1) = fare;
    }
    if (noofcust == 2)
    {
        int xsa = x[0], xea = x[1], ysa = x[2], yea = x[3], fare;
        int xsb = x[4], xeb = x[5], ysb = x[6], yeb = x[7], pay_a, pay_b, fare_a, fare_b;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        fare_a = maxarray(sa, 2) + maxarray(ea, 2);
        int sb[2] = {xsb, ysb};
        int eb[2] = {xeb, yeb};
        fare_b = maxarray(sb, 2) + maxarray(eb, 2);
        if ((route(xsa, ysa, xea, yea) == 10) || (route(xsa, ysa, xea, yea) == 9))
        {
            int y[4] = {ysa, yea, ysb, yeb};
            fare = maxarray(y, 4) - minarray(y, 4);
        }
        else if ((route(xsa, ysa, xea, yea) == 11) || (route(xsa, ysa, xea, yea) == 12))
        {
            int x[4] = {xsa, xea, xsb, xeb};
            fare = maxarray(x, 4) - minarray(x, 4);
        }
        else
        {
            int onxaxis[4], onyaxis[4];
            (ysa == 0) ? onxaxis[0] = mod(xsa) : 1;
            (yea == 0) ? onxaxis[1] = mod(xea) : 1;
            (ysb == 0) ? onxaxis[2] = mod(xsb) : 1;
            (yeb == 0) ? onxaxis[3] = mod(xeb) : 1;
            (xsa == 0) ? onyaxis[0] = mod(ysa) : 1;
            (xea == 0) ? onyaxis[1] = mod(yea) : 1;
            (xsb == 0) ? onyaxis[2] = mod(ysb) : 1;
            (xeb == 0) ? onyaxis[3] = mod(yeb) : 1;
            fare = maxarray(onxaxis, 4) + maxarray(onyaxis, 4);
        }
        fare = fare * c;
        pay_a = ((fare * fare_a) / (fare_a + fare_b));
        pay_b = ((fare * fare_b) / (fare_a + fare_b));
        fare = pay_a + pay_b;
        *(x + 0) = fare;
        *(x + 1) = pay_a;
        *(x + 2) = pay_b;
    }
    if (noofcust == 3)
    {
        int xsa = x[0], xea = x[1], ysa = x[2], yea = x[3], fare;
        int xsb = x[4], xeb = x[5], ysb = x[6], yeb = x[7], xsc = x[8], xec = x[9], ysc = x[10], yec = x[11], pay_a, pay_b, pay_c, fare_a, fare_b, fare_c;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        fare_a = maxarray(sa, 2) + maxarray(ea, 2);
        int sb[2] = {xsb, ysb};
        int eb[2] = {xeb, yeb};
        fare_b = maxarray(sb, 2) + maxarray(eb, 2);
        int sc[2] = {xsc, ysc};
        int ec[2] = {xec, yec};
        fare_c = maxarray(sc, 2) + maxarray(ec, 2);
        if ((route(xsa, ysa, xea, yea) == 10) || (route(xsa, ysa, xea, yea) == 9))
        {
            int y[6] = {ysa, yea, ysb, yeb, ysc, yec};
            fare = maxarray(y, 6) - minarray(y, 6);
        }
        else if ((route(xsa, ysa, xea, yea) == 11) || (route(xsa, ysa, xea, yea) == 12))
        {
            int x[6] = {xsa, xea, xsb, xeb, xsc, xec};
            fare = maxarray(x, 6) - minarray(x, 6);
        }
        else
        {
            int onxaxis[6], onyaxis[6];
            (ysa == 0) ? onxaxis[0] = mod(xsa) : 1;
            (yea == 0) ? onxaxis[1] = mod(xea) : 1;
            (ysb == 0) ? onxaxis[2] = mod(xsb) : 1;
            (yeb == 0) ? onxaxis[3] = mod(xeb) : 1;
            (ysc == 0) ? onxaxis[4] = mod(xsc) : 1;
            (yec == 0) ? onxaxis[5] = mod(xec) : 1;
            (xsa == 0) ? onyaxis[0] = mod(ysa) : 1;
            (xea == 0) ? onyaxis[1] = mod(yea) : 1;
            (xsb == 0) ? onyaxis[2] = mod(ysb) : 1;
            (xeb == 0) ? onyaxis[3] = mod(yeb) : 1;
            (xsc == 0) ? onyaxis[4] = mod(ysc) : 1;
            (xec == 0) ? onyaxis[5] = mod(yec) : 1;
            fare = maxarray(onxaxis, 6) + maxarray(onyaxis, 6);
        }
        fare = fare * c;
        pay_a = ((fare * fare_a) / (fare_a + fare_b + fare_c));
        pay_b = ((fare * fare_b) / (fare_a + fare_b + fare_c));
        pay_c = ((fare * fare_c) / (fare_a + fare_b + fare_c));
        fare = pay_a + pay_b + pay_c;
        *(x + 0) = fare;
        *(x + 1) = pay_a;
        *(x + 2) = pay_b;
        *(x + 3) = pay_c;
    }
    if (noofcust == 4)
    {
        int xsa = x[0], xea = x[1], ysa = x[2], yea = x[3], fare;
        int xsb = x[4], xeb = x[5], ysb = x[6], yeb = x[7], xsc = x[8], xec = x[9], ysc = x[10], yec = x[11], xsd = x[12], xed = x[13], ysd = x[14], yed = x[15], pay_a, pay_b, pay_c, pay_d, fare_a, fare_b, fare_c, fare_d;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        fare_a = maxarray(sa, 2) + maxarray(ea, 2);
        int sb[2] = {xsb, ysb};
        int eb[2] = {xeb, yeb};
        fare_b = maxarray(sb, 2) + maxarray(eb, 2);
        int sc[2] = {xsc, ysc};
        int ec[2] = {xec, yec};
        fare_c = maxarray(sc, 2) + maxarray(ec, 2);
        int sd[2] = {xsd, ysd};
        int ed[2] = {xed, yed};
        fare_d = maxarray(sd, 2) + maxarray(ed, 2);
        if ((route(xsa, ysa, xea, yea) == 10) || (route(xsa, ysa, xea, yea) == 9))
        {
            int y[8] = {ysa, yea, ysb, yeb, ysc, yec, ysd, yed};
            fare = maxarray(y, 8) - minarray(y, 8);
        }
        else if ((route(xsa, ysa, xea, yea) == 11) || (route(xsa, ysa, xea, yea) == 12))
        {
            int x[8] = {xsa, xea, xsb, xeb, xsc, xec, xsd, xed};
            fare = maxarray(x, 8) - minarray(x, 8);
        }
        else
        {
            int onxaxis[8], onyaxis[8];
            (ysa == 0) ? onxaxis[0] = mod(xsa) : 1;
            (yea == 0) ? onxaxis[1] = mod(xea) : 1;
            (ysb == 0) ? onxaxis[2] = mod(xsb) : 1;
            (yeb == 0) ? onxaxis[3] = mod(xeb) : 1;
            (ysc == 0) ? onxaxis[4] = mod(xsc) : 1;
            (yec == 0) ? onxaxis[5] = mod(xec) : 1;
            (ysd == 0) ? onxaxis[6] = mod(xsd) : 1;
            (yed == 0) ? onxaxis[7] = mod(xed) : 1;
            (xsa == 0) ? onyaxis[0] = mod(ysa) : 1;
            (xea == 0) ? onyaxis[1] = mod(yea) : 1;
            (xsb == 0) ? onyaxis[2] = mod(ysb) : 1;
            (xeb == 0) ? onyaxis[3] = mod(yeb) : 1;
            (xsc == 0) ? onyaxis[4] = mod(ysc) : 1;
            (xec == 0) ? onyaxis[5] = mod(yec) : 1;
            (xsd == 0) ? onyaxis[6] = mod(ysd) : 1;
            (xed == 0) ? onyaxis[7] = mod(yed) : 1;
            fare = maxarray(onxaxis, 8) + maxarray(onyaxis, 8);
        }
        fare = fare * c;
        pay_a = ((fare * fare_a) / (fare_a + fare_b + fare_c + fare_d));
        pay_b = ((fare * fare_b) / (fare_a + fare_b + fare_c + fare_d));
        pay_c = ((fare * fare_c) / (fare_a + fare_b + fare_c + fare_d));
        pay_d = ((fare * fare_d) / (fare_a + fare_b + fare_c + fare_d));
        fare = pay_a + pay_b + pay_c + pay_d;
        *(x + 0) = fare;
        *(x + 1) = pay_a;
        *(x + 2) = pay_b;
        *(x + 3) = pay_c;
        *(x + 4) = pay_d;
    }
}
