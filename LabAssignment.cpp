#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;

//Phuong Pham
//CS 311
//Lab 1

const char outfile[] = "test_fail.in";

bool is_double(char * temp);
int is_double_ext(char * temp, int count);

int main()
{
	char temp[100];
	ifstream in_file;
	in_file.open(outfile);
	
	if (in_file)
	{
		in_file.get(temp, 100, '\n');
		in_file.ignore(100, '\n');
		
		cout << "\n\nString is: " << temp << endl;
		cout << "String's length: " << strlen(temp) << endl;
		
		if (is_double(temp))
			cout << "\nSTRING IS A DOUBLE." << endl;
		else
			cout << "\nSRING IS NOT A DOUBLE." << endl;
		
		while (in_file && !in_file.eof())
		{
			in_file.get(temp, 100, '\n');
			in_file.ignore(100, '\n');
		
			cout << "\n\nString is: " << temp << endl;
			cout << "String's length: " << strlen(temp) << endl;
		
		
			if (is_double(temp))
				cout << "\nSTRING IS A DOUBLE." << endl;
			else
				cout << "\nSTRING IS NOT A DOUBLE." << endl;
		}
		
		in_file.close();
	}
	
	return 0;
}



bool is_double(char * temp)
{
	int count = 0;
	int array_place = 0;
	int array [4][4];
	
	//Initialize the "DFA"
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
			array [i][j] = 0;
	}
	array[0][0] = 99;
	
	for (int i = 0; i < strlen(temp); ++i)
	{
		if (is_double_ext(temp, i) == 4)
			return false;
	}

	//If the very first character is an e/E, no good
	if (is_double_ext(temp, count) == 3)
		return false;

	//If first character is a number
	if (is_double_ext(temp, count) == 0)
	{
		//While string is just number, loop on q1
		while (count != strlen(temp) && is_double_ext(temp, count) == 0)
			++count;
						
		array[0][0] = 0;
		array[0][1] = 99; //At q1
		
		//Something comes after the number
		if (count != strlen(temp))
		{
			//If it's a period
			if (is_double_ext(temp, count) == 2)
			{
				array[0][1] = 0;
				array[0][4] = 99; //At q4
				++count;

				//Loop on q4
				while (count != strlen(temp) && is_double_ext(temp, count) == 0)
					++count;
				
				//Still something after q4
				if (count != strlen(temp))
				{
					//Need to be an e or E
					if (is_double_ext(temp, count) == 3)
					{
						array[0][4] = 0;
						array[1][1] = 99; //Now at q6
					}
					
					//Else fails
					else
						return false;
					
					//After the e/E, need to be a number or +/-
					++count; //Advance to character after e/E
					
					//If a +/- after the e/E
					if (is_double_ext(temp, count) == 1)
					{
						array[1][1] = 0;
						array[1][3] = 99; //Now at q8
						++count; //Advance character
					}
					
					//If a number
					if (is_double_ext(temp, count) == 0)
					{
						array[1][1] = 0;
						array[1][2] = 99; //If a number, at q7
						
						//Loop on q7
						while (count != strlen(temp) && is_double_ext(temp, count) == 0)
							++count;
					}
					
					//Anything beside a number after q7 is not a double
					if (count != strlen(temp))
						return false;
				}
			}
			
			//If it's an e or E, we're at q6
			else if (is_double_ext(temp, count) == 3)
			{
				array[0][1] = 0;
				array[1][1] = 99; //Now at q6
				
				++count; //Advance character
				
				//If a +/- after the e/E
				if (is_double_ext(temp, count) == 1)
				{
					array[1][1] = 0;
					array[1][3] = 99; //Now at q8
					++count; //Advance character
				}
					
				//If a number
				if (is_double_ext(temp, count) == 0)
				{
					array[1][1] = 0;
					array[1][2] = 99; //If a number, at q7
						
					//Loop on q7
					while (count != strlen(temp) && is_double_ext(temp, count) == 0)
						++count;
				}
					
				//Anything beside a number after q7 is not a double
				if (count != strlen(temp))
					return false;
			}
			
			//If anything else, no longer a double
			else
				return false;
		}
	}
	
	//If first character is a +/-
	if (is_double_ext(temp, count) == 1)
	{
		array[0][0] = 0;
		array[0][2] = 99; //At q2
		
		//Need to be a period follow a +/-
		if (is_double_ext(temp, count + 1) == 3 || is_double_ext(temp, count + 1) == 4)
			return false;
		
		++count;
	}
	
	//If next character is a period
	if (is_double_ext(temp, count) == 2)
	{
		if (count != 0)
			array[0][2] = 0;
		else
			array[0][0] = 0;
			array[0][3] = 99; //At q3
		
		//Need to be a number after period
		if (is_double_ext(temp, count + 1) != 0)
			return false;
		
		++count;
	}
	
	//If more
	if (count != strlen(temp))
	{
		while (count != strlen(temp) && is_double_ext(temp, count) == 0)
		{
			++count;
		
			array[0][3] = 0;
			array[1][0] = 99; //At q5
		}
		
		if (count != strlen(temp))
		{
			//If next character is a period
			if (is_double_ext(temp, count) == 2)
			{
				array[1][0] == 0;
				array[0][4] == 99; //At q4
				
				//Loop on q4
				while (count != strlen(temp) && is_double_ext(temp, count) == 0)
					++count;
				
				//Still something after q4
				if (count != strlen(temp))
				{
					++count; //Move to next character
					
					//Need to be an e or E
					if (is_double_ext(temp, count) == 3)
					{
						array[0][4] = 0;
						array[1][1] = 99; //Now at q6
					}
					
					//After the e/E, need to be a number or +/-
					++count; //Advance to character after e/E
					
					//If a +/- after the e/E
					if (is_double_ext(temp, count) == 1)
					{
						array[1][1] = 0;
						array[1][3] = 99; //Now at q8
					}
					
					++count; //Advance character
					
					//If a number
					if (is_double_ext(temp, count) == 0)
					{
						array[1][1] = 0;
						array[1][3] = 0;
						array[1][2] = 99; //If a number, at q7
						
						//Loop on q7
						while (count != strlen(temp) && is_double_ext(temp, count) == 0)
							++count;

					}
					
					//Anything beside a number after q7 is not a double
					if (count != strlen(temp))
						return false;
					
					if (array[0][1] == 99 || array[0][4] == 99 || array[1][0] == 99 || array[1][2] == 99)
						return true;
					return false;
				}
			}
	
			//If next character is e/E
			if (is_double_ext(temp, count) == 3)
			{
				array[1][0] = 0;
				array[1][1] = 99; //At q6
				
				++count;
				
				//If a +/- after the e/E
				if (is_double_ext(temp, count) == 1)
				{
					array[1][1] = 0;
					array[1][3] = 99; //Now at q8
					++count; //Advance character
				}
					
				//If a number
				if (is_double_ext(temp, count) == 0)
				{
					array[1][1] = 0;
					array[1][2] = 99; //If a number, at q7
						
					//Loop on q7
					while (count != strlen(temp) && is_double_ext(temp, count) == 0)
						++count;
				}
					
				//Anything beside a number after q7 is not a double
				if (count != strlen(temp))
					return false;
				
				if (array[0][1] == 99 || array[0][4] == 99 || array[1][0] == 99 || array[1][2] == 99)
					return true;
				return false;
			}
			
			//Anything else is not a double
			else
				return false;
		}
		
	}
	
	if (array[0][1] == 99 || array[0][4] == 99 || array[1][0] == 99 || array[1][2] == 99)
		return true;
	return false;
}



int is_double_ext(char * temp, int count)
{
	if (temp[count] == '0' || temp[count] == '1' || temp[count] == '2' || temp[count] == '3' || temp[count] == '4' || temp[count] == '5'
		|| temp[count] == '6' || temp[count] == '7' || temp[count] == '8' || temp[count] == '9')
		return 0;
	if (temp[count] == '+' || temp[count] == '-')
		return 1;
	if (temp[count] == '.')
		return 2;
	if (temp[count] == 'e' || temp[count] == 'E')
		return 3;
	else
		return 4;
}








