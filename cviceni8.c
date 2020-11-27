#include <stdlib.h>
#include <stdio.h>
struct Radar
{
    double x, y, r;
};
struct Target
{
    double x, y;
};

int isInside(double circle_x, double circle_y,
             double rad, double x, double y)
{
    if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad)
        return 1;
    else
        return 0;
}

int main(void)
{
    char option = ' ';
    double x, y, r;
    int radar_counter = 0, target_counter = 0, input, counter = 0;
    struct Radar *radar;
    struct Target *target;
    target = (struct Target *)malloc(sizeof(double) * 2);
    radar = (struct Radar *)malloc(sizeof(double) * 3);
    printf("Seznam cilu a radaru:\n");
    while (option != EOF)
    {
        option = getchar();
        if (option == 'T')
        {
            input = scanf("%lf %lf", &x, &y);
            if (input != EOF && input == 2)
            {
                //printf("%c %lld %lld\n", option, x, y);
                target[target_counter].x = x;
                target[target_counter].y = y;
                target_counter++;
                target = (struct Target *)realloc(target,sizeof(double) * 2 * (target_counter+1));
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
        else if (option == 'R')
        {
            input = scanf("%lf %lf %lf", &x, &y, &r);
            if (input != EOF && input == 3 && r > 0)
            {
                //printf("%c %lld %lld %lld\n", option, x, y, r);
                radar[radar_counter].x = x;
                radar[radar_counter].y = y;
                radar[radar_counter].r = r;
                radar_counter++;
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
    }
    printf("Pokryti:\n");
    for (int i = 0; i < radar_counter; i++)
    {
        for (int j = 0; j < target_counter; j++)
        {
            if (isInside(radar[i].x, radar[i].y, radar[i].r, target[j].x, target[j].y))
            {
                counter++;
            }
        }
        printf("Radar #%d: %d\n", i, counter);
        counter = 0;
    }
    return 0;
}
