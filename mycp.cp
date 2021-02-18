/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the mycp ultility and allows for the user to copy files into other locations within the file system.
 *It does so by creating a file in the current directory with the new name and using the dump function to dump the contents of the
 *original file into the new one.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "You have entered an incorrect amount of arguments" << endl;
		return 0;
	}
	
	FileManager obj1(argv[1]);
	
	if (obj1.getUserName() == "Destroy Me")
	{
		cout << obj1.getName() << ": No such file or directory" << endl;
		return 0;
	}
	
	if (obj1.getFileType(obj1.getType()) == "directory") //check to see if the original file is a directory or not
	{
		cout << "This utility does not work on directories!" << endl;
		return 0;
	}
		
	string new_name = argv[2];
	
	ofstream file{new_name}; //creates a file in the current working directory with the name new_name
	
	if (file.bad()) //error checks
	{
		return EIO;
	}
	
	obj1.dump(file);
	
	file.close();
	
	if (file.bad()) 
	{
		return EIO;
	}
	
	return 0;
}