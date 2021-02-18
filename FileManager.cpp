/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the implementation for my FileManager class. It is used to manipulate a file in many ways.
 *Data fom this file is extracted and used to create C++ utlilites that help manage files on a Linux system.
 **/

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <cmath>
#include <stdio.h>  
#include <dirent.h>
#include <string.h>
#include "FileManager.h"

using namespace std;

/*This is a default constructor that is not used but is implemented if neccessary.*/
FileManager::FileManager(){}

/*Function name: FileManager constructor 
 *Parameters: The constructor of FileManager has a char* argument which is where the name of the file 
 *that is to be manipulated is passed through.
 *Description:This constructor will use multiple Linux System functions to extract data and contents from the file
 *that will be used too help create the C++ utilities. The constructor is where all of the member data is initialized.
 *Return: This constructor returns a new instance of the FileManager class so that the object can be used to manipulate
 *the specifed file.
 **/
FileManager::FileManager(char *file_name)
{
	this->file_name = file_name;

	struct stat buf;
	
	this->error_num = 0;
	
	if (stat(file_name, &buf) == -1)
	{
		this->error_num = errno;
		this->user_name = "Destroy Me";
		//do something here to indicate that this object should be destroyed
	}
	
	else
	{
		this->type = buf.st_mode;
		this->size = buf.st_size;
		this->user_id = buf.st_uid;
	
	
		if (getpwuid(this->user_id) == NULL)
		{
			this->error_num = errno;
		}
	
		else
		{
			this->user_name = getpwuid(this->user_id)->pw_name;
		
		
			this->group_id = buf.st_gid;
	
			if (getgrgid(this->group_id) == NULL)
			{
				this->error_num = errno;
			}
			
			else
			{
				this->group_name = getgrgid(this->group_id)->gr_name;
			
			
				this->permissons = buf.st_mode;
				this->access = ctime(&buf.st_atime);
				this->modifcation = ctime(&buf.st_mtime);
				this->status_change = ctime(&buf.st_ctime);
				this->block_size = buf.st_blksize;
				
				this->error_num = 0;
			}
		}
	}
}

/*Function name: FileManager destructor
 *Parameters: No parameters.
 *Description: The destructor is used to deallocate any dynamic memory that is being allocated in this file and cleans up any objects
 *that must be destroyed after going out of scope.
 *Return: No return type.
 **/
FileManager::~FileManager(){}

/*Function name: getName()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the file's name that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class.
 *Return: This function returns a char* which is the name of the file.
 **/
char* FileManager::getName()
{
	//cout << "the test final: " << this->file_name << endl;
	return this->file_name;
}

/*Function name: getType()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the file's type that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class. This type member 
 *will eventually be used to retrieve more specific data from the file.
 *Return: This getter returns a mode_t type which many of the system Linux functions require as arguments.
 **/
mode_t FileManager::getType()
{
	return this->type;
}

/*Function name: getSize()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the file's size in bytes that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class. This size member 
 *tells us what the size of the file we are working with is in bytes and will be important to us in the program so that 
 *we can later read and write to other files.
 *Return: This getter returns a mode_t type and stores the number of bytes in the file.
 **/
mode_t FileManager::getSize()
{
	return this->size;
}

/*Function name: getUserID()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the User ID of the file that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class. This User ID member 
 *helps us retreive the name of the owner of the file.
 *Return: This getter returns a uid_t type and contains the user id number.
 **/
uid_t FileManager::getUserID()
{
	return this->user_id;
}

/*Function name: getUserName()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the User Name or Owner name of the file that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class. This user name member 
 *will be used in some of the utlilites created to provide extra information to the user about the file.
 *Return: This getter returns a string type of the name of the owner.
 **/
string FileManager::getUserName()
{
	return this->user_name;
}

/*Function name: getGroupID()
 *Parameters: No parameters.
 *Description: This function is a getter function that retreives the Group ID of the file that was initlized and stored
 *in a private attribute. This getter allows you to retrieve the private member outside of the class. This group ID member 
 *helps us retreive the name of the group of the file.
 *Return: This getter returns a gid_t type and contains the user id number.
 **/
gid_t FileManager::getGroupID()
{
	return this->group_id;
}

/*Function name: getGroupName()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the Group Name of the file that was initlized and stored
*in a private attribute.This getter allows you to retrieve the private member outside of the class. This group name member 
*will be used in some of the utlilites created to provide extra information to the user about the file.
*Return : This getter returns a string type of the name of the group name.
**/
string FileManager::getGroupName()
{
	return this->group_name;
}

/*Function name: getPermissions()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the permissions of the file that was initlized and stored
*in a private attribute. This getter allows you to retrieve the private member outside of the class. This permissions attribute
*will be used to get an easily readable string version so that a user can easily see what actions can be performed on the file
*and by who.
*Return : This getter returns a mode_t type of the file permissions.
**/
mode_t FileManager::getPermissions()
{
	return this->permissons;
}

/*Function name: getAccessTime()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the time that the file was last accessed. This
*is used to display to a user to provide extra information about the file.
*Return : This getter returns a string type of the file access time.
**/
string FileManager::getAccessTime()
{
	return this->access;
}

/*Function name: getModification()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the time that the file was last modified. This
*is used to display to a user to provide extra information about the file.
*Return : This getter returns a string type of the file modification time.
**/
string FileManager::getModification()
{
	return this->modifcation;
}

/*Function name: getStatusChange()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the time that the file's status was changed. This
*is used to display to a user to provide extra information about the file.
*Return : This getter returns a string type of the file status change time.
**/
string FileManager::getStatusChange()
{
	return this->status_change;
}

/*Function name: getBlockSize()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the block size of the file. This
*attribute is used for reading and writing files in blocks to make the program more efficient.
*Return : This getter returns a blksize_t type that is the Block size of the file in bytes.
**/
blksize_t FileManager::getBlockSize()
{
	return this->block_size;
}

/*Function name: getChildren()
*Parameters : No parameters.
*Description : This function is a getter function that gives a vector of a 
*directory file in the system. This attribute is used quite abit in the program
*so that we can get access to the information about the child files in a file.
*Return : This getter returns a vector of FileManager objects.
**/
vector<FileManager> FileManager::getChildren()
{
	return this->children;
}

/*Function name: getErrorNum()
*Parameters : No parameters.
*Description : This function is a getter function that retreives the error number
*associated with the FileManager object. This error number will help to see where
*something went wrong during an operation.
*Return : This getter returns an integer type which is the error number.
**/
int FileManager::getErrorNum()
{
	return this->error_num;
}

/*Function name: getErrorNumStr()
*Parameters : No parameters.
*Description : This function is a getter function that retrieves
*the same error number as above however this time in a string.
*Return : This getter returns a string of the error number.
**/
string FileManager::getErrorNumStr()
{
	string error = strerror(this->error_num);
	return error;
}

/*Function name: setName
*Parameters : This function is a setter function that takes one char* parameter that
*the function uses to rename a file. 
*Description : This function takes the new name of the file as a an argument and calls another
*function called rename which actually renames the file in the system.
*Return : No return type
**/
void FileManager::setName(char *name)
{
	rename_(name);
}

/*Function name: getPermissionsString
*Parameters : This function takes one mode_t parameter that
*the function uses to understand which permissions are for which user. 
*Description : This function provides the permissions in an 
*easily readable fashion for a user to read. The function uses bitwise 
*operations to understand what permissions are set for the file.
*The permissions include for the Owner, Group, and Others.
*Return : This function returns a string.
**/
string FileManager::getPermissionsString(mode_t permission)
{
	string file_permissions;
	
	if (permission & S_IRUSR)
		file_permissions += 'r';
	
	else
		file_permissions += '-';

	
	if (permission & S_IWUSR)
		file_permissions += 'w';
	
	else
		file_permissions += '-';
	
	if (permission & S_IXUSR)
		file_permissions += 'x';
	
	else
		file_permissions += '-';
	
	if (permission & S_IRGRP)
		file_permissions += 'r';
	
	else
		file_permissions += '-';
	
	if (permission & S_IWGRP)
		file_permissions += 'w';
	
	else
		file_permissions += '-';
	
	if (permission & S_IXGRP)
		file_permissions += 'x';
	
	else
		file_permissions += '-';
	
	if (permission & S_IROTH)
		file_permissions += 'r';
	
	else
		file_permissions += '-';
	
	if (permission & S_IWOTH)
		file_permissions += 'w';
	
	else
		file_permissions += '-';
	
	if (permission & S_IXOTH)
		file_permissions += 'x';
	
	else
		file_permissions += '-';
	
	return file_permissions;
}

/*Function name: getFileType
*Parameters : This function takes in a mode_t parameter which represents the type.
*This type was retreived in the constructor and is used in coordination with some 
*sys functions to establish what type of file we are working with.
*Description : This function is used alot in the program when checking to see what 
*type of file it is since certain utilites have different operations depending on what
*type of file it is.
*Return : This function returns a string clearly indicating what type of file it is.
**/
string FileManager::getFileType(mode_t type)
{
	if (S_ISREG(type))
	{
		return "regular file";
	}
	
	else if (S_ISDIR(type))
	{
		return "directory";
	}
	
	else if (S_ISCHR(type))
	{
		return "character device";
	}
	
	else if (S_ISBLK(type))
	{
		return "block device";
	}
	
	else if (S_ISFIFO(type))
	{
		return "FIFO";
	}
	
	else if (S_ISLNK(type))
	{
		return "Symbolic Link";
	}
	
	else if (S_ISSOCK(type))
	{
		return "Socket";
	}
}

/*Function name: dump
*Parameters : This function takes in an output stream as a parameter which will either be
*a ofstream or cout in our program.
*Description : This function is used to dump the contents of one file into another. The function uses
*dynamically allocated arrays as buffers to allow for reading and writing in specified blocks. It reads
*the objects file contents and writes the contents into the output stream whether it being another file or cout.
*Return : This function returns an integer which is the error number. The function will return 0 if the operation
*is successful or else its corresponding error number if it encounters an issue.
**/
int FileManager::dump(ostream& stream)
{
	if ((stream.bad())){
		this->error_num = EIO;
		return this->error_num;
	}
	
	if (this->getFileType(this->getType()) != "regular file")
	{
		this->error_num = ENOTSUP;
		cout << "Error! This is not a regular file!" << endl;
		return this->error_num;
	}
	
	ifstream file;
	file.open(this->file_name);
	
	if (file.fail())
	{
		cout << "Error Opening File!" << endl;
		return this->error_num = EIO;
	}
	
	char *buffer = new char[this->block_size];
	
	double iterations = ceil(double(this->size) / double(this->block_size)); //dividing the size of the file with the block size and taking the ceiling of it will let us know how many block sizes we are reading and writing
	
	int i = 0;
	
	while (i < iterations)
	{
		file.read(buffer, this->block_size);
		if (file.bad())
		{
			this->error_num = EIO;
		}
		
		if (i == iterations - 1) //on the last iteration we do not want to write everthing that is left in the buffer if we have already written it so we use the modulus operator to get the remainder 
		{
			stream.write(buffer, ((this->size) % (this->block_size))); //this writes the remaining contents to the ostream while leaving out content that has already been written
			i++;
			continue;
		}
		
		stream.write(buffer, (this->block_size));
		
		i++;
	}
	
	file.close();
	
	delete[] buffer; //delete dynamically allocated buffer
	
	this->error_num = 0;
	return this->error_num;
}

/*Function name: rename_
*Parameters : This function takes in a char* which is the desired new name of the file.
*Description : This function physically renames the file by using a system function. The
*sys function rename takes in the existing name and the desired name and renames the file 
*in the system.
*Return : This function returns an integer value which is the error number.
**/
int FileManager::rename_(char* name)
{
	if (rename(this->file_name, name) == -1) //error checking since rename returns -1 if an issue occurs in the operations
	{
		this->error_num = errno;
		return this->error_num;
	}
	
	this->file_name = name;
	
	this->error_num = 0;
	return this->error_num;
}

/*Function name: remove
*Parameters : No parameters
*Description : This function is used to remove a file from the system. First all the 
*retrieved information in the attributes are cleared and then using the sys function
*unlink(), the file is automatically removed from the system. Unlink takes in the file name.
*Return : This function returns an integer value which is the error number.
**/
int FileManager::remove()
{
	this->type = NULL;
	this->size = NULL;
	this->user_id = NULL;
	this->user_name.clear();
	this->group_id = NULL;
	this->group_name.clear();
	this->permissons = NULL;
	this->access.clear();
	this->modifcation.clear();
	this->status_change.clear();
	this->block_size = NULL;
	children.clear();
	this->error_num = NULL;
	
	if (unlink(this->file_name) == -1)
	{
		this->error_num = errno;
		return this->error_num;
	}
	
	this->error_num = 0;
	return this->error_num;
}

/*Function name: compare
*Parameters : This function takes a fileManager object that holds the file that we want to compare with.
*Description : This function is used to compare the contents of a file with another file. It does so by reading
*the content in blocks using dynamically allocated buffers, and each iteration, the blocks are compared using a
*built in string function.
*Return : This function returns a string that indicates if the files are the same or different.
**/
string FileManager::compare(FileManager obj)
{
	if (this->getFileType(this->getType()) != "regular file")
	{
		this->error_num = ENOTSUP;
		cout << "Error! This is not a regular file!" << endl;
		return this->getErrorNumStr();
	}
	
	if (obj.getFileType(obj.getType()) != "regular file")
	{
		this->error_num = ENOTSUP;
		cout << "Error! This is not a regular file!" << endl;
		return this->getErrorNumStr();
	}
	
	char *buffer_one = new char[this->block_size];
	char *buffer_two = new char[obj.getBlockSize()];
	
	string content_one;
	string content_two;
	
	if (this->getSize() != obj.getSize())
	{
		this->error_num = 0;
		return "different!";
	}
	
	double iterations = ceil(double(this->size) / double(this->block_size));
	
	int i = 0;
	
	ifstream file_one;
	ifstream file_two;
	
	file_one.open(this->file_name);
		
	if (file_one.fail())
	{
		cout << "Error Opening File!" << endl;
		this->error_num = EIO;
		delete[] buffer_one;
		delete[] buffer_two;
		return this->getErrorNumStr();
	}
	
	file_two.open(obj.getName());
		
	if (file_two.fail())
	{
		cout << "Error Opening File!" << endl;
		this->error_num = EIO;
		delete[] buffer_one;
		delete[] buffer_two;
		return this->getErrorNumStr();
	}
	
	while (i < iterations)
	{
		file_one.read(buffer_one, this->block_size); //reads block of content from file one
		if (file_one.bad())
		{
			this->error_num = EIO;
		}
		
		file_two.read(buffer_two, this->block_size); //reads block of content from file two
		if (file_two.bad())
		{
			this->error_num = EIO;
		}
		
		content_one = buffer_one;
		content_two = buffer_two;
		
		if (content_one.compare(content_two) !=  0)
		{
			delete[] buffer_one;
			delete[] buffer_two;
			file_one.close();
			file_two.close();
			this->error_num = 0;
			return "different!";
		}	
		
		i++;
	}
	
	delete[] buffer_one;
	delete[] buffer_two;
	file_one.close();
	file_two.close();
	this->error_num = 0;
	return "the same!";
}

/*Function name: expand
*Parameters : No parameters
*Description : This function is used to populate the children vector with the contents 
*in a directory. This funtion only works on directories and will create FileManager objects
*for each file in the directory.
*Return : This function returns a string that specifies if the files were added to the vector,
*or will return the error number if the operation fails.
**/
string FileManager::expand()
{
	if (this->getFileType(this->getType()) != "directory")
	{
		this->error_num = ENOTSUP;
		return this->getErrorNumStr();
	}
	
	DIR *dir_stream = opendir(this->file_name);
	
	if (dir_stream == NULL)
	{
		this->error_num = errno;
		return this->getErrorNumStr();
	}
	
	struct dirent *next = readdir(dir_stream);
	
	errno = 0;
	
	while (next != NULL)
	{
		if ((strcmp(next->d_name, ".") == 0) || (strcmp(next->d_name, "..") == 0))
		{
			next = readdir(dir_stream);
			continue;
		}
		
		string path = get_current_dir_name();
		string name = next->d_name;
		string new_path = path + "/" + name; //this concatonates the paths and file to create a new path
		char *new_name = new char[new_path.length() + 1]; //turns the string into a char * since that is what my FileManager constructor execpts as an argument
		strcpy(new_name, new_path.c_str());
		
		FileManager file(new_name);
		this->children.push_back(file);
		next = readdir(dir_stream);
	}
	
	if (errno != 0)
	{
		this->error_num = errno;
		return this->getErrorNumStr();
	}
	
	if (closedir(dir_stream) == -1)
	{
		this->error_num = errno;
		return this->getErrorNumStr();
	}
	
	this->error_num = 0;
	return "Added Children";
	
}
