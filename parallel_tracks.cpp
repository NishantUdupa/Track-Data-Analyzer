#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <fstream>
#include <sstream>
using std::string;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  //TODO
  std::ifstream myfile(file);

  if (!myfile.is_open()) {
	  throw std::invalid_argument("Cannot open file");
  }
	string line = "";
	for(int i = 0; i < int(SIZE); i++) {
		std::stringstream categ;
		std::getline(myfile, line);
		categ << line;
		if(line == "") {
			throw std::domain_error("File missing data");
		}
		//TODO: if line is empty

		double time = 0.0;
		categ >> time;
		if(categ.fail() && !categ.eof()) {
			throw std::domain_error("File contains invalid data (time)");
		}
		if((time) <= 0) {
			throw std::domain_error("File contains invalid data (time)");
		}
		timeArray[i] = (time);

		string country = "";
		categ >> country;

		for (int i = 0; i < int(country.length()); i++) {
			if ((isupper(country[i]) == false) || (isalpha(country[i]) == false)) {
				throw std::domain_error("File contains invalid data (country)");
			}
		}
		if(country.length() != 3) {
			throw std::domain_error("File contains invalid data (country)");

		}
		countryArray[i] = country;
		
		unsigned int number = 0;
		if(!(categ >> number)) {
			throw std::domain_error("File contains invalid data (number)");
		}
		if(number > 100) {
			throw std::domain_error("File contains invalid data (number)");
		}

		numberArray[i] = number;

		string lastname = "";
		categ >> lastname;
		lastname = trim(lastname);

		if(lastname.length() <= 1) {
			throw std::domain_error("File contains invalid data (lastname)");
		}
		for(int i = 0; i < int(lastname.length()); i++) {
			if ((isalpha(lastname[i]) == false) && (isspace(lastname[i]) == false)) {
				throw std::domain_error("File contains invalid data (lastname)");
			}
		}

		lastnameArray[i] = lastname;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	//TODO
	for(unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0.0;
	}

}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	for(unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	for(unsigned int i = 0; i < SIZE; i++) {
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	for (int i = 0; i < int(SIZE); i++) {
		int count = 0;
		for (int j = 0; j < int(SIZE); j++) {
			if (timeArray[j] < timeArray [i])
			count++;
		}
		rankArray[i] = count + 1;
	}
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double besttime = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				besttime = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - besttime) << std::endl; 
			}
			
		}
	}	
}
std::string trim(std::string area) {
	// remove whitespace from the beginning
	while (!area.empty() && isspace(area.at(0))) {
			area.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!area.empty() && isspace(area.at(area.size()-1))) {
		area.erase(area.size()-1, 1);
	}
	
	return area;
}