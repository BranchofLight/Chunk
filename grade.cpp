#include <iostream>
#include "chunk.h"

int main()
{
	Chunk grade;
	
	std::cout << "What was your grade?";

	do
	{
		std::cout << "\n> ";
		getchunk(std::cin, grade);

		if (!grade.isFloat())
			std::cout << "Please enter a valid grade between 0-100.";
		else
		{
			if (grade.toFloat() < 0 || grade.toFloat() > 100)
				std::cout << "Please enter a valid grade between 0-100.";
		}	
	} while (!grade.isFloat() || grade.toFloat() < 0 || grade.toFloat() > 100);

	float gradeCheck = grade.toFloat();
           
    if (gradeCheck >= 90 && gradeCheck <= 100)
		std::cout << "Congratulations! You got an A!";
    else if (gradeCheck >= 80 && gradeCheck < 90)
		std::cout << "Congratulations! You got a B!";
    else if (gradeCheck >= 70 && gradeCheck < 80)
		std::cout << "You got a C!";
    else if (gradeCheck >= 60 && gradeCheck < 70)
		std::cout << "You got a D!";
    else if (gradeCheck >= 0 && gradeCheck < 60)
		std::cout << "Sorry! You got an F!";
	
	return 0;
}
	