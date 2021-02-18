/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the mycat ultility and allows for information about the file to be outputted.
 *The function prints the contents of each regular file by calling the dump function explained in FileManager.cpp.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "You have entered an incorrect amount of arguments." << endl;
		return 0;
	}
	
	int i = 1; 
	
	while (i < argc) //loop through the amount of arguments
	{
		FileManager obj(argv[i]);
		
		if (obj.getUserName() == "Destroy Me") //error checking to see if the file exists in the system or not
		{
			cout << obj .getName() << ": No such file or directory" << endl; 
			i++;
			continue;
		}
		
		obj.dump(cout); //for each FileManager object, the contents are dumped to the cout stream for the user to view
		
		cout << endl;
		
		i++;
	}
	
	cout << endl;
}