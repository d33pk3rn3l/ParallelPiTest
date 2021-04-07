//
//  main.cpp
//  Quickmafs
//
//  Created by Benedikt on 27.03.21.
//

#include <iostream>
#include <iomanip>
#include <chrono>
#import <omp.h>

using namespace std::chrono;
using namespace std;

void pi(int terms){
    unsigned long i;
    long double x;
    x = 1.0;

    auto start = high_resolution_clock::now();
    #pragma omp parallel for reduction(+:x)
    for (i=1; i <= terms; i++) {
      if (i % 2 == 1)
          x = x - (1.0 / ((2.0*i)+1));
      else
          x = x + (1.0 / ((2.0*i)+1));
       }
    x = x * 4.0;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << fixed;
    cout << setprecision(25);
    cout << "The value of pi is: " << x << " and it took " << duration.count() << " microseconds" << " for " << terms << " terms! \n";
}

bool isprime(int n) {
    bool flag = true;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

void primePara(int end) {
    unsigned long long int noPrimes = 0;

    auto start = high_resolution_clock::now();
    #pragma omp parallel for reduction(+:noPrimes)
    for (int i = 2; i <= end; i++) {
        //omp_get_num_threads();
        if (isprime(i)) {
            noPrimes++;
        }

    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "We found: " << noPrimes << " prime numbers and it took " << duration.count() << " milliseconds " << "for all numbers up to " << end << "\n";
}

void primefn(int end) {
    unsigned long long int noPrimes = 0;

    auto start = high_resolution_clock::now();
    //#pragma omp parallel for reduction(+:noPrimes)
    for (int startNumber = 1; startNumber <= end; startNumber++) {
        bool foundPrime = true;
        for (int i = 2; i < startNumber; i++) {
            //cout << "hows it going " << i << "\n";
            if (startNumber % i == 0) {
                foundPrime = false;
            }
        }
        if (foundPrime) {
            noPrimes++;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "We found: " << noPrimes - 1 << " prime numbers and it took " << duration.count() << " milliseconds " << "for all numbers up to " << end << "\n";
}

int main() {
    int mode; //see switch case

    while (true) {
    cout << "0 for pi, 1 for primeParallel, 2 for prime one core (10 for exit)? \n";
    cin >> mode;


        switch (mode) {
            case 0:
                int terms;
                cout << "Enter the number of terms to approximate (using parallelization)\n";
                cin >> terms;
                pi(terms);
                break;
            case 1:
                int end;
                cout << "Enter the number where you want to find all prime number up to (using parallelization): \n";
                cin >> end;
                primePara(end);
                break;
            case 2:
                end = 0;
                cout << "Enter the number where you want to find all prime number up to (using one core): \n";
                cin >> end;
                primefn(end);
                break;
            case 10:
                return 0;

            default:
                cout << "Give me a number :) \n";
                break;
        }
    }
}
