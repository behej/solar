#include <stdio.h>
#include <math.h>

int dayRank(int day, int month, int year);
double deg2rad(double angle);
double rad2deg(double angle);
double anomalieMoyenne(int j);
double anomalieMoyenne2(double J);
double equationCentre(double M);
double longitudeVraie(double C, int j);
double reductionEquateur(double L);
double equationTemps(double C, double R);
double declinaison(double L);
double angleHoraireSoleil(double dec, double lat);
double dateJulienne(int DD, int MM, int YYYY, int hh, int mm, int ss);
    
    

int main(void)
{
  int day = 13;
  int month = 04;
  int year = 2014;
  
  double lat_deg = 45.757500;
  double lon_deg = 4.833000;


  double lat_rad = deg2rad(lat_deg);
  double lon_rad = deg2rad(lon_deg);


  printf("Calcul de l'ephemeride du %02d/%02d/%04d\n", day, month, year);
  printf("Step 1: Calcul du rang j du jour\n");


//FILE *temp = fopen("data.dat", "w");

    printf("1er janvier 2000\n");
    printf("Theorique: J=2451545.0\n");
    printf("Calcule:   J=%f\n", dateJulienne(1,1,2000,12,0,0));

    printf("1er janvier -4712\n");
    printf("Theorique: J=0.0\n");
    printf("Calcule:   J=%f\n", dateJulienne(1,1,-4712,12,0,0));
    
    printf("==================\n");
    
    int j= dayRank(day, month, year);
    printf("j = %d\n", j);

    printf("Step 2: declinaison solaire\n");
    
//  for (j = 1 ; j <=365 ; j++)
//  {
    double M = anomalieMoyenne(j);
    M = anomalieMoyenne2(dateJulienne(day, month, year, 12, 0, 0));
    double C = equationCentre(M);
    double L = longitudeVraie(C, j);
    double R = reductionEquateur(L);
    double eqnTps = equationTemps(C, R);
    double sinDec = declinaison(L);
    double dec_rad = asin(sinDec);
    double cosHo = angleHoraireSoleil(dec_rad, lat_rad);
    double HL = (double)12.0 - rad2deg(acos(cosHo))/(double)15.0 + eqnTps/(double)60.0 + lon_deg/(double)15.0 + 1;
    
    
    printf("M = %f\n", M);
    printf("C = %f\n", C);
    printf("L = %f\n", L);
    printf("R = %f\n", R);
    printf("Equation du temps: %f\n", eqnTps);
    printf("Declinaison: %f \n", rad2deg(dec_rad));
    
    printf("Step 3 : angle horaire\n");
    printf("cos(Ho) = %f\n", cosHo);
    
    printf("Step 4 : Heure du lever\n");
    printf("Heure legale: %f\n", HL);

//    fprintf(temp, "%lf %lf\n", eqnTps, dec);

//  }  
  
  
  //FILE *gnuplot = popen("gnuplot", "w");
  
  
  
//  fclose(temp);
  
  

  return 0;
}





int dayRank(int day, int month, int year)
{
    int N1 = (month * 275) / 9;
    int N2 = (month + 9) / 12;
    int K = 1 + (int)((year - 4 * ((int)(year/4)) + 2) / 3);
    
    return (N1 - N2 * K + day - 30);
}


double anomalieMoyenne(int j)
{
    return ((double)356.8 + (double)0.9856 * (double)(j-1));
}

double anomalieMoyenne2(double J)
{
    return ((double)357.5291 + (double)0.98560028 * (double)(J-2451545));
}



double equationCentre(double M)
{
    double Mrad = (M * (double)2.0 * (double)M_PI) / (double)360.0;
    return ((double)1.91378 * (double)sin(Mrad) + (double)(0.02) * (double)sin((double)2.0 * Mrad));
}


double longitudeVraie(double C, int j)
{
    return ((double)280.0 + C + (double)0.9856*(double)j);

}



double reductionEquateur(double L)
{
    double Lrad = (L * (double)2.0 * (double)M_PI) / (double)360.0;
    return ((double)(-2.46522) * sin((double)2.0 * Lrad) + (double)0.05303 * sin((double)4.0 * Lrad));
}   



double equationTemps(double C, double R)
{
    return ((C + R) * (double)4.0);
}


double declinaison(double L)
{
    double Lrad =  (L * (double)2.0 * (double)M_PI) / (double)360.0;
    return ((double)0.39774 * sin(Lrad));
}



double angleHoraireSoleil(double dec, double lat)
{
    double cosHo, num, den;
    
    num = (double)(-0.01065) - (sin(dec) * sin(lat));
    den = cos(dec) * cos(lat);
    cosHo = num / den;
    
    return cosHo;
}



double deg2rad(double angle)
{
    return ((angle * (double)M_PI) / (double)180.0);
}

double rad2deg(double angle)
{
    return ((angle * (double)180.0) / (double)M_PI);
}


double dateJulienne(int DD, int MM, int YYYY, int hh, int mm, int ss)
{
    if ((MM == 1) || (MM == 2)) {
        YYYY--;
        MM += 12;
    }        

    int C = (int)(YYYY/100);
    double T = (double)hh/(double)24.0 + (double)mm/(double)1440.0 + (double)ss/(double)86400.0;
    int B = 2 - C + (int)((double)C/(double)4.0);
        
    
    
    double J = (double)(int)((double)365.25*(double)(YYYY+4716))
             + (double)(int)(30.6001*(double)(MM+1))
             + (double)DD
             + T
             + (double)B
             - (double)1524.5;
    return J;


}
    

