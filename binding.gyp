{
	"targets": [
		{
			"target_name": "bindings",
			"include_dirs": [
				"/usr/include/freetype2/",
				"/usr/local/include/freetype2",
				"<!(node -e \"require('nan')\")"
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
			"sources": [
				"src/main.cpp",
				"src/Fonts.cpp",
				"src/Async.cpp",
				"src/Utils.cpp"
			]
		}
	]
}