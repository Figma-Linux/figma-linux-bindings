#include "Async.h"

void AsyncModule::Execute() {
	this->fonts = Fonts::getFonts(this->dirs);
}

void AsyncModule::HandleOKCallback() {
	HandleScope scope;
	Local<Object> fonts = New<Object>();

	for (FontResult item: this->fonts) {
		Local<Array> list = New<Array>(item.fonts.size());
		uint i = 0;

		for (Font fontItem: item.fonts) {
			Local<Object> font = New<Object>();


			Set(font, New<String>("postscript").ToLocalChecked(), New<String>(fontItem.postscript.c_str()).ToLocalChecked());
			Set(font, New<String>("family").ToLocalChecked(), New<String>(fontItem.family).ToLocalChecked());
			Set(font, New<String>("id").ToLocalChecked(), New<String>(fontItem.id).ToLocalChecked());
			Set(font, New<String>("style").ToLocalChecked(), New<String>(fontItem.style).ToLocalChecked());
			Set(font, New<String>("weight").ToLocalChecked(), New<Number>(fontItem.weight));
			Set(font, New<String>("stretch").ToLocalChecked(), New<Number>(fontItem.stretch));
			Set(font, New<String>("italic").ToLocalChecked(), New<Boolean>(fontItem.italic));

			Set(list, i, font);

			i++;
		}

		Set(fonts, New<String>(item.path).ToLocalChecked(), list);
	}


	Local<Value> argv[] = { Null(), fonts };

	this->callback->Call(2, argv);
}

// void AsyncModule::HandleErrorCallback() {

// }

NAN_METHOD(getFonts) {
	vector<string> dirs;
	Local<Array> dirsArg = Local<Array>::Cast(info[0]);
	Local<Function> cb = To<Function>(info[1]).ToLocalChecked();
	Callback *callback = new Callback(cb);

	for (int i = 0; i < dirsArg->Length(); i++) {
		Utf8String str(dirsArg->Get(i)->ToString());
		char *path = new char[string(*str).length() + 2];

		strcpy(path, *str);

		dirs.push_back(path);
	}

	AsyncQueueWorker(new AsyncModule(dirs, callback));

	info.GetReturnValue().Set(Null());
}

