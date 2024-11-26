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

int cal_fare(int ride_id, int uid)
{
    int final_fare = 0;
    FILE *f = fopen("passengers.txt", "r");
    char line[150];
    int pass[4];
    int x[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ride, passenger_count;
    int index = 0;
    int numchars = 0;
    int noofcust = 0;
    int arr[5];
    int y[5];
    while (fgets(line, sizeof(line), f))
    {
        sscanf(line, "Ride ID: %d Passenger_count: %d %n", &ride, &passenger_count, &numchars);
        index = numchars;
        sscanf(&line[index], "Passengers: %n", &numchars);
        index += numchars;
        if (ride == ride_id)
        {
            noofcust = passenger_count;
            for (int i = 0; i < passenger_count; i++)
            {
                sscanf(&line[index], "%d %n", &pass[i], &numchars);
                index += numchars;
            }
            sscanf(&line[index], "Cords: %n", &numchars);
            index += numchars;
            for (int i = 0; i < passenger_count; i++)
            {
                sscanf(&line[index], "%d %d %d %d %n", &x[i * 4], &x[i * 4 + 1], &x[i * 4 + 2], &x[i * 4 + 3], &numchars);
                index += numchars;
            }
            break;
        }
    }
    fclose(f);
    if (noofcust == 2)
    {
        int xea = x[0], xsa = x[1], yea = x[2], ysa = x[3], fare = 0;
        int xeb = x[4], xsb = x[5], yeb = x[6], ysb = x[7], pay_a, pay_b, fare_a, fare_b;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        int xcounter = 0, ycounter = 0;
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
            if (ysa == 0)
            {
                onxaxis[xcounter] = mod(xsa);
                xcounter++;
            }
            if (yea == 0)
            {
                onxaxis[xcounter] = mod(xea);
                xcounter++;
            }
            if (ysb == 0)
            {
                onxaxis[xcounter] = mod(xsb);
                xcounter++;
            }
            if (yeb == 0)
            {
                onxaxis[xcounter] = mod(xeb);
                xcounter++;
            }
            if (xsa == 0)
            {
                onyaxis[ycounter] = mod(ysa);
                ycounter++;
            }
            if (xea == 0)
            {
                onyaxis[ycounter] = mod(yea);
                ycounter++;
            }
            if (xsb == 0)
            {
                onyaxis[ycounter] = mod(ysb);
                ycounter++;
            }
            if (xeb == 0)
            {
                onyaxis[ycounter] = mod(yeb);
                ycounter++;
            }
            fare = maxarray(onxaxis, xcounter) + maxarray(onyaxis, ycounter);
        }
        fare = fare * price_per_unit_distance;
        pay_a = ((fare * fare_a) / (fare_a + fare_b));
        pay_b = ((fare * fare_b) / (fare_a + fare_b));
        fare = pay_a + pay_b;
        y[0] = fare;
        y[1] = pay_a;
        y[2] = pay_b;
    }
    if (noofcust == 3)
    {
        int xea = x[0], xsa = x[1], yea = x[2], ysa = x[3], fare;
        int xeb = x[4], xsb = x[5], yeb = x[6], ysb = x[7], xec = x[8], xsc = x[9], yec = x[10], ysc = x[11], pay_a, pay_b, pay_c, fare_a, fare_b, fare_c;
        int sa[2] = {xsa, ysa};
        int ea[2] = {xea, yea};
        fare_a = maxarray(sa, 2) + maxarray(ea, 2);
        int sb[2] = {xsb, ysb};
        int eb[2] = {xeb, yeb};
        fare_b = maxarray(sb, 2) + maxarray(eb, 2);
        int sc[2] = {xsc, ysc};
        int ec[2] = {xec, yec};
        int xcounter = 0, ycounter = 0;
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
            if (ysa == 0)
            {
                onxaxis[xcounter] = mod(xsa);
                xcounter++;
            }
            if (yea == 0)
            {
                onxaxis[xcounter] = mod(xea);
                xcounter++;
            }
            if (ysb == 0)
            {
                onxaxis[xcounter] = mod(xsb);
                xcounter++;
            }
            if (yeb == 0)
            {
                onxaxis[xcounter] = mod(xeb);
                xcounter++;
            }
            if (ysc == 0)
            {
                onxaxis[xcounter] = mod(xsc);
                xcounter++;
            }
            if (yec == 0)
            {
                onxaxis[xcounter] = mod(xec);
                xcounter++;
            }
            if (xsa == 0)
            {
                onyaxis[ycounter] = mod(ysa);
                ycounter++;
            }
            if (xea == 0)
            {
                onyaxis[ycounter] = mod(yea);
                ycounter++;
            }
            if (xsb == 0)
            {
                onyaxis[ycounter] = mod(ysb);
                ycounter++;
            }
            if (xeb == 0)
            {
                onyaxis[ycounter] = mod(yeb);
                ycounter++;
            }
            if (xsc == 0)
            {
                onyaxis[ycounter] = mod(ysc);
                ycounter++;
            }
            if (xec == 0)
            {
                onyaxis[ycounter] = mod(yec);
                ycounter++;
            }
            fare = maxarray(onxaxis, xcounter) + maxarray(onyaxis, ycounter);
        }
        fare = fare * price_per_unit_distance;
        pay_a = ((fare * fare_a) / (fare_a + fare_b + fare_c));
        pay_b = ((fare * fare_b) / (fare_a + fare_b + fare_c));
        pay_c = ((fare * fare_c) / (fare_a + fare_b + fare_c));
        fare = pay_a + pay_b + pay_c;
        y[0] = fare;
        y[1] = pay_a;
        y[2] = pay_b;
        y[3] = pay_c;
    }
    if (noofcust == 4)
    {
        int xea = x[0], xsa = x[1], yea = x[2], ysa = x[3], fare;
        int xeb = x[4], xsb = x[5], yeb = x[6], ysb = x[7], xec = x[8], xsc = x[9], yec = x[10], ysc = x[11], xed = x[12], xsd = x[13], yed = x[14], ysd = x[15], pay_a, pay_b, pay_c, pay_d, fare_a, fare_b, fare_c, fare_d;
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
        int xcounter = 0, ycounter = 0;
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
            if (ysa == 0)
            {
                onxaxis[xcounter] = mod(xsa);
                xcounter++;
            }
            if (yea == 0)
            {
                onxaxis[xcounter] = mod(xea);
                xcounter++;
            }
            if (ysb == 0)
            {
                onxaxis[xcounter] = mod(xsb);
                xcounter++;
            }
            if (yeb == 0)
            {
                onxaxis[xcounter] = mod(xeb);
                xcounter++;
            }
            if (ysc == 0)
            {
                onxaxis[xcounter] = mod(xsc);
                xcounter++;
            }
            if (yec == 0)
            {
                onxaxis[xcounter] = mod(xec);
                xcounter++;
            }
            if (ysd == 0)
            {
                onxaxis[xcounter] = mod(xsd);
                xcounter++;
            }
            if (yed == 0)
            {
                onxaxis[xcounter] = mod(xed);
                xcounter++;
            }
            if (xsa == 0)
            {
                onyaxis[ycounter] = mod(ysa);
                ycounter++;
            }
            if (xea == 0)
            {
                onyaxis[ycounter] = mod(yea);
                ycounter++;
            }
            if (xsb == 0)
            {
                onyaxis[ycounter] = mod(ysb);
                ycounter++;
            }
            if (xeb == 0)
            {
                onyaxis[ycounter] = mod(yeb);
                ycounter++;
            }
            if (xsc == 0)
            {
                onyaxis[ycounter] = mod(ysc);
                ycounter++;
            }
            if (xec == 0)
            {
                onyaxis[ycounter] = mod(yec);
                ycounter++;
            }
            if (xsd == 0)
            {
                onyaxis[ycounter] = mod(ysd);
                ycounter++;
            }
            if (xed == 0)
            {
                onyaxis[ycounter] = mod(yed);
                ycounter++;
            }
            fare = maxarray(onxaxis, xcounter) + maxarray(onyaxis, ycounter);
        }
        fare = fare * price_per_unit_distance;
        pay_a = ((fare * fare_a) / (fare_a + fare_b + fare_c + fare_d));
        pay_b = ((fare * fare_b) / (fare_a + fare_b + fare_c + fare_d));
        pay_c = ((fare * fare_c) / (fare_a + fare_b + fare_c + fare_d));
        pay_d = ((fare * fare_d) / (fare_a + fare_b + fare_c + fare_d));
        fare = pay_a + pay_b + pay_c + pay_d;
        y[0] = fare;
        y[1] = pay_a;
        y[2] = pay_b;
        y[3] = pay_c;
        y[4] = pay_d;
    }
    FILE *file = fopen("fare.txt", "a");
    fprintf(file, "Ride ID: %d Passenger Count: %d Total Fare : ", ride_id, passenger_count);
    for (int i = 0; i < passenger_count + 1; i++)
    {
        fprintf(file, "%d ", y[i]);
    }
    fprintf(file, "\n");
    fclose(file);
    for (int i = 0; i < noofcust + 1; i++)
    {
        if (pass[i] == uid)
        {
            final_fare = y[i + 1];
            break;
        }
    }
    return final_fare;
}