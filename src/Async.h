#ifndef ASYNC_H_
#define ASYNC_H_

#include <node.h>
#include <nan.h>

#include "Fonts.h"

using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::Utf8String;
using Nan::Null;
using Nan::New;
using Nan::Set;
using Nan::To;

using v8::Number;
using v8::Boolean;
using v8::Function;
using v8::Object;
using v8::Local;
using v8::Array;
using v8::String;
using v8::Value;

using std::vector;
using std::string;

class AsyncModule: public AsyncWorker {

public:
	AsyncModule (vector<string> dirs, Callback* callback): AsyncWorker(callback), dirs(dirs) {};
	~AsyncModule () {};

	void Execute ();
	void Destory () {};

private:
	vector<string> dirs;
	vector<FontResult> fonts;

protected:
	void HandleOKCallback ();
	// void HandleErrorCallback () {};
};

NAN_METHOD(getFonts);

#endif  // ASYNC_H_