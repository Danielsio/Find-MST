#include "Utillities.h"

void main(int argc, char** argv)
{
	try
	{
		runTasks(argv[1]); // run the program
	}
	catch (string outRes)
	{
		ofstream outputFile(argv[2]);
		if (outputFile)
		{
			outputFile << outRes;
		}
		cout << outRes;
		outputFile.close();
		
		exit(1);
	}
	catch (...)
	{
		ofstream outputFile(argv[2]);
		if (outputFile)
		{
			outputFile << "Unknown Error";
		}
		cout << "Unknown Error";
		outputFile.close();
		
		exit(1);
	}

}