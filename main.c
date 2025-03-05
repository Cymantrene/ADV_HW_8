#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double f1(double x)
{
    return 0.6 * x + 3;
}

double f2(double x)
{
    return pow(x - 2, 3) - 1;
}

double f3(double x)
{
    return 3 / x;
}

double df1(double x)
{
    return 0.6;
}

double df2(double x)
{
    return 3 * pow(x - 2, 2);
}

double df3(double x)
{
    return -3 / (x * x);
}


double root(double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*df)(double), double (*dg)(double), int *iterations)
{
    double x = (a + b) / 2;
    *iterations = 0;


    if (fabs(f(x) - g(x)) <= eps1)
    {
        (*iterations)++;
        return x;
    }

    while (fabs(f(x) - g(x)) > eps1)
    {
        if (fabs(df(x) - dg(x)) < 1e-10)
        {
            printf("ERROR!!!\n");
            return 0;
        }
        else
        {
            x = x - (f(x) - g(x)) / (df(x) - dg(x));
            (*iterations)++;
        }
    }
    return x;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
    int n = 1;
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2;
    double prevSum = 0;
    while (fabs(sum - prevSum) > eps2)
    {
        n *= 2;
        h = (b - a) / n;
        prevSum = sum;
        sum = 0;
        for (int i = 1; i < n; i++)
        {
            sum += f(a + i * h);
        }
        sum = (f(a) + f(b) + 2 * sum) * h / 2;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    double eps1 = 1e-6;
    double eps2 = 1e-6;
    double x1, x2, x3, x4, x5;
    int showRoots = 0;
    int showIterations = 0;
    int showArea = 0;
    int showTest = 0;


    int iterations1 = 0;
    int iterations2 = 0;
    int iterations3 = 0;


    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-help") == 0)
        {
            printf("True Keys:\n");
            printf("-help\n");
            printf("-roots\n");
            printf("-iterations\n");
            printf("-area\n");
            printf("-test\n");
            return 0;
        }
        else if (strcmp(argv[i], "-roots") == 0)
        {
            showRoots = 1;
        }
        else if (strcmp(argv[i], "-iterations") == 0)
        {
            showIterations = 1;
        }
        else if (strcmp(argv[i], "-area") == 0)
        {
            showArea = 1;
        }
        else if (strcmp(argv[i], "-test") == 0)
        {
            showTest = 1;
        }
    }



    x1 = root(f1, f2, 0, 5, eps1, df1, df2, &iterations1); // f1(x) = f2(x)
    x2 = root(f1, f3, -6, -4, eps1, df1, df3, &iterations2); // f1(x) = f3(x)
    x3 = root(f1, f3, 0, 2, eps1, df1, df3, &iterations2); // f1(x) = f3(x)
    x4 = root(f2, f3, -2, 0, eps1, df2, df3, &iterations3); // f2(x) = f3(x)
    x5 = root(f2, f3, 2, 4, eps1, df2, df3, &iterations3); // f2(x) = f3(x)


    if (showRoots)
    {
        printf("Точки пересечения кривых:\n");
        printf("f1(x) = f2(x): x1 = %lf\n", x1);
        printf("f1(x) = f3(x): x2 = %lf, x3 = %lf\n", x2, x3);
        printf("f2(x) = f3(x): x4 = %lf, x5 = %lf\n", x4, x5);
    }


    if (showTest)
    {
        printf("Тестирование функции root:\n");

        int iterationsTest1 = 0, iterationsTest2 = 0, iterationsTest3 = 0;
        printf("Корень уравнения f1(x) = f2(x) на отрезке [0, 3]: %lf\n", root(f1, f2, 0, 3, eps1, df1, df2, &iterationsTest1));
        printf("Корень уравнения f1(x) = f3(x) на отрезке [1, 4]: %lf\n", root(f1, f3, 1, 4, eps1, df1, df3, &iterationsTest2));
        printf("Корень уравнения f2(x) = f3(x) на отрезке [1, 4]: %lf\n", root(f2, f3, 1, 4, eps1, df2, df3, &iterationsTest3));
        printf("Тестирование функции integral:\n");
        printf("Интеграл от f1(x) на отрезке [0, 3]: %lf\n", integral(f1, 0, 3, eps2));
        printf("Интеграл от f2(x) на отрезке [0, 3]: %lf\n", integral(f2, 0, 3, eps2));
        printf("Интеграл от f3(x) на отрезке [1, 4]: %lf\n", integral(f3, 1, 4, eps2));
        printf("Число итераций для поиска корней:\n");
        printf("f1(x) = f2(x): Число итераций: %d\n", iterationsTest1);
        printf("f1(x) = f3(x): Число итераций: %d\n", iterationsTest2);
        printf("f2(x) = f3(x): Число итераций: %d\n", iterationsTest3);
        return 0;
    }


    if (showIterations)
    {
        printf("Число итераций для поиска корней:\n");
        printf("f1(x) = f2(x): Число итераций: %d\n", iterations1);
        printf("f1(x) = f3(x): Число итераций: %d\n", iterations2);
        printf("f2(x) = f3(x): Число итераций: %d\n", iterations3);
    }


    if (showArea)
    {
        printf("Площадь фигуры:\n");

        double intersections[5] = {x2, x3, x1, x4, x5};
        for (int i = 0; i < 5; i++)
        {
            for (int j = i + 1; j < 5; j++)
            {
                if (intersections[i] > intersections[j])
                {
                    double temp = intersections[i];
                    intersections[i] = intersections[j];
                    intersections[j] = temp;
                }
            }
        }
        double area1 = integral(f1, intersections[0], intersections[1], eps2) - integral(f3, intersections[0], intersections[1], eps2);
        double area2 = integral(f1, intersections[1], intersections[2], eps2) - integral(f2, intersections[1], intersections[2], eps2);
        double area3 = integral(f2, intersections[2], intersections[3], eps2) - integral(f3, intersections[2], intersections[3], eps2);
        double area4 = integral(f2, intersections[3], intersections[4], eps2) - integral(f3, intersections[3], intersections[4], eps2);
        double total_area = area1 + area2 + area3 + area4;
        printf("%lf\n", total_area);
    }
    return 0;
}
