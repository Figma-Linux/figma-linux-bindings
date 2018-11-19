#include "Fonts.h"
#include "Utils.h"


/**
 * This method accept one param, is array<string>
 * Paths to fonts folder.
 */
vector<FontResult> Fonts::getFonts(vector<string> dirs) {
	DIR *dir;
	struct dirent *entry;
	vector<string> fontList;
	regex ext(".+\\.(tt[fc]|otf|pfb)");

	for (string d: dirs) {
		dir = opendir(d.c_str());
		if (!dir) {
			printf("Cannot open directory: %s", d.c_str());
			perror("diropen");

			continue;
		}

		while((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0) {
				char *p = new char[string(d).length() + strlen(entry->d_name) + 2];

				strcpy(p, d.c_str());
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
		printf("Failed to initialize freetype lib");

		exit(1);
	}

	vector<FontResult> fonts;
	uint numFaces = 1;

	for (string fontPath: fontList) {
		FT_Face face;

		err = FT_New_Face(lib, fontPath.c_str(), 0, &face);
		if (err != 0) {
			printf("Failed to open font: %s, error code: %d (see: https://github.com/aseprite/freetype2/blob/master/include/freetype/fterrdef.h)\n", fontPath.c_str(), err);
			continue;
		}

		numFaces = (uint)face->num_faces;

		vector<FontResult> resultList;
		vector<Font> fontProps;
		regex italic(".*[Ii]talic");

		if (numFaces == 1) {
			Font font;

			font.postscript = FT_Get_Postscript_Name(face);
			font.family = face->family_name;
			font.id = face->family_name;
			font.style = face->style_name;
			font.weight = 400;
			font.stretch = 5;
			font.italic = regex_match(face->style_name, italic) ? true : false;

			fontProps.push_back(font);
		} else if (numFaces > 1) {

			for (uint j = 0; j < numFaces; j++) {
				FT_Face f;

				err = FT_New_Face(lib, fontPath.c_str(), j, &f);
				if (err == 0) {
					Font font;

					font.postscript = FT_Get_Postscript_Name(face);
					font.family = face->family_name;
					font.id = face->family_name;
					font.style = face->style_name;
					font.weight = 400;
					font.stretch = 5;
					font.italic = regex_match(face->style_name, italic) ? true : false;

					fontProps.push_back(font);
				} else {
					printf("Cannot open font item at %d in file: %s, error code: %d\n", j, fontPath.c_str(), err);
				}
			}
		}

		FontResult fontResult;
		fontResult.path = fontPath.c_str();
		fontResult.fonts = fontProps;

		fonts.push_back(fontResult);
	}

	return fonts;
}
