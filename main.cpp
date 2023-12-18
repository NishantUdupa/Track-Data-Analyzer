/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.text
content: The text file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    // TODO: create arrays needed
    double time[SIZE];
    string country[SIZE];
    unsigned int number[SIZE];
    string lastname[SIZE];
    unsigned int rank[SIZE];
    // TOTO: prep all arrays
    prep_double_array(time);
    prep_unsigned_int_array(rank);
    prep_unsigned_int_array(number);
    prep_string_array(country);
    prep_string_array(lastname);
    string filein = "";
    while (true) {
        try {
            cout << "Enter file name: ";
            cin >> filein;
            get_runner_data(filein, time, country, number, lastname);
            break;
        } 
        catch(invalid_argument &e) {
            cout<< "Invalid File: " << e.what() << endl;
        }
        catch(domain_error &e) {
            cout << "Invalid File: " << e.what() << endl;
        
        }
        
    }

    get_ranking(time, rank);
    print_results(time, country, lastname, rank);

    return 0;
}

