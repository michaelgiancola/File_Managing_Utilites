/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the myrm utility and removes the specified file or files that the user wants
 *deleted from the system.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "You have entered an incorrect amount of arguments" << endl;
		return 0;
	}
	
	int i = 1; 
	
	while (i < argc)
	{
		FileManager obj(argv[i]);
		obj.remove(); 					//remove function unlinks the file from the system
		
		if (obj.getUserName() == "Destroy Me")
		{
			cout << obj.getName() << ": No such file or directory" << endl;
			i++;
			continue;
		}
		
		i++;
	}
	
	if (argc == 2) 						//if one file is being removed
	{
		cout << "The requested file have been removed." << endl;
		return 0;
	}
	
	else 							//if multiple files are being removed
	{
		cout << "The requested files have been removed." << endl;
	}
}
