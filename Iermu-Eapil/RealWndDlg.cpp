#include "StdAfx.h"
#include "RealWndDlg.h"


CRealWndDlg::CRealWndDlg():SHostDialog(_T("LAYOUT:XML_REALWND"))								
{
	m_menu_open.LoadMenu(_T("LAYOUT:menu_open"));
	m_ctrl_down = FALSE;
}

CRealWndDlg::~CRealWndDlg(void)
{
}
void CRealWndDlg::On_Menu_Open()
{
	CRect rc_menu;
	SWindow * pBtn = FindChildByID(401);
	if (pBtn)
	{
		pBtn->GetClientRect(&rc_menu);
		ClientToScreen(&rc_menu);
		m_menu_open.TrackPopupMenu(0, rc_menu.left, rc_menu.bottom, m_hWnd);
	}
}
void CRealWndDlg::On_Open_Files()
{
	::SendMessageW(SApplication::getSingleton().GetMainWnd(), MS_REALWND, 0, (LPARAM)(int)1);
}
void CRealWndDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{

	if (uNotifyCode == 0)
	{
		if (nID == 2000)
		{
			::SendMessageW(SApplication::getSingleton().GetMainWnd(), MS_REALWND, 0, (LPARAM)(int)2);
		}		
	}
}
// ¼üÅÌÏûÏ¢
void CRealWndDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_ESCAPE:
		m_dlgplayer->FullScreen(FALSE);
		break;
	case VK_CONTROL:
		m_ctrl_down = TRUE;
		break;
	case VK_RIGHT:
		m_dlgplayer->PlayerJumpNextTime(15000);
		break;
	case VK_LEFT:
		m_dlgplayer->PlayerJumpNextTime(-5000);
		break;
	case VK_UP:
		m_dlgplayer->PlayerSetSpeed(25);
		break;
	case VK_DOWN:
		m_dlgplayer->PlayerSetSpeed(-25);
		break;
	case VK_SPACE:
		if (m_dlgplayer->m_isplaying)
			m_dlgplayer->OnBtnPause();
		else
		{
			player_play(m_dlgplayer->m_hplayer);
			m_dlgplayer->m_isplaying = TRUE;
			m_dlgplayer->OnPlaySwitchPause();
		}
		break;
	case 'R'://Ctrl + R
		if (m_ctrl_down)
		{
			m_dlgplayer->OnRecord();
		}
		break;
	case 'S'://Ctrl + S
		if (m_ctrl_down)
		{
			m_dlgplayer->OnSnapshot();
		}
		break;
	}
}

void CRealWndDlg::OnLbuttonDBLCLK(UINT nFlags, CPoint pt)
{	
	//Ë«»÷È«ÆÁ/ÍË³ö
	m_dlgplayer->m_bFullScreenMode ? m_dlgplayer->FullScreen(FALSE) : m_dlgplayer->FullScreen(TRUE);
	
	SetMsgHandled(false);
}

//void CRealWndDlg::OnLbuttonup(UINT nFlags, CPoint pt)
//{
//
//	//if (GetWindowRect().PtInRect(pt))//µ¥»÷²¥·Å/ÔÝÍ£
//	//	::SendMessageW(SApplication::getSingleton().GetMainWnd(), MS_REALWND, 0, (LPARAM)(int)14);
//	SetMsgHandled(false);
//
//}

void CRealWndDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_dlgplayer)
	{
		player_leftbtndown(m_dlgplayer->m_hplayer, point.x, point.y);
	}

	//if (!m_bLiveStream) {
	//	if (point.y > m_rtClient.bottom - 8) {
	//		LONGLONG total = 1;
	//		player_getparam(m_ffPlayer, PARAM_MEDIA_DURATION, &total);
	//		KillTimer(TIMER_ID_PROGRESS);
	//		player_seek(m_ffPlayer, total * point.x / m_rtClient.right, SEEK_PRECISELY);
	//		SetTimer(TIMER_ID_PROGRESS, 100, NULL);
	//	}
	//	else {
	//		if (!m_bPlayPause) player_pause(m_dlgplayer->m_hplayer);
	//		else player_play(m_ffPlayer);
	//		m_bPlayPause = !m_bPlayPause;
	//	}
	//}
}

void CRealWndDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_dlgplayer)
	{
		player_leftbtnup(m_dlgplayer->m_hplayer);
	}
}

void CRealWndDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_dlgplayer)
	{
		player_mousemove(m_dlgplayer->m_hplayer, point.x, point.y);
	}
}

BOOL CRealWndDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (m_dlgplayer)
	{
		player_mousewheel(m_dlgplayer->m_hplayer, zDelta);
		return TRUE;
	}
	return TRUE;
}

LRESULT CRealWndDlg::openVideo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_dlgplayer = (PlayerDlg*)lParam;
	return 0;
}

LRESULT CRealWndDlg::closeVideo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RELEASEPLAYER(m_dlgplayer->m_hplayer);
	
	return 0;
}

LRESULT CRealWndDlg::playVideo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int type = 1;
	switch (wParam)
	{
	case MSG_OPEN_DONE:

		player_play(m_dlgplayer->m_hplayer);
		m_dlgplayer->m_isplaying = TRUE;		
		m_dlgplayer->OnPlaySwitchPause();
		m_dlgplayer->OnPlayProgress();
		player_setparam(m_dlgplayer, PARAM_PLAY_SPEED_TYPE, &type);
		break;
	case MSG_PLAY_COMPLETED:
		RELEASEPLAYER(m_dlgplayer->m_hplayer);
		m_dlgplayer->m_isplaying = FALSE;
		m_dlgplayer->OnPlaySwitchPause();
		break;
	}
	return 0;
}

