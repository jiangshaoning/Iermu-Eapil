// MainDlg.cpp : implementation of the PlayerDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PlayerDlg.h"	
#include "PlayListAdapter.h"
#include <time.h>
#include <shellapi.h>

#define TIMER_ID_HIDE_TEXT			3
#define TIMER_ID_PLAYING_PROGRESS	1

const TCHAR STR_MOVE_FILE_FILTER[] =
_T("媒体文件(所有类型)\0*.asf;*.avi;*.wm;*.wmp;*.wmv;*.ram; *.rm; *.rmvb; *.rp; *.rpm; *.rt; *.smi; *.smil;*.dat; *.m1v; *.m2p; *.m2t; *.m2ts; *.m2v; *.mp2v; *.mpeg; *.mpe; *.mpg; *.mpv2; *.pss; *.pva; *.tp; *.tpr; *.ts;*.m4b; *.m4p; *.m4v; *.mp4; *.mpeg4; *.mov; *.qt; *.f4v; *.flv; *.hlv; *.swf; *.ifo; *.vob;*.3g2; *.3gp; *.3gp2; *.3gpp; *.amv; *.bik; *.csf; *.divx; *.evo; *.ivm; *.mkv; *.mod; *.mts; *.ogm; *.pmp; *.scm; *.tod; *.vp6; *.webm; *.xlmv;*.aac; *.ac3; *.amr; *.ape; *.cda; *.dts; *.flac; *.mla; *.m2a; *.m4a; *.mid; *.midi; *.mka; *.mp2; *.mp3; *.mpa; *.ogg; *.ra; *.tak; *.tta; *.wav; *.wma; *.wv;\0")
_T("window媒体(*.asf; *.avi; *.wm; *.wmp; *.wmv;)\0*.asf; *.avi; *.wm; *.wmp; *.wmv;\0")
_T("real媒体(*.ram;*.rm;*.rmvb;*.rp;*.rpm;*.rt;*.smi;*.smil;)\0*.ram;*.rm;*.rmvb;*.rp;*.rpm;*.rt;*.smi;*.smil;\0")
_T("MPEG1/2媒体(*.dat;*.m1v;*.m2p;*.m2t;*.m2ts;*.m2v;*.mp2v;*.mpeg;*.mpe;*.mpg;*.mpv2;*.pss;*.pva;*.tp;*.tpr;*.ts;)\0*.dat; *.m1v; *.m2p; *.m2t; *.m2ts; *.m2v; *.mp2v; *.mpeg; *.mpe; *.mpg; *.mpv2; *.pss; *.pva; *.tp; *.tpr; *.ts;\0")
_T("MPEG4媒体(*.m4b;*.m4p;*.m4v;*.mp4;*.mpeg4;)\0*.m4b;*.m4p;*.m4v;*.mp4;*.mpeg4;\0")
_T("3GPP媒体(*.3g2;*.3gp;*.3gp2;*.3gpp;)\0*.3g2;*.3gp;*.3gp2;*.3gpp;\0")
_T("APPLE媒体(*.mov;*.qt;)\0*.mov;*.qt;\0")
_T("Flash媒体(*.f4v;*.flv;*.hlv;*.swf;)\0*.f4v;*.flv;*.hlv;*.swf;\0")
_T("DVD媒体(*.ifo;*.vob;)\0*.ifo;*.vob;\0")
_T("其它视频文件(*.amv;*.bik;*.csf;*.*.divx;*.evo;*.ivm;*.mkv;*.mod;*.mts;*.ogm;*.pmp;*.scm;*.tod;*.vp6;*.webm;*.xlmv;)\0*.amv;*.bik;*.csf;*.*.divx;*.evo;*.ivm;*.mkv;*.mod;*.mts;*.ogm;*.pmp;*.scm;*.tod;*.vp6;*.webm;*.xlmv;\0")
_T("其它音频文件(*.aac;*.ac3;*.amr;*.ape;*.cda;*.dts;*.flac;*.mla;*.m2a;*.m4a;*.mid;*.midi;*.mka;*.mp2;*.mp3;*.mpa;*.ogg;*.ra;*.tak;*.tta;*.wav;*.wma;*.wv;)\0*.aac;*.ac3;*.amr;*.ape;*.cda;*.dts;*.flac;*.mla;*.m2a;*.m4a;*.mid;*.midi;*.mka;*.mp2;*.mp3;*.mpa;*.ogg;*.ra;*.tak;*.tta;*.wav;*.wma;*.wv;\0");


const TCHAR STR_SUPPORT_FILE_EXT[] =
_T("*.asf;*.avi;*.wm;*.wmp;*.wmv;*.ram;*.rm;*.rmvb;*.rp;*.rpm;*.rt;*.smi;*.smil;*.dat;*.m1v;*.m2p;*.m2t;*.m2ts;*.m2v;*.mp2v;*.mpeg;*.mpe;*.mpg;*.mpv2;*.pss;*.pva;*.tp;*.tpr;*.ts;*.m4b;*.m4p;*.m4v;*.mp4;*.mpeg4;*.mov;*.qt;*.f4v;*.flv;*.hlv;*.swf;*.ifo;*.vob;*.3g2;*.3gp;*.3gp2;*.3gpp;*.amv;*.bik;*.csf;*.divx;*.evo;*.ivm;*.mkv;*.mod;*.mts; *.ogm; *.pmp; *.scm; *.tod; *.vp6; *.webm; *.xlmv;*.aac; *.ac3; *.amr; *.ape; *.cda; *.dts; *.flac; *.mla; *.m2a; *.m4a; *.mid; *.midi; *.mka; *.mp2; *.mp3; *.mpa; *.ogg; *.ra; *.tak; *.tta; *.wav; *.wma; *.wv;");


//增加文件结构体
struct Thread_add
{
	SListView* plist;
	vector<SStringT> files;
	HWND hwnd;
};
//增加文件线程提高UI响应速度
static DWORD WINAPI threadadd(LPVOID lpParameter)
{
	struct Thread_add* prama1 = (struct Thread_add *)lpParameter;
	SListView  *mclist = prama1->plist;
	vector<SStringT> pfiles = prama1->files;
	HWND phwnd = prama1->hwnd;
	delete prama1;
	CPlayListWnd *pAdapter = (CPlayListWnd*)mclist->GetAdapter();
	for (vector<SStringT>::iterator it = pfiles.begin(); it != pfiles.end(); ++it)
	{
		SStringT  path_name = *it;
		pAdapter->ADD_files(path_name);
	}
	::PostMessage(phwnd, MS_ADD_FILESED, 0, 0);
	return 0;
}

static unsigned short AMF_DecodeInt16(const char *data)
{
	unsigned char *c = (unsigned char *)data;
	unsigned short val;
	val = (c[0] << 8) | c[1];
	return val;
}

static int BinaryBytes2String(const unsigned char* pSrc, int nSrcLength, char* pDst)
{
	if (pSrc == 0 || pDst == 0)
		return 0;

	const char tab[] = "0123456789abcdef";

	for (int i = 0; i<nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];
		*pDst++ = tab[*pSrc & 0x0f];
		pSrc++;
	}

	*pDst = '/0';

	return nSrcLength * 2;
}

//文件文件夹拖入
class CTestDropTarget1 : public CTestDropTarget
{
protected:
	SWindow *m_pmanwindow;
	HWND m_hwnd;
	SListView  *mclist;

public:
	CTestDropTarget1(SWindow *pwindow, HWND hwnd, SListView *pmclist) :m_pmanwindow(pwindow), m_hwnd(hwnd), mclist(pmclist)
	{
		if (m_pmanwindow) m_pmanwindow->AddRef();
	}
	~CTestDropTarget1()
	{
		if (m_pmanwindow) m_pmanwindow->Release();
	}
public:
	virtual HRESULT STDMETHODCALLTYPE Drop(
		/* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
		/* [in] */ DWORD grfKeyState,
		/* [in] */ POINTL pt,
		/* [out][in] */ __RPC__inout DWORD *pdwEffect)
	{
		FORMATETC format =
		{
			CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
		};
		STGMEDIUM medium;
		if (FAILED(pDataObj->GetData(&format, &medium)))
		{
			return S_FALSE;
		}

		HDROP hdrop = static_cast<HDROP>(GlobalLock(medium.hGlobal));

		if (!hdrop)
		{
			return S_FALSE;
		}

		//////////////////////////////////////////////////////////////////////////
		UINT nFileCount = ::DragQueryFile(hdrop, -1, NULL, 0);

		TCHAR szFileName[_MAX_PATH] = _T("");
		DWORD dwAttribute;
		std::vector<SStringT> vctString;

		// 获取拖拽进来文件和文件夹
		for (UINT i = 0; i < nFileCount; i++)
		{
			::DragQueryFile(hdrop, i, szFileName, sizeof(szFileName));
			dwAttribute = ::GetFileAttributes(szFileName);

			// 是否为文件夹
			if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
			{
				::SetCurrentDirectory(szFileName);
				CFileHelp::EnumerateFiles(vctString, STR_SUPPORT_FILE_EXT);
			}
			else
			{
				if (CFileHelp::FindFileExt(szFileName, STR_SUPPORT_FILE_EXT))
					vctString.push_back(szFileName);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		GlobalUnlock(medium.hGlobal);
		if (m_pmanwindow)
		{
			struct Thread_add *prama1 = new Thread_add;
			prama1->files = vctString;
			prama1->plist = mclist;
			prama1->hwnd = m_hwnd;
			HANDLE hThread = CreateThread(NULL, 0, &threadadd, (LPVOID)prama1, 0, 0);
		}
		*pdwEffect = DROPEFFECT_LINK;
		return S_OK;
	}
};

PlayerDlg::PlayerDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
	m_hplayer = NULL;
	m_voiceType = 0;
	m_eapilType = 0;
	m_bIsRecording = FALSE;
	m_ctrl_down = FALSE;
	m_LButtonDown = 0;
	m_bFullScreenMode = FALSE;
	m_bOpenPlayList = TRUE;
	m_captionHeight = 40;
	m_toolsHeight = 60;
	m_listWidth = 260;
	memset(m_playUrl, 0, sizeof(m_playUrl));
}

PlayerDlg::~PlayerDlg()
{
	RELEASEPLAYER(m_hplayer);
}

int PlayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL PlayerDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	SRealWnd  *p_RealWnd = FindChildByName2<SRealWnd>(L"ffplaywnd");
	HWND PlayHwnd = p_RealWnd->GetRealHwnd();
	::SendMessageW(PlayHwnd, MS_OPENVIDEO_REALWND, 0, (LPARAM)(void *)this);

	//RELEASEPLAYER(m_hplayer);
	//SRealWnd  *p_RealWnd = FindChildByName2<SRealWnd>(L"ffplaywnd");
	//if (p_RealWnd)
	//{
	//	HWND PlayHwnd = NULL;
	//	PLAYER_INIT_PARAMS	Params;
	//	PlayHwnd = p_RealWnd->GetRealHwnd();
	//	memset(&Params, 0, sizeof(Params));
	//	Params.adev_render_type = ADEV_RENDER_TYPE_WAVEOUT;
	//	Params.vdev_render_type = VDEV_RENDER_TYPE_GDI;
	//	Params.init_timeout = 10000;
	//	if (m_voiceType)
	//	{
	//		Params.audio_stream_cur = -1;
	//		Params.low_delay = 1;
	//	}
	//	m_hplayer = player_open((char *)"D:\\4033E1F3DCC04F54B12DBDE9A2A4889D.MP4", PlayHwnd, &Params);

	//	::SendMessageW(PlayHwnd, MS_OPENVIDEO_REALWND, 0, (LPARAM)(void *)this);
	//}
	m_Sliderbarpos = FindChildByName2<SSliderBar>(L"sliderbarpos");
	if (m_Sliderbarpos)
	{
		m_Sliderbarpos->SetRange(0, 1000);
	}

	m_VolumeSlider = FindChildByName2<SSliderBar>(L"volumeSlider");
	if (m_VolumeSlider)
	{
		int volume = m_VolumeSlider->GetValue();
		//m_VolumeSlider->SetRange(-182, 73);
		player_setparam(m_hplayer, PARAM_AUDIO_VOLUME, (void*)&volume);
	}

	m_Play_List_Wnd = FindChildByName2<SListView>(L"lv_play_list");
	if (m_Play_List_Wnd)
	{
		HRESULT hr = ::RegisterDragDrop(m_hWnd, GetDropTarget());
		RegisterDragDrop(m_Play_List_Wnd->GetSwnd(), new CTestDropTarget1(m_Play_List_Wnd, m_hWnd, m_Play_List_Wnd));//注册拖动
		CPlayListWnd *pTvAdapter = new CPlayListWnd(m_hWnd);
		m_Play_List_Wnd->SetAdapter(pTvAdapter);
		pTvAdapter->Release();
	}
	return 0;
}
//TODO:消息映射
void PlayerDlg::OnClose()
{
	RELEASEPLAYER(m_hplayer);
	CSimpleWnd::DestroyWindow();
}

void PlayerDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void PlayerDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void PlayerDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void PlayerDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;

	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if (!pBtnMax || !pBtnRestore) return;

	if (nType != SIZE_MINIMIZED) {
		m_rtClient = size;
		player_setrect(m_hplayer, 0, 2, 0, size.cx - 4 - m_listWidth, size.cy - m_captionHeight - m_toolsHeight);
		player_setrect(m_hplayer, 1, 2, 0, size.cx - 4 - m_listWidth, size.cy - m_captionHeight - m_toolsHeight);
	}
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}

}

void PlayerDlg::OnPlayProgress()
{
	SetTimer(TIMER_ID_PLAYING_PROGRESS, 1000);
}

void PlayerDlg::Play(const char *url)
{
	SRealWnd  *p_RealWnd = FindChildByName2<SRealWnd>(L"ffplaywnd");
	if (p_RealWnd)
	{
		unsigned char temp[1024] = { 0 };
		char templet[1024] = { 0 };
		int temp_len = 0;
		HWND PlayHwnd = NULL;
		PLAYER_INIT_PARAMS	Params;
		PlayHwnd = p_RealWnd->GetRealHwnd();
		memset(&Params, 0, sizeof(Params));
		Params.adev_render_type = ADEV_RENDER_TYPE_WAVEOUT;
		Params.vdev_render_type = VDEV_RENDER_TYPE_GDI;
		Params.init_timeout = 10000;
		if (m_voiceType)
		{
			Params.audio_stream_cur = -1;
			Params.low_delay = 1;
		}
		temp_len = irmFlvReadFileTemplate((char *)url, temp);
		if (temp_len > 1)
		{
			temp_len = BinaryBytes2String(temp, temp_len, templet);
			// load fanplayer init params
			Params.vdev_render_type = VDEV_RENDER_TYPE_EAPIL;
			memcpy(Params.eapil_template, templet, temp_len);
		}
		RELEASEPLAYER(m_hplayer);
		m_hplayer = player_open((char *)url, PlayHwnd, &Params);

		::SendMessageW(PlayHwnd, MS_OPENVIDEO_REALWND, 0, (LPARAM)(void *)this);
	}
}

//增加文件完成后的通知 如果有文件则显示列表
LRESULT PlayerDlg::OnMsg_ADD_FILED(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled)
{
	CPlayListWnd *pAdapter = (CPlayListWnd*)m_Play_List_Wnd->GetAdapter();
	if (pAdapter->getCount()>0)
	{
		SWindow   *playlist_wnd = FindChildByID(8000);
		if (!playlist_wnd->IsVisible())
		{
			playlist_wnd->SetVisible(true, true);
		}
	}
	pAdapter->notifyDataSetChanged();
	return 0;
}



//双击列表通知播放文件
LRESULT PlayerDlg::OnMsg_PLAY_FILE(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled)
{
	Play((char *)lp);
	return 0;
}

//接受键盘输入
void PlayerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_ESCAPE:
		FullScreen(FALSE);
		break;
	case VK_CONTROL:
		m_ctrl_down = TRUE;
		break;
	case 'R'://Ctrl + R
		if (m_ctrl_down)
		{
			OnRecord();
		}
		break;
	case 'S'://Ctrl + S
		if (m_ctrl_down)
		{
			OnSnapshot();
		}
		break;
	}
}

void PlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	int64_t pos = 0;
	int64_t total = 1;
	int value = 0;
	switch (nIDEvent)
	{
	case TIMER_ID_PLAYING_PROGRESS:
		if (!m_hplayer)
		{
			KillTimer(TIMER_ID_PLAYING_PROGRESS);
			break;
		}
		player_getparam(m_hplayer, PARAM_MEDIA_DURATION, &total);
		player_getparam(m_hplayer, PARAM_MEDIA_POSITION, &pos);
		value = (int)(1000 * pos / total);
		m_Sliderbarpos->SetValue(value);

		break;
	case TIMER_ID_HIDE_TEXT:
		KillTimer(TIMER_ID_HIDE_TEXT);
		player_textout(m_hplayer, 0, 0, 0, NULL);
		m_strTxt[0] = '\0';
		break;
	}
}

void PlayerDlg::PlayerShowText(int time)
{
	player_textout(m_hplayer, 20, 20, RGB(0, 255, 0), m_strTxt);
	SetTimer(TIMER_ID_HIDE_TEXT, time);
}

void PlayerDlg::SetPlayUrl(char *url, int voiceType)
{
	m_voiceType = voiceType;
	strcpy(m_playUrl, url);
}

void PlayerDlg::GetCurTimeName(char* Ctime, wchar_t* Wtime, char* name, char* postfix)
{
	time_t curtime = time(NULL);
	tm *ptm = localtime(&curtime);

	sprintf(Ctime, "%s_%d%02d%02d%02d%02d%02d.%s", name, ptm->tm_year + 1900, ptm->tm_mon + 1,
		ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, postfix);

	MultiByteToWideChar(CP_ACP, 0, Ctime, -1, Wtime, 40);

}

void PlayerDlg::OnRecord()
{
	if (!m_hplayer) return;

	char ctime[40] = { 0 };
	wchar_t wtime[48] = {0};
	GetCurTimeName(ctime, wtime, "record", "mp4");
	player_record(m_hplayer, m_bIsRecording ? NULL : ctime);
	m_bIsRecording = !m_bIsRecording;
	if (m_bIsRecording)
	{
		FindChildByName2<SWindow>(L"btn_record")->SetVisible(FALSE, TRUE);
		FindChildByName2<SWindow>(L"btn_record_stop")->SetVisible(TRUE, TRUE);
	}
	else
	{
		FindChildByName2<SWindow>(L"btn_record")->SetVisible(TRUE, TRUE);
		FindChildByName2<SWindow>(L"btn_record_stop")->SetVisible(FALSE, TRUE);
	}

	_stprintf(m_strTxt, _T("%s: %s"), m_bIsRecording ? _T("开始录屏") : _T("结束录屏 保存到当前路径"), wtime);
	PlayerShowText(3000);
}

void PlayerDlg::OnSnapshot()
{
	if (!m_hplayer) return;

	char ctime[40] = { 0 };
	wchar_t wtime[48] = { 0 };
	GetCurTimeName(ctime, wtime, "snapshot", "jpg");
	player_snapshot(m_hplayer, ctime, 0, 0, 1000);
	_stprintf(m_strTxt, _T("抓拍到当前路径：%s"), wtime);
	PlayerShowText(3000);
}

void PlayerDlg::OnVolume()
{
	int volume = -182;
	FindChildByName2<SWindow>(L"btn_volume")->SetVisible(FALSE, TRUE);
	FindChildByName2<SWindow>(L"btn_volume_zero")->SetVisible(TRUE, TRUE);
	player_setparam(m_hplayer, PARAM_AUDIO_VOLUME, (void*)&volume);
}

void PlayerDlg::OnVolumeZero()
{
	int volume = m_VolumeSlider->GetValue();
	FindChildByName2<SWindow>(L"btn_volume")->SetVisible(TRUE, TRUE);
	FindChildByName2<SWindow>(L"btn_volume_zero")->SetVisible(FALSE, TRUE);
	player_setparam(m_hplayer, PARAM_AUDIO_VOLUME, (void*)&volume);
}


void PlayerDlg::FullScreen(BOOL bFull)
{
	int iBorderX = GetSystemMetrics(SM_CXFIXEDFRAME) + GetSystemMetrics(SM_CXBORDER);
	int iBorderY = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYBORDER);
	m_bFullScreenMode = bFull;

	if (bFull)
	{

		::GetWindowPlacement(m_hWnd, &m_OldWndPlacement);

		if (::IsZoomed(m_hWnd))
		{
			::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		}

		::SetWindowPos(m_hWnd, HWND_TOP, -iBorderX, -iBorderY, GetSystemMetrics(SM_CXSCREEN) + 2 * iBorderX + m_listWidth, GetSystemMetrics(SM_CYSCREEN) + 2 * iBorderY + m_captionHeight + m_toolsHeight, 0);
		m_captionHeight = 0;
		m_toolsHeight = 0;
		SCaption  *cap = FindChildByID2<SCaption>(6000);
		cap->SetVisible(FALSE, TRUE);
		cap = FindChildByID2<SCaption>(7000);
		cap->SetVisible(FALSE, TRUE);
		FindChildByID2<SWindow>(8000)->SetVisible(FALSE, TRUE);
	}
	else
	{
		m_captionHeight = 40;
		m_toolsHeight = 60;
		::SetWindowPlacement(m_hWnd, &m_OldWndPlacement);
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, m_listWidth, m_captionHeight + m_toolsHeight, SWP_NOSIZE | SWP_NOMOVE);

		SCaption  *cap = FindChildByID2<SCaption>(6000);
		cap->SetVisible(TRUE, TRUE);
		cap = FindChildByID2<SCaption>(7000);
		cap->SetVisible(TRUE, TRUE);
		FindChildByID2<SWindow>(8000)->SetVisible(m_bOpenPlayList, TRUE);
	}
}

void PlayerDlg::OnScreenFull()
{
	if (!m_bFullScreenMode)
		FullScreen(true);
}

void PlayerDlg::OnBtnOpen()	//打开文件
{
	vector<SStringT> names;
	CFileHelp::OpenFile(STR_MOVE_FILE_FILTER, GetHostHwnd(), names);
	if (names.empty()) return;
	struct Thread_add *prama1 = new Thread_add;
	prama1->files = names;
	prama1->plist = m_Play_List_Wnd;
	prama1->hwnd = m_hWnd;
	HANDLE hThread = CreateThread(NULL, 0, &threadadd, (LPVOID)prama1, 0, 0);
	SWindow   *playlist_wnd = FindChildByID(8000);
	if (!playlist_wnd->IsVisible())
	{
		playlist_wnd->SetVisible(true, true);
	}
}

void PlayerDlg::OnPlaySwitchPause()
{
	SImageButton *pbtnPlay = FindChildByID2<SImageButton>(200);
	SImageButton *pbtnPause = FindChildByID2<SImageButton>(201);
	if (pbtnPlay && pbtnPause)
	{
		pbtnPlay->SetVisible(!pbtnPlay->IsVisible(), TRUE);
		pbtnPause->SetVisible(!pbtnPause->IsVisible(), TRUE);
	}
}

void PlayerDlg::OnBtnPlay()
{
	int status = 0;;
	CPlayListWnd *pAdapter = (CPlayListWnd*)m_Play_List_Wnd->GetAdapter();
	int m_items = m_Play_List_Wnd->GetSel();
	if (m_items < 0) return;

	string path = S_CT2A(pAdapter->Get_index_Path(m_items));
	player_getparam(m_hplayer, PARAM_PLAYER_STATUS, &status);
	if (status >> 2 & 1)
	{
		player_play(m_hplayer);
	}
	else
	{
		m_Sliderbarpos->SetValue(0);
		Play(path.c_str());
	}
	OnPlaySwitchPause();
}

void PlayerDlg::OnBtnPause()
{
	player_pause(m_hplayer);
	OnPlaySwitchPause();
}

void PlayerDlg::OnBtnStop()
{
	RELEASEPLAYER(m_hplayer);
}

void PlayerDlg::OnPlayList()
{
	m_bOpenPlayList ? m_listWidth = 0 : m_listWidth = 260;
	player_setrect(m_hplayer, 0, 2, 0, m_rtClient.cx - 4 - m_listWidth, m_rtClient.cy - m_captionHeight - m_toolsHeight);
	player_setrect(m_hplayer, 1, 2, 0, m_rtClient.cx - 4 - m_listWidth, m_rtClient.cy - m_captionHeight - m_toolsHeight);

	SWindow  *wnd = FindChildByID2<SWindow>(8000);
	wnd->SetVisible(!wnd->IsVisible(), TRUE);
	m_bOpenPlayList = !m_bOpenPlayList;
}

void PlayerDlg::OnEapilType()
{
	int type = 0;
	player_getparam(m_hplayer, PARAM_PLAYER_RENDER_TYPE, &type);
	if (type != VDEV_RENDER_TYPE_EAPIL) return;

	m_eapilType++;
	if (m_eapilType >= 4) m_eapilType = 0;
	player_setrendertype(m_hplayer, m_eapilType);

}

//删除列表文件
void PlayerDlg::OnDellfiles_MenuBtn()
{
	CPlayListWnd *pAdapter = (CPlayListWnd*)m_Play_List_Wnd->GetAdapter();
	int m_items = m_Play_List_Wnd->GetSel();
	if (m_items < 0) return;
	if (m_items == pAdapter->getCount() - 1 && pAdapter->getCount()>1)
	{
		pAdapter->Dll_File(m_items);
		m_Play_List_Wnd->SetSel(m_items - 1);
	}
	else
		pAdapter->Dll_File(m_items);
}

//增加文件
void PlayerDlg::OnAddfiles_MenuBtn()
{
	OnBtnOpen();
}

void PlayerDlg::OnLButtonUp(UINT nFlags, CPoint pt)//处理进度条鼠标事件 播放指定位置 此处没有用EventSliderPos事件
{
	if (m_Sliderbarpos->GetWindowRect().PtInRect(pt) && m_LButtonDown == 1)
	{
		LONGLONG inter = 0;
		LONGLONG total = 1;
		player_getparam(m_hplayer, PARAM_MEDIA_DURATION, &total);
		inter = total / 1000;
		player_seek(m_hplayer, (m_Sliderbarpos->GetValue()*inter) + 1, 0);
	}
	m_LButtonDown = 0;
	SetMsgHandled(false);
}

void PlayerDlg::OnLButtonDown(UINT nFlags, CPoint pt)//处理进度条鼠标事件
{
	if (m_Sliderbarpos->GetWindowRect().PtInRect(pt))//处理进度条
		m_LButtonDown = 1;
	if (m_VolumeSlider->GetWindowRect().PtInRect(pt) && !m_voiceType)//处理音量
		m_LButtonDown = 1;
	SetMsgHandled(false);

}

//-182, 73
void PlayerDlg::OnMouseMove(UINT nFlags, CPoint pt)
{
	if (m_VolumeSlider->GetWindowRect().PtInRect(pt) && m_LButtonDown == 1 && !m_voiceType)
	{
		int volume = m_VolumeSlider->GetValue();
		switch (volume)
		{
		case -182:
			OnVolume();
			break;
		default:
			OnVolumeZero();
			break;
		}
	}
	SetMsgHandled(false);
}

BOOL PlayerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (m_hplayer)
	{
		player_mousewheel(m_hplayer, zDelta);
		return TRUE;
	}
	return TRUE;
}

int PlayerDlg::irmFlvReadFileTemplate(char *FlvFile, unsigned char *FileLink)
{
	char tbuff[1024], *tp = tbuff;
	FILE* tfd = NULL;
	int tlen = 1024;
	unsigned short len = 0;
	tfd = fopen(FlvFile, "rb");
	if (tfd >0)
	{
		tlen = fread(tbuff, 1, tlen, tfd);
		fclose(tfd);
		while (tlen > 0)
		{
			if (!memcmp(tp, "Templet", 7))
				break;
			tp++;
			tlen--;
		}

		if (tlen > 0)
		{
			len = AMF_DecodeInt16(tp + 8);
			memcpy(FileLink, tp + 10, len);
			return len;
		}
	}

	return -1;
}