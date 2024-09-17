#ifndef OBJ_COLORHELPERS_H
#define OBJ_COLORHELPERS_H

#include "palettetools.h"

// Extra Entity Functions
Uint16 ColorHelpers_PackRGB(ObjectColor *color);

void ColorHelpers_RGBToHSL(ObjectColor *color, ObjectHSL *hsl);
void ColorHelpers_HSLToRGB(ObjectHSL *hsl, ObjectColor *color);

#endif //! OBJ_COLORHELPERS_H
