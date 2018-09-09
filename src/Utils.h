#include <nan.h>

using v8::String;
using std::string;
using std::vector;

bool isDir(const string *path);
bool isDir(const String *path);
bool isDir(const char *path);

vector<string> readDirRecursice(const char *path);
