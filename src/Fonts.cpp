#include "Fonts.h"
#include "Utils.h"

using v8::Local;
using v8::Array;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Boolean;
using Nan::ThrowError;
using Nan::Utf8String;
using Nan::New;
using Nan::Set;
using std::string;
using std::vector;
using std::regex;
using std::regex_match;
using std::ios;
using std::ifstream;
using std::streamsize;


/**
 * This method accept one param, is array<string>
 * Paths to fonts folder. 
 */
NAN_METHOD(GetFonts) {
	Local<Array> dirs = Local<Array>::Cast(info[0]);

	DIR *dir;
	struct dirent *entry;
	vector<string> fontList;
	regex ext(".+\\.(tt[fc]|otf|pfb)");

	for (uint i = 0; i < dirs->Length(); i++) {
		Utf8String path(dirs->Get(i)->ToString());

		dir = opendir(*path);
		if (!dir) {
			char *err = new char[string(*path).length() + 25];
			sprintf(err, "Cannot open directory: %s", string(*path).c_str());

			perror("diropen");
			ThrowError(New<String>(string(err)).ToLocalChecked());
			continue;
		}

		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0) {
				char *p = new char[path.length() + strlen(entry->d_name) + 2];

				strcpy(p, *path);
				strcat(p, "/");
				strcat(p, entry->d_name);

				if (isDir(p)) {
					vector<string> result = readDirRecursice(p);
					fontList.insert(fontList.end(), result.begin(), result.end());
				} else if (regex_match(p, ext)) {
					fontList.push_back(p);
				}
			}
		}

		closedir(dir);
	}


	FT_Library lib;
	FT_Error err;

	err = FT_Init_FreeType(&lib);
	if (err) {
		perror("FT_Init_FreeType");
		ThrowError(New<String>("Failed to initialize freetype lib").ToLocalChecked());
		exit(1);
	}

	Local<Object> fonts = New<Object>();
	uint numFaces = 1;

	for (auto it = fontList.begin(); it != fontList.end(); it++) {
		auto i = it - fontList.begin();

		ifstream fontFile(fontList[i], ios::binary | ios::ate);
		streamsize size = fontFile.tellg();
		fontFile.seekg(0, ios::beg);

		vector<char> buffer(size);
		if (fontFile.read(buffer.data(), size)) {
			FT_Face face;

			err = FT_New_Memory_Face(lib, (FT_Byte*)(buffer.data()), size, 0, &face);
			if (err != 0) {
				char *err = new char[fontList[i].length() + 255];
				sprintf(err, "Failed to open font: %s, error code: %s (see: https://github.com/aseprite/freetype2/blob/master/include/freetype/fterrdef.h)\n", fontList[i].c_str(), err);

				ThrowError(New<String>(string(err)).ToLocalChecked());
				continue;
			}

			numFaces = (uint)face->num_faces;

			Local<Array> list = New<Array>((int)face->num_faces);
			regex italic(".*[Ii]talic");

			if (numFaces == 1) {
				Local<Object> font = New<Object>();

				Set(font, New<String>("postscript").ToLocalChecked(), New<String>(FT_Get_Postscript_Name(face)).ToLocalChecked());
				Set(font, New<String>("family").ToLocalChecked(), New<String>(face->family_name).ToLocalChecked());
				Set(font, New<String>("id").ToLocalChecked(), New<String>(face->family_name).ToLocalChecked());
				Set(font, New<String>("style").ToLocalChecked(), New<String>(face->style_name).ToLocalChecked());
				Set(font, New<String>("weight").ToLocalChecked(), New<Number>(400));
				Set(font, New<String>("stretch").ToLocalChecked(), New<Number>(5));
				Set(font, New<String>("italic").ToLocalChecked(), New<Boolean>((regex_match(face->style_name, italic)) ? true : false));

				Set(list, 0, font);
			} else if (numFaces > 1) {

				for (uint j = 0; j < numFaces; j++) {
					FT_Face f;

					err = FT_New_Memory_Face(lib, (FT_Byte*)(buffer.data()), size, j, &f);
					if (err == 0) {
						Local<Object> font = New<Object>();

						Set(font, New<String>("postscript").ToLocalChecked(), New<String>(FT_Get_Postscript_Name(f)).ToLocalChecked());
						Set(font, New<String>("family").ToLocalChecked(), New<String>(f->family_name).ToLocalChecked());
						Set(font, New<String>("id").ToLocalChecked(), New<String>(f->family_name).ToLocalChecked());
						Set(font, New<String>("style").ToLocalChecked(), New<String>(f->style_name).ToLocalChecked());
						Set(font, New<String>("weight").ToLocalChecked(), New<Number>(400));
						Set(font, New<String>("stretch").ToLocalChecked(), New<Number>(5));
						Set(font, New<String>("italic").ToLocalChecked(), New<Boolean>((regex_match(f->style_name, italic)) ? true : false));

						Set(list, j, font);
					} else {
						printf("Cannot open font item at %d in file: %s, error code: %d\n", j, fontList[i].c_str(), err);
					}

				}

			}

			Set(fonts, New<String>(fontList[i]).ToLocalChecked(), list);
		}
	}

	info.GetReturnValue().Set(fonts);
}


