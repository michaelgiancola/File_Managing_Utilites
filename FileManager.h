/*Author: Michael Giancola
 *Date: 03/10/2019
 *Description: This file contains the private attributes of the class and all of the function declarations.
 **/

#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <fstream>

class FileManager
{
private:
	char *file_name;
	mode_t type;
	off_t size;
	uid_t user_id;
	std ::string user_name;
	gid_t group_id;
	std ::string group_name;
	mode_t permissons;
	std::string access;
	std::string modifcation;
	std::string status_change;
	blksize_t block_size;
	std::vector<FileManager> children;
	int error_num;

public:
	FileManager();
	~FileManager();
	FileManager(char *file_name);
	char* getName();
	mode_t getType();
	mode_t getSize();
	uid_t getUserID();
	std::string getUserName();
	gid_t getGroupID();
	std::string getGroupName();
	mode_t getPermissions();
	std::string getAccessTime();
	std::string getModification();
	std::string getStatusChange();
	blksize_t getBlockSize();
	std::vector<FileManager> getChildren();
	int getErrorNum();
	std::string getErrorNumStr();
	void setName(char *file_name);
	std::string getPermissionsString(mode_t permissons);
	std::string getFileType(mode_t type);
	int dump(std::ostream& stream);
	int rename_(char* name);
	int remove();
	std::string compare(FileManager obj);
	std::string expand();
	
};

#endif // !FILEMANAGER_H



