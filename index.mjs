import binding from './build/Release/loadfonts';

let fonts;
let dirs = [
	'/usr/share/fonts',
	`${process.env.HOME}/.local/share/fonts`
];

binding.getFonts(dirs, (err, fonts) => {
	console.log('fonts: ', fonts);
});

console.log('print first');
