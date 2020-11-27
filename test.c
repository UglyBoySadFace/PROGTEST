#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int isPrestupni(int year)
{
  if (year % 4000 == 0)
  {
    return 0;
  }
  else if (year % 400 == 0)
  {
    return 1;
  }
  else if (year % 100 == 0)
  {
    return 0;
  }
  else if (year % 4 == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int cuckooPerHour(int hour)
{
  if (hour > 12)
  {
    return hour - 12;
  }
  else
  {
    return hour;
  }
}
int cuckooClock(int y1, int m1, int d1, int h1, int i1,
                int y2, int m2, int d2, int h2, int i2,
                long long int *cuckoo)
{
    long long int cuckoos = 0;
    int first_Months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int second_Months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isPrestupni(y1))
    {
        first_Months[1] = 29;
    }
    if (isPrestupni(y2))
    {
        second_Months[1] = 29;
    }
    if (y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 ||
        d1 < 1 || d1 > first_Months[m1 - 1] || d2 < 1 || d2 > second_Months[m2 - 1] ||
        h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59)
    {
        return 0;
    }
    if ((y1 - y2) < 0)
    {
        return 0;
    }
    else if (y1 == y2)
    {
        if (m1 > m2)
        {
            return 0;
        }
        if (m1 == m2)
        {
            if (d1 > d2)
            {
                return 0;
            }
            if (d1 == d2)
            {
                if (h1 > h2)
                {
                    return 0;
                }
                if (h1 == h2)
                {
                    if (i1 > i2)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    if ((h1 == 0 || h1 == 12) && i1 == 0)
    {
        cuckoos += 12;
    }
    while (!(y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 == i2))
    {
        if (i1 == 30)
        {
            cuckoos += 1;
        }
        i1++;
        if (i1 == 60)
        {
            h1++;
            i1 = 0;
            cuckoos += cuckooPerHour(h1);
            if (h1 == 24)
            {
                h1 = 0;
                d1++;
                if (d1 == first_Months[m1 - 1] + 1)
                {
                    d1 = 1;
                    m1++;
                    if (m1 == 13)
                    {
                        m1 = 1;
                        y1++;
                        if (isPrestupni(y1))
                        {
                            first_Months[1] = 29;
                        }
                        else
                        {
                            first_Months[1] = 28;
                        }
                    }
                }
            }
        }
        
    }
    *cuckoo = cuckoos;
    return 1;
}
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  long long int cuckoo;
  assert(cuckooClock(2013, 10, 1, 13, 15,
                     2013, 10, 1, 18, 45, &cuckoo) == 1 &&
         cuckoo == 26);
  assert(cuckooClock(2013, 10, 1, 13, 15,
                     2013, 10, 2, 11, 20, &cuckoo) == 1 &&
         cuckoo == 165);
  assert(cuckooClock(2013, 1, 1, 13, 15,
                     2013, 10, 5, 11, 20, &cuckoo) == 1 &&
         cuckoo == 49845);
  assert(cuckooClock(2012, 1, 1, 13, 15,
                     2012, 10, 5, 11, 20, &cuckoo) == 1 &&
         cuckoo == 50025);
  assert(cuckooClock(1900, 1, 1, 13, 15,
                     1900, 10, 5, 11, 20, &cuckoo) == 1 &&
         cuckoo == 49845);
  assert(cuckooClock(2013, 10, 1, 0, 0,
                     2013, 10, 1, 12, 0, &cuckoo) == 1 &&
         cuckoo == 102);
  assert(cuckooClock(2013, 10, 1, 0, 15,
                     2013, 10, 1, 0, 25, &cuckoo) == 1 &&
         cuckoo == 0);
  assert(cuckooClock(2013, 10, 1, 12, 0,
                     2013, 10, 1, 12, 0, &cuckoo) == 1 &&
         cuckoo == 12);
  assert(cuckooClock(2013, 11, 1, 12, 0,
                     2013, 10, 1, 12, 0, &cuckoo) == 0);
  assert(cuckooClock(2013, 10, 32, 12, 0,
                     2013, 11, 10, 12, 0, &cuckoo) == 0);
  assert(cuckooClock(2100, 2, 29, 12, 0,
                     2100, 2, 29, 12, 0, &cuckoo) == 0);
  assert(cuckooClock(2400, 2, 29, 12, 0,
                     2400, 2, 29, 12, 0, &cuckoo) == 1 &&
         cuckoo == 12);
  return 0;
}
#endif /* __PROGTEST__ */
