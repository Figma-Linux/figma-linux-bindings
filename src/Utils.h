#include <nan.h>

using Nan::Utf8String;
using Nan::ThrowError;
using Nan::New;

using v8::String;
using v8::String;

using std::string;
using std::vector;
using std::regex;
using std::regex_match;

bool isDir(const string *path);
bool isDir(const String *path);
bool isDir(const char *path);

vector<string> readDirRecursice(const char *path);
