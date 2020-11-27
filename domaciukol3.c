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
    
    if (y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 ||
        d1 < 1 || d1 > first_Months[m1 - 1] || d2 < 1 || d2 > second_Months[m2 - 1] ||
        h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59)
    {
        return 0;
    }
    
    if (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 == i2){
        cuckoos=cuckooPerHour(h1);
        *cuckoo=cuckoos;
        return 1;
    }
    *cuckoo = cuckoos;
    return 1;
}