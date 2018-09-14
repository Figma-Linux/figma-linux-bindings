import binding from './build/Release/loadfonts';

let fonts;

try {
	fonts = binding.getFonts([
		'/usr/share/fonts',
		`${process.env.HOME}/.local/share/fonts`
	
	]);
} catch (error) {
	console.log('\nfonts error: ', error);
}