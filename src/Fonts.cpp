#include "Fonts.h"
#include "Utils.h"

using v8::Local;
using v8::Array;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Boolean;
using Nan::TypeError;
using Nan::Utf8String;
using Nan::New;
using Nan::Set;
using std::string;
using std::copy;
using std::vector;
using std::regex;
using std::regex_match;


/**
 * This method accept one param, is array<string>
 * Paths to fonts folder. 
 */
NAN_METHOD(GetFonts) {
	Local<Array> dirs = Local<Array>::Cast(info[0]);

	DIR *dir;
	struct dirent *entry;
	vector<string> fontList;

	for (uint i = 0; i < dirs->Length(); i++) {
		Utf8String path(dirs->Get(i)->ToString());

		dir = opendir(*path);
		if (!dir) {
			perror("diropen");
			TypeError("open dir error");
			exit(1);
		}

		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0) {
				char *p = new char[path.length()+strlen(entry->d_name)+1];

				strcpy(p, *path);
				strcat(p, "/");
				strcat(p, entry->d_name);

				if (isDir(p)) {
					vector<string> result = readDirRecursice(p);
					fontList.insert(fontList.end(), result.begin(), result.end());
				} else {
					fontList.push_back(p);
				}
			}
		}

		closedir(dir);
	}

	printf("\n\n");

	FT_Library lib;
	FT_Error err;

	err = FT_Init_FreeType(&lib);
	if (err) {
		perror("FT_Init_FreeType");
		TypeError("Failed to initialize freetype lib");
		exit(1);
	}

	Local<Object> fonts = New<Object>();

	for (auto it = fontList.begin(); it != fontList.end(); it++) {
		auto i = it - fontList.begin();
		FT_Face face;
		uint numFaces = 1;

		if (FT_New_Face(lib, fontList[i].c_str(), 0, &face)) {
			printf("Could not load font file: %s", fontList[i].c_str());
			continue;
		}

		numFaces = (uint)face->num_faces;

		Local<Array> list = New<Array>((int)face->num_faces);
		regex italic(".*[Ii]talic");

		if (numFaces == 1) {
			Local<Object> font = New<Object>();

			Set(font, New<String>("postscript").ToLocalChecked(), New<String>(FT_Get_Postscript_Name(face)).ToLocalChecked());
			Set(font, New<String>("family").ToLocalChecked(), New<String>(face->family_name).ToLocalChecked());
			Set(font, New<String>("style").ToLocalChecked(), New<String>(face->style_name).ToLocalChecked());
			Set(font, New<String>("weight").ToLocalChecked(), New<Number>(400));
			Set(font, New<String>("stretch").ToLocalChecked(), New<Number>(5));
			Set(font, New<String>("italic").ToLocalChecked(), New<Boolean>((regex_match(face->style_name, italic)) ? true : false));
	
			Set(list, 0, font);
		} else if (numFaces > 1) {

			FT_Parameter parameter;
			FT_Open_Args args;
			char *pathname = new char[fontList[i].length() + 1];

			copy(fontList[i].begin(), fontList[i].end(), pathname);

			parameter.tag = FT_PARAM_TAG_UNPATENTED_HINTING;
			args.flags = FT_OPEN_PATHNAME;
			args.pathname = pathname;
			args.num_params = 1;
			args.params = &parameter;

			for (uint j = 0; j < numFaces; j++) {
				FT_Face f;
				err = FT_Open_Face(lib, &args, j, &f);
				if (err == 0) {
					Local<Object> font = New<Object>();

					Set(font, New<String>("postscript").ToLocalChecked(), New<String>(FT_Get_Postscript_Name(f)).ToLocalChecked());
					Set(font, New<String>("family").ToLocalChecked(), New<String>(f->family_name).ToLocalChecked());
					Set(font, New<String>("style").ToLocalChecked(), New<String>(f->style_name).ToLocalChecked());
					Set(font, New<String>("weight").ToLocalChecked(), New<Number>(400));
					Set(font, New<String>("stretch").ToLocalChecked(), New<Number>(5));
					Set(font, New<String>("italic").ToLocalChecked(), New<Boolean>((regex_match(f->style_name, italic)) ? true : false));

					Set(list, j, font);
				}
			}
		}

		Set(fonts, New<String>(fontList[i]).ToLocalChecked(), list);

	}

	info.GetReturnValue().Set(fonts);
}


