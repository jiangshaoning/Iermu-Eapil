#pragma once
#include "PlayerDlg.h"
#include "ffplayer.h"
class CRealWndDlg : public SHostDialog
{
public:
    CRealWndDlg();
    ~CRealWndDlg(void);

	void On_Menu_Open();
	void On_Open_Files();
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	//���ܼ�������
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnLbuttonDBLCLK(UINT nFlags, CPoint pt);
	void OnLbuttonup(UINT nFlags, CPoint pt);
	LRESULT openVideo(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT closeVideo(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT playVideo(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	//soui��Ϣ
	EVENT_MAP_BEGIN()
		
		EVENT_ID_COMMAND(400, On_Menu_Open)
		EVENT_ID_COMMAND(402, On_Open_Files)
	EVENT_MAP_END()
    //��Ϣӳ���
    BEGIN_MSG_MAP_EX(CRealWndDlg)
		MSG_WM_COMMAND(OnCommand)
		//������̰�����Ϣ
		MSG_WM_KEYDOWN(OnKeyDown)
		MSG_WM_LBUTTONDBLCLK(OnLbuttonDBLCLK)
		MSG_WM_LBUTTONUP(OnLbuttonup)
		MESSAGE_HANDLER_EX(MS_OPENVIDEO_REALWND, openVideo)
		MESSAGE_HANDLER_EX(MS_CLOSEVIDEO_REALWND, closeVideo)
		MESSAGE_HANDLER_EX(MSG_FANPLAYER, playVideo)	//��������������Ⱦ��Ϣ
        CHAIN_MSG_MAP(SHostDialog)
        REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
private:
	SMenuEx			m_menu_open;
	PlayerDlg*		m_dlgplayer;
	BOOL			m_ctrl_down;
};
