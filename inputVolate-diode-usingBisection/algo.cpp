#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


#define IO 1 * pow(10, -12)
#define UT 0.0258563


double diode (double, double, double); // U_p calculation using bisection method
double parseExp ( char* ); // // convert char* to double

int main(int argc, char** argv) {
	
	if(argc != 4) {
		fprintf(stderr, "Nespravny pocet argumentu.\n");
		return 1;
	}

	// parse user input
	double u0vstup 	= parseExp(argv[1]);
	double rvstup 	= parseExp(argv[2]);
	double epsvstup = parseExp(argv[3]);

	double Up = diode(u0vstup, rvstup, epsvstup);
	double Ip;

	if (Up == INFINITY ){
		Ip = INFINITY;
	} else if(isnan( Up ) ) {
		printf("error: invalid arguments\n");
		return 1;
	} else {
		// Ip = (u0vstup - Up)/rvstup;  <= doesnt work 
		Ip = IO * ( exp(Up/UT) - 1);
	}

	printf("Up=%g V\n", Up);
	printf("Ip=%g A\n", Ip);

	return 0;
}


double parseExp(char* exp){ // convert char* to double
	
	// char* "1e-2" => 0.01 double
	// char* "0.5"  => 0.5  double
	// char* ".6"   => 0.6  double

	char* end;

	if(strlen(exp) > 1){
		if (exp[1] == 'e'){ // check if char* contains "e" letter in it
			if (exp[2] == '-'){ // if it does check its 1e+10 or 1e-10 (positive or negative)
				return 1 * pow(10, -strtod(exp+3, &end)); 
			} else {
				return 1 * pow(10, strtod(exp+3, &end));	
			}
			
		} else {
			return strtod(exp, &end); // char* doesnt contain e, simply strtod
		}
	} else {
		return strtod(exp, &end); 
	}
}

double diode (double u0, double r, double eps){
	// calculating Up using bisection method
	// So this function optimizes the value of Up

	double min = 0, max = u0, Up, result, prevUp; 

	if ( u0 == INFINITY ){ // If u0 is infinity return Up as infinity
		Up = INFINITY;
		return Up;
	}
	if ( u0 < 0 ){ // If u0 is negative number, return NAN(Not a number) and error out
		Up = NAN;
		return Up;
	}

	// If Up is valid finite positive number 
	// min = 0
	// max = U0(upperlimit for Up)
	// Up =====> ( min + max ) / 2 ------> until ----> result is less than EPSILON
	// where result = (IO * (exp(Up / UT ) - 1)) - ( (u0 - Up) / r)

	while(1){
		
		Up = (min + max)/2;
		result = (IO * (exp(Up / UT ) - 1)) - ( (u0 - Up) / r);
		if (fabs(result) < eps) {
			return prevUp;
		}
		else if (result < 0){
			min = Up;
		}
		else {
			max = Up;
		}
		prevUp = Up;
	}
}