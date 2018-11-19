# Description

This module find (by mask: \\.(tt[fc]|otf|pfb)) and combine all fonts from the passed directories. And returns IFonts object of fonts of next structure:

```typescript
interface IFontsFigmaItem {
	postscript: string;
	family: string;
	id: string;
	style?: string;
	weight?: number;
	stretch?: number;
	italic?: boolean;
}

interface IFonts {
	[path: string]: Array<IFontsFigmaItem>
}
```

Example:

```javascript
{ '/usr/share/fonts/opentype/stix/STIXVariants-Bold.otf':
   [ { postscript: 'STIXVariants-Bold',
       family: 'STIXVariants',
       id: 'STIXVariants',
       style: 'Bold',
       weight: 400,
       stretch: 5,
       italic: false } ],
  '/usr/share/fonts/opentype/stix/STIXIntegralsUpSm-Bold.otf':
   [ { postscript: 'STIXIntegralsUpSm-Bold',
       family: 'STIXIntegralsUpSm',
       id: 'STIXIntegralsUpSm',
       style: 'Bold',
       weight: 400,
       stretch: 5,
       italic: false } ],
  '/usr/share/fonts/opentype/stix/STIXNonUnicode-Regular.otf':
   [ { postscript: 'STIXNonUnicode-Regular',
       family: 'STIXNonUnicode',
       id: 'STIXNonUnicode',
       style: 'Regular',
       weight: 400,
       stretch: 5,
       italic: false } ],
  '/usr/share/fonts/opentype/stix/STIXSizeFourSym-Regular.otf':
   [ { postscript: 'STIXSizeFourSym-Regular',
       family: 'STIXSizeFourSym',
       id: 'STIXSizeFourSym',
       style: 'Regular',
       weight: 400,
       stretch: 5,
       italic: false } ],
  '/usr/share/fonts/opentype/noto/NotoSansCJK-DemiLight.ttc':
   [ { postscript: 'NotoSansCJKjp-DemiLight',
       family: 'Noto Sans CJK JP',
       id: 'Noto Sans CJK JP',
       style: 'DemiLight',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKkr-DemiLight',
       family: 'Noto Sans CJK KR',
       id: 'Noto Sans CJK KR',
       style: 'DemiLight',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKsc-DemiLight',
       family: 'Noto Sans CJK SC',
       id: 'Noto Sans CJK SC',
       style: 'DemiLight',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKtc-DemiLight',
       family: 'Noto Sans CJK TC',
       id: 'Noto Sans CJK TC',
       style: 'DemiLight',
       weight: 400,
       stretch: 5,
       italic: false } ],
  '/usr/share/fonts/opentype/noto/NotoSansCJK-Thin.ttc':
   [ { postscript: 'NotoSansCJKjp-Thin',
       family: 'Noto Sans CJK JP',
       id: 'Noto Sans CJK JP',
       style: 'Thin',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKkr-Thin',
       family: 'Noto Sans CJK KR',
       id: 'Noto Sans CJK KR',
       style: 'Thin',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKsc-Thin',
       family: 'Noto Sans CJK SC',
       id: 'Noto Sans CJK SC',
       style: 'Thin',
       weight: 400,
       stretch: 5,
       italic: false },
     { postscript: 'NotoSansCJKtc-Thin',
       family: 'Noto Sans CJK TC',
       id: 'Noto Sans CJK TC',
       style: 'Thin',
       weight: 400,
       stretch: 5,
       italic: false } ] }
```

# Usage

```javascript
import binding from './build/Release/loadfonts';

let fonts;
let dirs = [
  '/usr/share/fonts',
  `${process.env.HOME}/.local/share/fonts`
];

binding.getFonts(dirs, (err, fonts) => {
  console.log('fonts: ', fonts);
});
```
