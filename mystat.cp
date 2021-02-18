/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the mystat ultility and allows for information about the file to be outputed.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 2) //argument input check to see if the number of arguments including the program name
	{
		cout << "You have entered an incorrect amount of arguments" << endl;
		return 0;
	}
	
	FileManager obj(argv[1]);
	
	if (obj.getUserName() == "Destroy Me") //unidentified file check
	{
		cout << obj.getName() << ": No such file or directory" << endl;
		return 0;
	}
	
	cout << "File: " << obj.getName() << endl;
	cout << "Size: " << obj.getSize() << endl;
	cout << "File Type: " << obj.getFileType(obj.getType()) << endl;
	cout << "Permission Access: " << obj.getPermissionsString(obj.getPermissions()) << endl;
	cout << "Uid: " << obj.getUserID() << endl;
	cout << "User Name: " << obj.getUserName() << endl;
	cout << "Gid: " << obj.getGroupID() << endl; 
	cout << "Group Name: " << obj.getGroupName() << endl;
	cout << "Block Size: " << obj.getBlockSize() << endl;
	cout << "Access Time: " << obj.getAccessTime() << endl;
	cout << "Modify: " << obj.getModification() << endl;
	cout << "Change: " << obj.getStatusChange() << endl;
	cout << "Error Number: " << obj.getErrorNum() << endl;
}