#pragma once

#ifndef MICROFLAKEX_EXPORTS

#ifndef MICORFLAKEX_H
#define MICORFLAKEX_H

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

#define MFX_DLL_EXPORT __declspec(dllimport)
#include "MfxBase.h"
#include "MfxType.h"
#include "MfxGraph.h"
#include "MfxExplain.h"
#include "MfxAppFrame.h"

#pragma comment(lib, "MicroFlakeX_A.0.1.1.lib")

#endif
#endif