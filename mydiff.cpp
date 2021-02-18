/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the mydiff ultility which will compare two regular files to see
 *if there contents in are the same or not.
 **/

#include <iostream>
#include "FileManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) 									//number of arguments check
	{
		cout << "You have entered an incorrect amount of arguments" << endl;
		return 0;
	}
	
	FileManager obj1(argv[1]);
	if (obj1.getUserName() == "Destroy Me") 					//unidentifed file check
	{
		cout << obj1.getName() << ": No such file or directory" << endl;
		return 0;
	}
	
	FileManager obj2(argv[2]);
	if (obj2.getUserName() == "Destroy Me")
	{
		cout << obj2.getName() << ": No such file or directory" << endl;
		return 0;
	}
	
	cout << "The files are " << obj1.compare(obj2) << endl; 			//calls compare to see if the contents are the same or not
}
