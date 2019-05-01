import bindings from '../build/Release/bindings';

let fonts;
let dirs = [
	'/usr/share/fonts',
	`${process.env.HOME}/.local/share/fonts`
];

bindings.getFonts(dirs, (err, fonts) => {
	console.log('err: ', err);
	console.log('fonts: ', fonts['/home/ruut/.local/share/fonts/Shree714.ttc']);
});

console.log('print first');
