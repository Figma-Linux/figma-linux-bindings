#include "Fonts.h"
#include "Utils.h"

using v8::Local;
using v8::Array;
using Nan::TypeError;
using Nan::Utf8String;
using std::string;
using std::vector;


/**
 * This method accept one param, is array<string>
 * Paths to fonts folder. 
 */
NAN_METHOD(GetFonts) {
	Local<Array> dirs = Local<Array>::Cast(info[0]);

	DIR *dir;
	struct dirent *entry;
	vector<string> fonts;

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
					fonts.insert(fonts.end(), result.begin(), result.end());
				} else {
					fonts.push_back(p);
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

	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		auto i = it - fonts.begin();
		printf("font: %s\n", fonts[i].c_str());
	}

	info.GetReturnValue().Set(info[0]);
}


