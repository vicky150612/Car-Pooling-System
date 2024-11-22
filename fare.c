#include <stdio.h>
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
int max(int a, int b, int c, int d, int e, int f, int g, int h)
{
    int max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    if (d > max)
    {
        max = d;
    }
    return max;
}
// void main(int noofcust,int c)
// {
//     if(noofcust==1)
//     {
//         int xsa=10,xea=0,ysa=0,yea=65,fare=1;
//         fare = max(mod(xsa),mod(ysa),0,0,0,0,0,0)+max(mod(xea),mod(yea),0,0,0,0,0,0);
//         fare=fare*c;
//         printf("%i",fare);
//     }
//     if(noofcust==2)
//     {
//         int xsa=10,xea=0,ysa=0,yea=65,fare=1;
//         int xsb=0,xeb=65,ysb=10,yeb=0;
//         fare = max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xea),mod(yea),mod(xeb),mod(yeb),0,0,0,0);
//         fare=fare*c;
//         printf("%i",fare);
//     }
//     if(noofcust==3)
//     {
//         int xsa,xea,ysa,yea,xsb,xeb,ysb,yeb,xsc,xec,ysc,yec,fare;
//         fare =  max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xsc),mod(ysc),0,0)+max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xec),mod(yec),0,0);
//         fare=fare*c;
//         printf("%i",fare);
//     }
//     if(noofcust==4)
//     {
//         int  xsa,xea,ysa,yea,xsb,xeb,ysb,yeb,xsc,xec,ysc,yec,xsd,xed,ysd,yed,fare;
//         fare = max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xsc),mod(ysc),mod(xsd),mod(ysd))+max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xec),mod(yec),mod(xed),mod(yed));
//         fare=fare*c;
//         printf("%i",fare);
//     }
// }