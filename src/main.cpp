#include "Fonts.h"
#include "Async.h"
#include <nan.h>

using v8::String;
using v8::FunctionTemplate;

using Nan::Set;
using Nan::GetFunction;
using Nan::New;


NAN_MODULE_INIT(Initialize) {
	Set(target, New<String>("getFonts").ToLocalChecked(),
		GetFunction(New<FunctionTemplate>(getFonts)).ToLocalChecked()
	);
}

NODE_MODULE(loadfonts, Initialize)
