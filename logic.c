#include <stdio.h>
int route(int xsa,int ysa,int xea,int yea)
{
    if ((xsa==0 && ysa<=0 && yea<=0 && xea>0 && yea>ysa && xea>xsa)||(xsa>0 && ysa==0 && xea>0 && yea==0 && xea>xsa)) //S to E
    {
        return 1;
    }
    else if ((xsa==0 && ysa<=0 && yea<=0 && xea<0 && yea>ysa && xea<xsa)||(xsa<0 && ysa==0 && xea<0 && yea==0 && xea<xsa))//S to W
    {
        return 2;
    }
    else if ((xsa==0 && ysa>=0 && yea>=0 && xea<0 && yea<ysa && xea<xsa)||(xsa<0 && ysa==0 && xea<0 && yea==0 && xea<xsa))//N to W
    {
        return 3;
    }
    else if ((xsa==0 && ysa>=0 && yea>=0 && xea>0 && yea<ysa && xea>xsa)||(xsa>0 && ysa==0 && xea>0 && yea==0 && xea>xsa))  //N to E
    {
        return 4;
    }
    else if ((xea==0 && yea<=0 && ysa<=0 && xsa>0 && ysa>yea && xsa>xea)||(xea>0 && yea==0 && xsa>0 && ysa==0 && xsa>xea))  //E to S
    {
        return 5;
    }
    else if ((xea==0 && yea<=0 && ysa<=0 && xsa<0 && ysa>yea && xsa<xea)||(xea<0 && yea==0 && xsa<0 && ysa==0 && xsa<xea))  //W to S
    {
        return 6;
    }
    else if ((xea==0 && yea>=0 && ysa>=0 && xsa<0 && ysa<yea && xsa<xea)||(xea<0 && yea==0 && xsa<0 && ysa==0 && xsa<xea))  //W to N
    {
        return 7;
    }
    else if ((xea==0 && yea>=0 && ysa>=0 && xsa>0 && ysa<yea && xsa>xea)||(xea>0 && yea==0 && xsa>0 && ysa==0 && xsa>xea))  //E to N
    {
        return 8;
    }
    else if(xsa==0 && xea==0 && ysa<yea) && (xsb==0 && xeb==0 && ysb<yeb) // N to S
    {
        return 9;
    }
    else if(xsa==0 && xea==0 && ysa>yea) && (xsb==0 && xeb==0 && ysb>yeb) // S to N
    {
        return 10;
    }
    else if(ysa==0 && yea==0 && xsa<xea) && (ysb==0 && yeb==0 && xsb<xeb) // E to W
    {
        return 11;
    }
    else if(ysa==0 && yea==0 && xsa>xea) && (ysb==0 && yeb==0 && xsb>xeb) // W to E
    {
        return 12;
    }    
    else
    {
        return 0;
    }        
}

void main()
{
    int xsa,xsb,ysa,ysb,xea,xeb,yea,yeb;
    xsa = 0,xsb=0,ysa=-5,ysb=-10,xea=5,xeb=10,yea=1,yeb=0;
    printf("%d",route(0,0,-5,-10,5,10,1,0));

}