import bindings from './build/Release/bindings';

let fonts;
let dirs = [
	'/usr/share/fonts',
	`${process.env.HOME}/.local/share/fonts`
];

bindings.getFonts(dirs, (err, fonts) => {
	console.log('fonts: ', fonts);
});

console.log('print first');
