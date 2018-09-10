{
	"targets": [
		{
			"target_name": "loadfonts",
			"include_dirs": [
				"/usr/include/freetype2/",
				"/usr/local/include/freetype2",
				"<!(node -e \"require('nan')\")"
			],
			"libraries": [
				"../lib/freetype2/libfreetype.so"
			],
			"sources": [
				"src/main.cpp",
				"src/Fonts.cpp",
				"src/Utils.cpp"
			]
		}
	]
}