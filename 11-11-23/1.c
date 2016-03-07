/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<string.h>
#include<math.h>

#define TABLELENGTH 20
#define MAXFNAMELENGTH 30
#define CLOSE_ENOUGH 0.001

struct
{
	char name[MAXFNAMELENGTH];
	double (*f)(double);
} functiontable[TABLELENGTH];

unsigned int functions;

double sin2(double x);
double MIN(double a, double b){return a<b?a:b;}
double MAX(double a, double b){return a>b?a:b;}
double apply(const char* fname, double x);
double findzero(const char *fname, double x0, double x1);
double ffindzero(double (*f)(double), double x0, double x1);
void plotfunction(const char *fname, double x0, double x1);
void fplotfunction(double (*f)(double), double x0, double x1);

int main(void)
{
	char name[20];
	double a, b;
	/* SET AVAILABLE FUNCTIONS */
	strcpy(functiontable[0].name, "sin");
	functiontable[0].f = sin;
	++ functions;

	strcpy(functiontable[1].name, "cos");
	functiontable[1].f = cos;
	++ functions;

	strcpy(functiontable[2].name, "tan");
	functiontable[2].f = tan;
	++ functions;

	strcpy(functiontable[3].name, "log");
	functiontable[3].f = log;
	++ functions;

	strcpy(functiontable[4].name, "sqrt");
	functiontable[4].f = sqrt;
	++ functions;

	strcpy(functiontable[5].name, "sin2");
	functiontable[5].f = &sin2;
	++ functions;

	printf("Function name and parameters: ");
	scanf("%s %lf %lf", name, &a, &b);
	printf("f(a): %.2lf, f(b): %.2lf, zero: %.2lf\n", apply(name, a), apply(name, b), findzero(name, a, b));
	plotfunction(name, a, b);
	return 0;
}

double apply(const char* fname, double x)
{
	for(unsigned int f = 0; f < functions; ++ f)
		if(!strcmp(fname, functiontable[f].name))
			return (*(functiontable[f].f))(x);

	return -1000000000;
}

double findzero(const char *fname, double x0, double x1)
{
	for(unsigned int f = 0; f < functions; ++ f)
		if(!strcmp(fname, functiontable[f].name))
			return ffindzero(functiontable[f].f, x0, x1);

	return -1000000000;
}

double ffindzero(double (*f)(double), double x0, double x1)
{
	double mid,
		   fmid;
	while(x1 - x0 > CLOSE_ENOUGH)
	{
		mid = (x0 + x1) / 2;
		fmid = f(mid);
		if(fmid < 0)
			x1 = mid;

		else if(fmid > 0)
			x0 = mid;

		else
			return mid;

	}

	return (x1 + x0) / 2;
}

void plotfunction(const char *fname, double x0, double x1)
{
	for(unsigned int f = 0; f < functions; ++ f)
		if(!strcmp(fname, functiontable[f].name))
		{
			fplotfunction(functiontable[f].f, x0, x1);
			return;
		}

	return;
}

void fplotfunction(double (*f)(double), double x0, double x1)
{
	const double eps = 0.0001;
	const int height = 20,
			  width = 80;
	char result[height + 2][width + 2];
	double maks = f(x0), //func max
		   mins = f(x1), // func min
		   maksd = (f(x0 + eps) - f(x0))/eps, //deriverative max
		   minsd = (f(x1 + eps) - f(x1))/eps, //deriverative min
		   stepx = (x1 - x0) / width, // step in x-axis
		   stepy = 0; // step in y-axis

	/* COUNT MIN AND MAX */
	for(int i = 0; i < width; ++ i)
	{
		maks = MAX(maks, f(x0 + stepx * i));
		mins = MIN(mins, f(x0 + stepx * i));
		maksd = MAX(maksd, (f(x0 + stepx * i + eps) - f(x0 + stepx * i)) / eps);
		minsd = MIN(minsd, (f(x0 + stepx * i + eps) - f(x0 + stepx * i)) / eps);
	}

	/* DRAW FUNCTION */
	puts("Function");
	stepy = (maks - mins) / height;
	memset(result, ' ', sizeof(result));
	for(int w = 0; w < width; ++ w)
		result[(int)floor((maks - f(x0 + stepx*w)) / stepy)][w] = '*';

	/* DRAW Y AXIS */
	if(x0 <= 0 && 0 <= x1)
		for(int h = 0, w = floor(-x0/stepx); h < height; ++ h)
			if(result[h][w] == ' ') result[h][w] = '|';

	/* DRAW X AXIS */
	if(mins <= 0 && 0 <= maks)
		for(int w = 0, h = floor(maks/stepy); w < width; ++ w)
			if(result[h][w] == ' ') result[h][w] = '-';

	for(int h = 0; h < height; ++ h)
	{
		for(int w = 0; w < width; ++ w)
			putchar(result[h][w]);

		puts("");
	}
	puts("Derivative");

	/* DRAW DERIVATIVE */
	stepy = (maksd - minsd) / height;
	memset(result, ' ', sizeof(result));
	for(int w = 0; w < width; ++ w)
		result[(int)floor((maksd - (f(x0 + stepx*w + eps) - f(x0 + stepx*w))/eps) / stepy)][w] = '*';

	/* DRAW Y AXIS */
	if(x0 <= 0 && 0 <= x1)
		for(int h = 0, w = floor(-x0/stepx); h < height; ++ h)
			if(result[h][w] == ' ') result[h][w] = '|';

	/* DRAW X AXIS */
	if(mins <= 0 && 0 <= maks)
		for(int w = 0, h = floor(maksd/stepy); w < width; ++ w)
			if(result[h][w] == ' ') result[h][w] = '-';

	for(int h = 0; h < height; ++ h)
	{
		for(int w = 0; w < width; ++ w)
			putchar(result[h][w]);

		puts("");
	}
	return;
}

double sin2(double x)
{
	return sin(x*x);
}
