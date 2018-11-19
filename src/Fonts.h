#ifndef FONTS_H_
#define FONTS_H_

#include <regex>
#include <dirent.h>
#include <node.h>
#include <ft2build.h>
#include <freetype/ttunpat.h>
#include FT_FREETYPE_H

using std::string;
using std::vector;
using std::regex;
using std::regex_match;

struct Font {
	string postscript;
	string family;
	string id;
	string style;
	uint weight;
	uint stretch;
	bool italic;
};
struct FontResult {
	string path;
	vector<Font> fonts;
};

class Fonts {

public:
	Fonts () {};
	~Fonts () {};

	static vector<FontResult> getFonts(vector<string> dirs);
};

#endif  // FONTS_H_
