#include <regex>
#include <dirent.h>
#include <fstream>
#include <node.h>
#include <nan.h>
#include <ft2build.h>
#include <freetype/ttunpat.h>
#include FT_FREETYPE_H

NAN_METHOD(GetFonts);