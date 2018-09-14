#include <nan.h>
#include <dirent.h>
#include <string.h>
#include <regex>

#include "Utils.h"

using Nan::Utf8String;
using Nan::ThrowError;
using Nan::New;
using v8::String;
using std::string;
using std::vector;
using std::regex;
using std::regex_match;

bool isDir(const string *path) {
	DIR *dir;
	bool exists = false;

	dir = opendir(path->c_str());

	if (dir != NULL) {
		exists = true;
		(void)closedir(dir);
	}

	return exists;
}

bool isDir(const char *path) {
	DIR *dir;
	bool exists = false;

	dir = opendir(path);

	if (dir != NULL) {
		exists = true;
		(void)closedir(dir);
	}

	return exists;
}

bool isDir(const String *path) {
	DIR *dir;
	bool exists = false;

	Utf8String p(path->ToString());
	dir = opendir(string(*p).c_str());

	if (dir != NULL) {
		exists = true;
		(void)closedir(dir);
	}

	return exists;
}

vector<string> readDirRecursice(const char *path) {
	DIR *dir;

	if (!(dir = opendir(path))) {
		char *err = new char[strlen(path) + 25];
		sprintf(err, "Cannot open directory: %s", path);

		perror("diropen");
		ThrowError(New<String>(err).ToLocalChecked());
		exit(1);
	}

	regex ext(".+\\.(tt[fc]|otf|pfb)");
	struct dirent *entry;
	vector<string> files;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0) {
			char *p = new char[strlen(path) + strlen(entry->d_name) + 2];

			strcpy(p, path);
			strcat(p, "/");
			strcat(p, entry->d_name);

			if (isDir(p)) {
				vector<string> result = readDirRecursice(p);
				files.insert(files.end(), result.begin(), result.end());
			} else if (regex_match(p, ext)) {
				files.push_back(p);
			}
		}
	}

	closedir(dir);

	return files;
}