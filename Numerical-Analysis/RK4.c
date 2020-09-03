
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>


std::vector<long double> linspace(long double start, long double end, long double step)
{
    
    long double step_size = abs(end-start)/step;
    std::vector<long double> space;
    for (long double i=start; i<end+step_size; i+=step_size)
    {
        //std::cout << i <<std::endl;
        space.insert(space.end(), i);
    }
    return space;
}

long double f(long double t,long double y)
{
    return y-(t*t) + 1;
}

std::vector<long double> RK4(long double (*f)(long double, long double), std::vector<long double> space, long double step_size, long double w)
{   
    long double y = w;
    //std::vector<long double> space = linspace(a, b, steps);
    long double h = step_size;
    long double k_1, k_2, k_3, k_4;

    std::vector<long double> solution;

    for (auto &t : space)   
    {
        solution.insert(solution.end(), y);
        // slope
        k_1 = f(t, y);
        // slope at midpoint
        k_2 = f(t + h/2, y + h*k_1/2);
        // slope at the midpoint of last section
        k_3 = f(t + h/2, y + h*k_2/2);
        // end point slope
        k_4 = f(t + h, y + h*k_3);
        
        y = y + h/6 * (k_1 + 2*k_2 + 2*k_3 + k_4);
        //std::cout << t <<"," << y<<std::endl;
    }
    
    return solution;
}

int main(int argc, char* argv[])
{
	//using namespace std;
    if (argc == 5)
    {
        long double a = std::stold(argv[1]);
        long double b = std::stold(argv[2]);
        long double n = std::stold(argv[3]);
        long double w = std::stold(argv[4]);

        std::vector<long double> space = linspace(a, b, n);
        long double step_size = abs(b-a)/b;
        std::vector<long double> solution = RK4(&f, space, step_size, w);

        //for (auto &w : solution)
        for (int i=0; i < solution.size(); i++)
        {   
            std::cout << std::setw(5) << space[i] << std::setw(15)  << solution[i] << std::endl;
        }
    }
    else
    {
        std::cout << "rk4 <start> <end> <steps> <initial_value>" <<std::endl;
    }
    
	return 0;
}


