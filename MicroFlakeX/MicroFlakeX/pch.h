#ifndef PCH_H
#define PCH_H

#include <windows.h>
#include <windowsx.h>

#include <stdarg.h>
#include <typeinfo>

#include <any>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <mutex>
#include <stack>
#include <thread>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include <cmath>
#include <ctime>

#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>


#include "Gdiplus.h"
#pragma comment(lib, "Gdiplus.lib")

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")


#define MFX_PORT __declspec(dllexport)

#include "MfxBase.h"
#include "MfxType.h"
#include "MfxGraph.h"
#include "MfxExplain.h"
#include "MfxAppFrame.h"


#endif //PCH_H