/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the mymv utlity which moves a file from one locaton to another. 
 *This utlilty also supports across system platform moves as well.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments!" << endl;
		return 0;
	}
	
	FileManager obj1(argv[1]);
	
	if (obj1.getUserName() == "Destroy Me")
	{
		cout << obj1.getName() << ": No such file or directory" << endl;
		return 0;
	}
	
	int check = obj1.rename_(argv[2]); //uses rename to move file locally
	
	if (check != 0) //this is for if the file transfer is over two different systems (if an error occurs in the rename_ we know)
	{
		ofstream file{argv[2]};
		
		if (file.bad())
		{
			return EIO;
		}
	
		obj1.dump(file);
		
		obj1.remove();
		
		file.close();
		
		if (file.bad())
		{
			return EIO;
		}
	}
}