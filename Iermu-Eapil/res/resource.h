//stamp:0925fe8728974d3f
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_REALWND = _T("LAYOUT:XML_REALWND");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_REALWND;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _PNG{
			public:
			_PNG(){
				ID_SYSBTN_CLOSE = _T("PNG:ID_SYSBTN_CLOSE");
				ID_SYSBTN_MAX = _T("PNG:ID_SYSBTN_MAX");
				ID_SYSBTN_MIN = _T("PNG:ID_SYSBTN_MIN");
				ID_SYSBTN_RESTORE = _T("PNG:ID_SYSBTN_RESTORE");
				ID_PNG_BG = _T("PNG:ID_PNG_BG");
				ID_MAIN_BK = _T("PNG:ID_MAIN_BK");
				ID_SCORLLBAR = _T("PNG:ID_SCORLLBAR");
				ID_SLIDERBACKVOLUME = _T("PNG:ID_SLIDERBACKVOLUME");
				ID_SLIDERFOREVOLUME = _T("PNG:ID_SLIDERFOREVOLUME");
				ID_SLIDERPLAYTHUMB = _T("PNG:ID_SLIDERPLAYTHUMB");
				ID_SLIDERPLAYVOLUM = _T("PNG:ID_SLIDERPLAYVOLUM");
				ID_TREEVIEW_HEADER_EXPAND = _T("PNG:ID_TREEVIEW_HEADER_EXPAND");
			}
			const TCHAR * ID_SYSBTN_CLOSE;
			const TCHAR * ID_SYSBTN_MAX;
			const TCHAR * ID_SYSBTN_MIN;
			const TCHAR * ID_SYSBTN_RESTORE;
			const TCHAR * ID_PNG_BG;
			const TCHAR * ID_MAIN_BK;
			const TCHAR * ID_SCORLLBAR;
			const TCHAR * ID_SLIDERBACKVOLUME;
			const TCHAR * ID_SLIDERFOREVOLUME;
			const TCHAR * ID_SLIDERPLAYTHUMB;
			const TCHAR * ID_SLIDERPLAYVOLUM;
			const TCHAR * ID_TREEVIEW_HEADER_EXPAND;
		}PNG;
		class _BTN{
			public:
			_BTN(){
				ID_STOP_BTN = _T("BTN:ID_STOP_BTN");
				ID_PLAY_BTN = _T("BTN:ID_PLAY_BTN");
				ID_PAUSE_BTN = _T("BTN:ID_PAUSE_BTN");
				ID_VOLUME_BTN = _T("BTN:ID_VOLUME_BTN");
				ID_VOLUME_ZERO_BTN = _T("BTN:ID_VOLUME_ZERO_BTN");
				ID_SNAPSHOT_BTN = _T("BTN:ID_SNAPSHOT_BTN");
				ID_RECORD_BTN = _T("BTN:ID_RECORD_BTN");
				ID_RECORD_STOP_BTN = _T("BTN:ID_RECORD_STOP_BTN");
				ID_SCREEN_FULL_BTN = _T("BTN:ID_SCREEN_FULL_BTN");
				ID_SCREEN_NORMAL_BTN = _T("BTN:ID_SCREEN_NORMAL_BTN");
				ID_PLAYLIST_BTN = _T("BTN:ID_PLAYLIST_BTN");
				ID_PLAYMODE_BTN = _T("BTN:ID_PLAYMODE_BTN");
				ID_PLAYADD_BTN = _T("BTN:ID_PLAYADD_BTN");
				ID_PLAYDELETE_BTN = _T("BTN:ID_PLAYDELETE_BTN");
				ID_EAPILTYPE_BTN = _T("BTN:ID_EAPILTYPE_BTN");
			}
			const TCHAR * ID_STOP_BTN;
			const TCHAR * ID_PLAY_BTN;
			const TCHAR * ID_PAUSE_BTN;
			const TCHAR * ID_VOLUME_BTN;
			const TCHAR * ID_VOLUME_ZERO_BTN;
			const TCHAR * ID_SNAPSHOT_BTN;
			const TCHAR * ID_RECORD_BTN;
			const TCHAR * ID_RECORD_STOP_BTN;
			const TCHAR * ID_SCREEN_FULL_BTN;
			const TCHAR * ID_SCREEN_NORMAL_BTN;
			const TCHAR * ID_PLAYLIST_BTN;
			const TCHAR * ID_PLAYMODE_BTN;
			const TCHAR * ID_PLAYADD_BTN;
			const TCHAR * ID_PLAYDELETE_BTN;
			const TCHAR * ID_EAPILTYPE_BTN;
		}BTN;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"aboutwnd",65548},
		{L"btn_close",65536},
		{L"btn_eapiltype",65554},
		{L"btn_max",65537},
		{L"btn_min",65539},
		{L"btn_playlist",65556},
		{L"btn_record",65550},
		{L"btn_record_stop",65551},
		{L"btn_restore",65538},
		{L"btn_screen_full",65555},
		{L"btn_snapshot",65552},
		{L"btn_volume",206},
		{L"btn_volume_zero",206},
		{L"depotwnd",65545},
		{L"ffplaywnd",65542},
		{L"filename",65544},
		{L"lv_play_list",65543},
		{L"maintab",65540},
		{L"realplay_wnd",65541},
		{L"skinwnd",65546},
		{L"sliderbarpos",65549},
		{L"urlwnd",65547},
		{L"volumeSlider",65553}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			aboutwnd = namedXmlID[1].strName;
			btn_close = namedXmlID[2].strName;
			btn_eapiltype = namedXmlID[3].strName;
			btn_max = namedXmlID[4].strName;
			btn_min = namedXmlID[5].strName;
			btn_playlist = namedXmlID[6].strName;
			btn_record = namedXmlID[7].strName;
			btn_record_stop = namedXmlID[8].strName;
			btn_restore = namedXmlID[9].strName;
			btn_screen_full = namedXmlID[10].strName;
			btn_snapshot = namedXmlID[11].strName;
			btn_volume = namedXmlID[12].strName;
			btn_volume_zero = namedXmlID[13].strName;
			depotwnd = namedXmlID[14].strName;
			ffplaywnd = namedXmlID[15].strName;
			filename = namedXmlID[16].strName;
			lv_play_list = namedXmlID[17].strName;
			maintab = namedXmlID[18].strName;
			realplay_wnd = namedXmlID[19].strName;
			skinwnd = namedXmlID[20].strName;
			sliderbarpos = namedXmlID[21].strName;
			urlwnd = namedXmlID[22].strName;
			volumeSlider = namedXmlID[23].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * aboutwnd;
		 const wchar_t * btn_close;
		 const wchar_t * btn_eapiltype;
		 const wchar_t * btn_max;
		 const wchar_t * btn_min;
		 const wchar_t * btn_playlist;
		 const wchar_t * btn_record;
		 const wchar_t * btn_record_stop;
		 const wchar_t * btn_restore;
		 const wchar_t * btn_screen_full;
		 const wchar_t * btn_snapshot;
		 const wchar_t * btn_volume;
		 const wchar_t * btn_volume_zero;
		 const wchar_t * depotwnd;
		 const wchar_t * ffplaywnd;
		 const wchar_t * filename;
		 const wchar_t * lv_play_list;
		 const wchar_t * maintab;
		 const wchar_t * realplay_wnd;
		 const wchar_t * skinwnd;
		 const wchar_t * sliderbarpos;
		 const wchar_t * urlwnd;
		 const wchar_t * volumeSlider;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int aboutwnd	=	65548;
		const static int btn_close	=	65536;
		const static int btn_eapiltype	=	65554;
		const static int btn_max	=	65537;
		const static int btn_min	=	65539;
		const static int btn_playlist	=	65556;
		const static int btn_record	=	65550;
		const static int btn_record_stop	=	65551;
		const static int btn_restore	=	65538;
		const static int btn_screen_full	=	65555;
		const static int btn_snapshot	=	65552;
		const static int btn_volume	=	206;
		const static int btn_volume_zero	=	206;
		const static int depotwnd	=	65545;
		const static int ffplaywnd	=	65542;
		const static int filename	=	65544;
		const static int lv_play_list	=	65543;
		const static int maintab	=	65540;
		const static int realplay_wnd	=	65541;
		const static int skinwnd	=	65546;
		const static int sliderbarpos	=	65549;
		const static int urlwnd	=	65547;
		const static int volumeSlider	=	65553;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
