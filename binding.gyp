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
			"cflags": [
				"-g",
				"-lstdc++",
				"-static-libgcc",
				"-static-libstdc++"
			],
			"cflags_cc+": [
				"-g",
				"-lstdc++",
				"-static-libgcc",
				"-static-libstdc++"
			],
			"link_settings": {
				"libraries": ["-Wl,-rpath,/usr/lib/x86_64-linux-gnu/libstdc++.so.6"],
			},
			"sources": [
				"src/main.cpp",
				"src/Fonts.cpp",
				"src/Async.cpp",
				"src/Utils.cpp"
			]
		}
	]
}