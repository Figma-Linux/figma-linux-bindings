{
	"targets": [
		{
			"target_name": "bindings",
			"include_dirs": [
				"/usr/include/freetype2/",
				"/usr/local/include/freetype2",
				"<!(node -e \"require('nan')\")"
			],
			# "libraries": [
			# 	"../lib/freetype2/libfreetype.so.6",
			# 	"/usr/lib/x86_64-linux-gnu/libstdc++.so.6"
			# ],
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
			"sources": [
				"src/main.cpp",
				"src/Fonts.cpp",
				"src/Async.cpp",
				"src/Utils.cpp"
			]
		}
	]
}