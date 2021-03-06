// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#define  _CRT_SECURE_NO_WARNINGS
#define	 DLL_SOUI
#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>
#include <com-cfg.h>
#include "resource.h"
#define R_IN_CPP	//定义这个开关来
#include "res\resource.h"
using namespace SOUI;


#define RELEASEPLAYER(player) \
if (player) \
{ \
	player_close(player); \
	player = NULL; \
}

#define WM_USER_PLAYING				WM_USER + 1				// 开始播放文件
#define WM_USER_POS_CHANGED			WM_USER + 2				// 文件播放位置改变
#define WM_USER_END_REACHED			WM_USER + 3				// 播放完毕
#define MS_REALWND					WM_USER+200
#define MS_OPENVIDEO_REALWND		WM_USER+201				//父子窗口通信
#define MS_CLOSEVIDEO_REALWND		WM_USER+202				//父子窗口通信
#define MS_PLAYING_PATHNAME			WM_USER+203				//通知播放文件
#define MS_ADD_FILESED				WM_USER+204				//增加文件后的通知