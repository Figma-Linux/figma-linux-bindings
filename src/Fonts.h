#include <node.h>
#include <nan.h>
#include <dirent.h>
#include <regex>
#include <ft2build.h>
#include <freetype/ttunpat.h>
#include FT_FREETYPE_H

NAN_METHOD(GetFonts);