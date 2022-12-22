#pragma once
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>
class Descent_MethClass
{
	typedef double (*func_ptr)(double*);
	const int var_count = 2;
	const double eps = 0.0;
	int max_steps_count;
	double* variables;
	Descent_MethClass() {}
	double golden_section(func_ptr f, double* vars, int var_index, double eps, double a, double b, int max_steps_count);
	void descent_method(func_ptr f, double* vars, double eps, int max_steps_count);

};

