// Dustin Gordon


#include <iostream>
#include <chrono>

using namespace std;

// Algorithm A:
double pow(double base, int exp)
{
    switch(exp)
    {
        case 0: // A^0 = 1
        {
            return 1;
        }
        case 1: // A^1 = A
        {
            return base;
        }
        default:
            //Positive exponents:
            if(exp > 0)
            {
                // [A^B] = [A * A^(B-1)]
                return base * pow(base, (exp - 1));
            }
            //Negative exponents:
            else if(exp < 0)
            {
                // [A^(-B)] = [1 / (A^|B|)]
                double absExp = exp * -1;
                return 1 / (base * pow(base, (absExp - 1)));
            }
            else
            {
                return 0; //To satisfy compiler expecting a return;
            }
    }
}

// Algorithm B:
double improvedPow(double base, int exp)
{
    //Even exponents:
    if(exp % 2 == 0)
    {
        // [A^10] = [A^5 * A^5]
        double temp = pow(base, (exp / 2));
        return temp * temp;
    }
    //Odd exponents:
    else
    {
        // [A^13] = [A * A^6 * A^6]
        double temp = pow(base, (exp / 2));
        return base * temp * temp;
    }
}


int main()
{
    double x;	//The Base
    int y;		//The Exponent

    cout << "\n* To calculate x^y ..." << endl;
    cout << "\n* Enter the base (x): ";
    cin >> x;   //User input
    cout << "* Enter exponent (y): ";
    cin >> y;   //User input

    if(x == 0)  //Input validation
    {
        if (y > 0)
            cout << "\n* Result: 0^" << y << " = 0" << endl;
        else
            cout << "\nERROR: 0^0 is not defined!" << endl;
    }
    else
    {
        cout << "\n* Result: " << x << "^" << y << " = "
             << improvedPow(x,y) << endl; //Call improved recursive function
    }

    cout << "\n*\t\tRun-time Comparison: " << endl;

    // Benchmark Algorithm A:
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    pow(x,y);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto durationA = chrono::duration_cast<chrono::nanoseconds>( t2 - t1 ).count();
    cout << "* Algr. A)         pow(x,y) =\t" << durationA << " ns;" << endl;

    // Benchmark Algorithm B:
    t1 = chrono::high_resolution_clock::now();
    improvedPow(x,y);
    t2 = chrono::high_resolution_clock::now();
    auto durationB = chrono::duration_cast<chrono::nanoseconds>( t2 - t1 ).count();
    cout << "* Algr. B) improvedPow(x,y) =\t" << durationB << " ns;" << endl;
    cout << "\n* The improved function was faster by " << durationA - durationB << " ns. \n" << endl;

    return 0;
}

