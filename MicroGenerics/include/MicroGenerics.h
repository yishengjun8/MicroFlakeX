#pragma once

#ifndef MICROGENERICS_H
#define MICROGENERICS_H

#define MGENERICS_DLL_EXPORT __declspec(dllimport)

#include <typeinfo>              /* ����֧�ֿ� */

#include <map>                   /* ӳ�� */
#include <set>                   /* ���� */
#include <stack>                 /* ջ */
#include <queue>                 /* ���� */
#include <vector>                /* �б� */
#include <unordered_map>         /* ��ϣ ӳ�� */
#include <unordered_set>         /* ��ϣ ���� */

#include <mutex>                 /* ������ */
#include <thread>                /* �߳��� */
#include <condition_variable>    /* �ȴ��¼� */

#include <string>                /* �ַ��� */
#include <iostream>              /* ��������� */

#include <cmath>                 /* ��ѧ����� */
#include <ctime>                 /* ʱ��� */
#include <algorithm>             /* �㷨�� */


#include "MicroGenerics/MPreprocessor.h"
#include "MicroGenerics/MUtil.h"
#include "MicroGenerics/MGenerics.h"


#endif //MICROFLAKEX_CALL_H