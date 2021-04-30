#ifndef PCH_H
#define PCH_H
/* 数学库 */
#include <cmath>
/**/

/* STL模板库 */
/**/

/* Direct2D1 */
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
/**/

/* time库 */
#include <ctime>
/**/

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")

/**/
#include "MfxBase.h"

#define MFX_BUILDING

#endif //PCH_H
