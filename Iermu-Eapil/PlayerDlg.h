// MainDlg.h : interface of the PlayerDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ffplayer.h"

class PlayerDlg : public SHostWnd
{
public:
	PlayerDlg();
	~PlayerDlg();

	void*			m_hplayer;
	BOOL            m_bFullScreenMode;  // �Ƿ���ȫ��ģʽ
	BOOL            m_bOpenPlayList;    // �Ƿ�򿪲����б�
	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//���ܼ�������
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnTimer(UINT_PTR nIDEvent);
	void PlayerShowText(int time);
	void SetPlayUrl(char *url, int voiceType);
	void GetCurTimeName(char* Ctime, wchar_t* Wtime, char* name, char* postfix);
	void OnRecord();
	void OnSnapshot();
	void OnVolume();
	void OnVolumeZero();
	void FullScreen(BOOL bFull);
	void OnScreenFull();
	void OnEapilType();
	void OnPlaySwitchPause();
	void OnPlayList();
	void OnBtnOpen();
	void OnBtnPlay();
	void OnBtnPause();
	void OnBtnStop();
	void OnLButtonUp(UINT nFlags, CPoint pt);
	void OnLButtonDown(UINT nFlags, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint pt);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	void OnPlayProgress();
	void Play(const char *url);
	LRESULT OnMsg_PLAY_FILE(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//�����ļ�
	LRESULT OnMsg_ADD_FILED(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//�����ļ���ɺ��֪ͨ
	void OnDellfiles_MenuBtn();													//��ɾ���˵�
	void OnAddfiles_MenuBtn();													//�����Ӳ˵�
	int irmFlvReadFileTemplate(char *FlvFile, unsigned char *FileLink);
;protected:
	//soui��Ϣ
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"btn_record", OnRecord)
		EVENT_NAME_COMMAND(L"btn_record_stop", OnRecord)
		EVENT_NAME_COMMAND(L"btn_snapshot", OnSnapshot)
		EVENT_NAME_COMMAND(L"btn_volume", OnVolume)
		EVENT_NAME_COMMAND(L"btn_volume_zero", OnVolumeZero)
		EVENT_NAME_COMMAND(L"btn_screen_full", OnScreenFull)
		EVENT_NAME_COMMAND(L"btn_eapiltype", OnEapilType)
		EVENT_NAME_COMMAND(L"btn_playlist", OnPlayList)
		EVENT_ID_COMMAND(200, OnBtnPlay)
		EVENT_ID_COMMAND(201, OnBtnPause)
		EVENT_ID_COMMAND(202, OnBtnStop)
		EVENT_ID_COMMAND(700, OnAddfiles_MenuBtn)
		EVENT_ID_COMMAND(701, OnDellfiles_MenuBtn)
		EVENT_MAP_END()

		//HostWnd��ʵ������Ϣ����
		BEGIN_MSG_MAP_EX(PlayerDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_TIMER(OnTimer)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		//MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_KEYDOWN(OnKeyDown)
		MESSAGE_HANDLER(MS_PLAYING_PATHNAME, OnMsg_PLAY_FILE)
		MESSAGE_HANDLER(MS_ADD_FILESED, OnMsg_ADD_FILED)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;
	char			m_playUrl[60];		//����·��
	int				m_voiceType;		//�Ƿ�������
	CSize			m_rtClient;
	BOOL			m_ctrl_down;
	BOOL			m_bIsRecording;
	SSliderBar*		m_VolumeSlider;
	SSliderBar*		m_Sliderbarpos;
	int				m_LButtonDown;
	int				m_eapilType;		// ȫ��ģʽ
	WINDOWPLACEMENT m_OldWndPlacement;  // ���洰��ԭ����λ��
	int				m_listWidth;		// �ұ�list���
	int				m_captionHeight;	// ����title�߶�
	int				m_toolsHeight;		// ����tools�߶�
	SListView*		m_Play_List_Wnd;	//�����б�ؼ�
	TCHAR			m_strTxt[MAX_PATH];
};
