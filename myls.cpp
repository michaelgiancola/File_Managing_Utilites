/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the myls utility which outputs the contents of a directory. This utlilty also has
 *the capability of using the -l extention to show even more information about files.
 **/

#include <iostream>
#include "FileManager.h"
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 3)
	{
		cout << "Invalid number of arguments" << endl;
		return 0;
	}
	
	if (argc == 1) //case one is just the ls command
	{
		FileManager obj(get_current_dir_name());
		
		if (obj.getUserName() == "Destroy Me")
		{
			cout << obj.getName() << ": No such file or directory" << endl;
			return 0;
		}
		
		obj.expand();
		
		for (int i = 0; i < obj.getChildren().size(); i++)
		{
			cout << obj.getChildren()[i].getName() << endl; //for each file that exists in the directory, a file object is created and thier name is printed
		}
		cout << endl;
		return 0;
	}
	
	else if (argc == 2) //this is either the ls -l command or ls filename
	{
		string command = argv[1];
			
		if (command == "-l")
		{
			FileManager obj(get_current_dir_name());
		
			obj.expand();
			
			for (int i = 0; i < obj.getChildren().size(); i++)
			{
				cout << obj.getChildren()[i].getPermissionsString(obj.getChildren()[i].getPermissions()) << " " << obj.getChildren()[i].getUserName() << " " << obj.getChildren()[i].getGroupName() << " " << obj.getChildren()[i].getSize() << " " << obj.getChildren()[i].getName() << " " << endl;
				cout << obj.getChildren()[i].getModification() << endl;
			}
			
			cout << endl;
			return 0;
		}
		
		FileManager obj(argv[1]);
		
		if (obj.getUserName() == "Destroy Me")
		{
			cout << obj.getName() << ": No such file or directory" << endl;
			return 0;
		}
		
		if (obj.getFileType(obj.getType()) == "directory") //if the object is a directory then we must iterate through its childrena and output the names
		{
			obj.expand();
		
			for (int i = 0; i < obj.getChildren().size(); i++)
			{
				cout << obj.getChildren()[i].getName() << endl;
			}
			cout << endl;
			return 0;
		}
		
		else
		{
			cout << obj.getName() << endl;
			return 0;
		}
	}
	
	else //this is for the ls -l filename case 
	{
		FileManager obj(argv[2]);
		
		if (obj.getUserName() == "Destroy Me")
		{
			cout << obj.getName() << ": No such file or directory" << endl;
			return 0;
		}
		
		if (obj.getFileType(obj.getType()) == "directory")
		{
			obj.expand();
		
			for (int i = 0; i < obj.getChildren().size(); i++)
			{
				cout << obj.getChildren()[i].getPermissionsString(obj.getChildren()[i].getPermissions()) << " " << obj.getChildren()[i].getUserName() << " " << obj.getChildren()[i].getGroupName() << " " << obj.getChildren()[i].getSize() << " " << obj.getChildren()[i].getName() << endl;
				cout << obj.getChildren()[i].getModification() << endl;
			}
			return 0;
		}
		
		else
		{
			cout << obj.getPermissionsString(obj.getPermissions()) << " " << obj.getUserName() << " " << obj.getGroupName() << " " << obj.getSize() << " " << obj.getName() << endl;
			cout << obj.getModification() << endl;
			return 0;
		}
	}
}
