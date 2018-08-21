#include <node/node.h>

namespace loadFonts {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;

	void test(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, "load fonts"));
	}

	void Initialize(Local<Object> exports) {
		NODE_SET_METHOD(exports, "getFonts", test);
	}

	NODE_MODULE(NODE_GYP_LOADFONTS, Initialize)
}
