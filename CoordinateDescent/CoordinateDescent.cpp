// CoordinateDescent.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>

typedef double (*func_ptr)(double*);

const int var_count = 2;

double function(double* variables);
double golden_section(func_ptr f, double* vars, int var_index, double eps, double a, double b, int max_steps_count);
void descent_method(func_ptr f, double* vars, double eps, int max_steps_count);

int menu();
int submenu();
void input_data(double* eps, int* max_steps, double* vars);
void about();

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    double eps = 0.0;
    int max_steps_count = 0;
    double variables[var_count] = { 0.0 };

    while (int choice = menu())
    {
        switch (choice) {
        case 1:
            input_data(&eps, &max_steps_count, variables);
            while (int subchoice = submenu())
            {
                switch (subchoice) {
                case 1:
                    input_data(&eps, &max_steps_count, variables);
                    break;
                case 2:
                    descent_method(function, variables, eps, max_steps_count);
                    break;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                    break;
                }
            }
            break;
        case 2:
            about();
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
    }

    return 0;
}


double function(double* variables)
{

    return pow(25 - variables[0], 2) + pow((variables[1] - 50), 3);
        /*sin(variables[0] * variables[1]) - cos(variables[1] - variables[0]);*/
}


double golden_section(func_ptr f, double* vars, int var_index, double eps, double a, double b, int max_steps_count)
{
    double res = 0.0;
    double phi = (1 + sqrt(5.0)) / 2.0;
    double A = 0.0f, B = 0.0f;
    double x1 = a + phi * (b - a), x2 = b - phi * (b - a);

    int step = 0;

    while ((b - a > eps))
    {
        x1 = b - ((b - a) / phi);
        vars[var_index] = x1;
        A = f(vars);
        x2 = a + ((b - a) / phi);
        vars[var_index] = x2;
        B = f(vars);
        if (A > B)
            a = x1;
        else
            b = x2;

        step++;
        if (step > max_steps_count)
            break;
    }

    res = (a + b) / 2;
    return res;
}

void descent_method(func_ptr f, double* vars, double eps, int max_steps_count)
{
    double B = f(vars), A = 0;
    bool was_counted = false;
    int stpes_ellapsed = 0;
    double delta = 0.0;
    for (int i = 0; i < max_steps_count; i++) {
        A = B;

        for (int var_index = 0; var_index < var_count; var_index++)
            vars[var_index] = golden_section(f, vars, var_index, eps, -5000, 5000, max_steps_count);

        B = f(vars);

        delta = fabs(A - B);

        if (delta <= eps)
        {
            stpes_ellapsed = i + 1;
            was_counted = true;
            break;
        }
    }

    std::cout << "Результат поиска минимума функции " << "0.5-x1^2 + x2-0.5^2)" << std::endl;

    if (!was_counted)
        std::cout << "За максимально указанное количество шагов ( " << max_steps_count << " ) минимум не был посчитан." << std::endl;
    else {
        std::cout << "Количество итераций: " << stpes_ellapsed << std::endl;
        std::cout << "Погрешность: " << delta << std::endl;
    }

    std::cout << "Точка: X(";
    for (int i = 0; i < var_count; i++) {
        std::cout << vars[i] << ", ";

    }

    std::cout << "\b\b" << ")" << std::endl;
    std::cout << "Значение фукнции f(X): " << std::setprecision(10) << f(vars) << std::endl;
}

int menu()
{
    int choice = 0;

    std::cout << "*************************" << std::endl;
    std::cout << "1) Ввод данных..." << std::endl;
    std::cout << "2) О программе" << std::endl;
    std::cout << "0) Выход" << std::endl;
    std::cout << ": ";
    std::cin >> choice;
    std::cout << std::endl;

    return choice;
}

int submenu()
{
    int choice = 0;

    std::cout << "*************************" << std::endl;
    std::cout << "1) Ввод данных..." << std::endl;
    std::cout << "2) Найти минимум функции" << std::endl;
    std::cout << "0) Назад" << std::endl;
    std::cout << ": ";
    std::cin >> choice;
    std::cout << std::endl;

    return choice;
}

void input_data(double* eps, int* max_steps, double* vars)
{
    std::cout << "Введите значение погрешности: ";
    std::cin >> *eps;

    double step = 0;
    std::cout << "Введите величину шага: ";
    std::cin >> step;

    std::cout << "Введите максимальное количество шагов: ";
    std::cin >> *max_steps;
    for (int i = 0; i < var_count; i++) {
        std::cout << "Введите начальное значение " << i + 1 << " координаты: ";
        std::cin >> vars[i];
    }
    std::cout << std::endl;
}

void about()
{
    std::cout << "Программа для поиска минимума функции методом координатного спуска." << std::endl;
}