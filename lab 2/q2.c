#include <stdio.h>
#include <stdlib.h>

int main(int arg, char *argv[])
{
    char *name = argv[1];
    int pop = atoi(argv[2]);
    char *county = argv[3];
    char *country = argv[4];
    float lat = atof(argv[5]);
    float lon = atof(argv[6]);

    printf("Town name : %s\n", name);
    printf("Population : %d\n",pop);
    printf("County : %s \n",county);
    printf("Country : %s\n",country);
    printf("Location Latitude : %f \n",lat);
    printf("Longitude : %f \n",lon);

    printf("char =%ld byte int =%ld byte float =%ld byte\n",sizeof(char),sizeof(int),sizeof(float));

    int total =sizeof(name)+sizeof(county)+sizeof(country)+sizeof(pop)+sizeof(lat)+sizeof(lon);
    printf("Memory used: %d bytes",total);


    return 0;
}