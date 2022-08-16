#ifndef PCH_H
#define PCH_H

#define MGENERICS_DLL_EXPORT __declspec(dllexport)

#include <typeinfo>              /* 类型支持库 */

#include <map>                   /* 映射 */
#include <set>                   /* 集合 */
#include <stack>                 /* 栈 */
#include <queue>                 /* 队列 */
#include <vector>                /* 列表 */
#include <unordered_map>         /* 哈希 映射 */

#include <unordered_set>         /* 哈希 集合 */

#include <mutex>                 /* 互斥锁 */
#include <thread>                /* 线程锁 */
#include <condition_variable>    /* 等待事件 */

#include <string>                /* 字符串 */
#include <iostream>              /* 输入输出流 */

#include <cmath>                 /* 数学运算库 */
#include <ctime>                 /* 时间库 */
#include <algorithm>             /* 算法库 */


#include "MPreprocessor.h"
#include "MUtil.h"
#include "MGenerics.h"

#endif //PCH_H
