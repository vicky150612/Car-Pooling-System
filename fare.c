<<<<<<< HEAD
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
=======
#include <stdio.h>
int mod(int x)
{
    if(x>=0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}
int max(int a, int b,int c,int d, int e, int f, int g, int h)
{
    int max=a;
    if(b>max)
    {
        max=b;
    }
    if(c>max)
    {
        max=c;
    }
    if(d>max)
    {
        max=d;
    }
    return max;
}
void main()
{
    int noofcust,c=10;
    scanf("%i",&noofcust);
    if(noofcust==1)
    {
        int xsa=10,xea=0,ysa=0,yea=65,fare=1;
        fare = max(mod(xsa),mod(ysa),0,0,0,0,0,0)+max(mod(xea),mod(yea),0,0,0,0,0,0);
        fare=fare*c;
        printf("%i\n",fare);
        printf("A has to pay: %i",fare);
    }
    if(noofcust==2) 
    {
        int xsa=10,xea=0,ysa=0,yea=65,fare=1;
        int xsb=0,xeb=95,ysb=10,yeb=0,pay_a,pay_b,fare_a,fare_b;
        fare = max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xea),mod(yea),mod(xeb),mod(yeb),0,0,0,0);
        fare_a=max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xea),mod(yea),mod(xea),mod(yea),0,0,0,0);
        fare_b=max(mod(xsb),mod(ysb),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xeb),mod(yeb),mod(xeb),mod(yeb),0,0,0,0);
        fare=fare*c*1.1;
        printf("%i \n",fare);
        pay_a=((fare*fare_a)/(fare_a+fare_b));
        pay_b=((fare*fare_b)/(fare_a+fare_b));
        printf("A has to pay: %i\n",pay_a);
        printf("B has to pay: %i\n",pay_b);
    }
    if(noofcust==3)
    {
        int xsa,xea,ysa,yea,xsb,xeb,ysb,yeb,xsc,xec,ysc,yec,fare,fare_a,fare_b,fare_c,pay_a,pay_b,pay_c;
        fare = max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xsc),mod(ysc),0,0)+max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xec),mod(yec),0,0);
        fare_a=max(mod(xsa),mod(ysa),mod(xsa),mod(ysa),0,0,0,0)+max(mod(xea),mod(yea),mod(xea),mod(yea),0,0,0,0);
        fare_b=max(mod(xsb),mod(ysb),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xeb),mod(yeb),mod(xeb),mod(yeb),0,0,0,0);
        fare_c=max(mod(xsc),mod(ysc),mod(xsc),mod(ysc),0,0,0,0)+max(mod(xec),mod(yec),mod(xec),mod(yec),0,0,0,0);
        fare=fare*c*1.15;
        pay_a=((fare*fare_a)/(fare_a+fare_b+fare_c));
        pay_b=((fare*fare_b)/(fare_a+fare_b+fare_c));
        pay_c=((fare*fare_c)/(fare_a+fare_b+fare_c));

    }
    if(noofcust==4)
    {
        int  xsa,xea,ysa,yea,xsb,xeb,ysb,yeb,xsc,xec,ysc,yec,xsd,xed,ysd,yed,fare,fare_a,fare_b,fare_c,fare_d,pay_a,pay_b,pay_c,pay_d;
        fare = max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xsc),mod(ysc),mod(xsd),mod(ysd))+max(mod(xsa),mod(ysa),mod(xsb),mod(ysb),mod(xec),mod(yec),mod(xed),mod(yed));
        fare_a=max(mod(xsa),mod(ysa),mod(xsa),mod(ysa),0,0,0,0)+max(mod(xea),mod(yea),mod(xea),mod(yea),0,0,0,0);
        fare_b=max(mod(xsb),mod(ysb),mod(xsb),mod(ysb),0,0,0,0)+max(mod(xeb),mod(yeb),mod(xeb),mod(yeb),0,0,0,0);
        fare_c=max(mod(xsc),mod(ysc),mod(xsc),mod(ysc),0,0,0,0)+max(mod(xec),mod(yec),mod(xec),mod(yec),0,0,0,0);
        fare_d=max(mod(xsd),mod(ysd),mod(xsd),mod(ysd),0,0,0,0)+max(mod(xed),mod(yed),mod(xed),mod(yed),0,0,0,0);
        fare=fare*c*1.2;
        pay_a=((fare*fare_a)/(fare_a+fare_b+fare_c+fare_d));
        pay_b=((fare*fare_b)/(fare_a+fare_b+fare_c+fare_d));
        pay_c=((fare*fare_c)/(fare_a+fare_b+fare_c+fare_d));
        pay_d=((fare*fare_d)/(fare_a+fare_b+fare_c+fare_d));
        printf("%i",fare);
    }
}
>>>>>>> 70974af6a1e409d8ebba5fa0e1098441ee7beb05
