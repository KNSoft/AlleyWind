﻿#include "../AlleyWind.inl"

#define DEFINE_CONSTANT(Value, Description) { Value, L###Value, (PCWSTR)Description }

#pragma region Styles

// CS_*
static UI_VALUEEDITOR_CONSTANT CSConsts[] = {
    DEFINE_CONSTANT(CS_VREDRAW, NULL),
    DEFINE_CONSTANT(CS_HREDRAW, NULL),
    DEFINE_CONSTANT(CS_DBLCLKS, NULL),
    DEFINE_CONSTANT(CS_OWNDC, NULL),
    DEFINE_CONSTANT(CS_CLASSDC, NULL),
    DEFINE_CONSTANT(CS_PARENTDC, NULL),
    DEFINE_CONSTANT(CS_NOCLOSE, NULL),
    DEFINE_CONSTANT(CS_SAVEBITS, NULL),
    DEFINE_CONSTANT(CS_BYTEALIGNCLIENT, NULL),
    DEFINE_CONSTANT(CS_BYTEALIGNWINDOW, NULL),
    DEFINE_CONSTANT(CS_GLOBALCLASS, NULL),
    DEFINE_CONSTANT(CS_IME, NULL),
    DEFINE_CONSTANT(CS_DROPSHADOW, NULL),
};

// WS_*
static UI_VALUEEDITOR_CONSTANT WSConsts[] = {
    DEFINE_CONSTANT(WS_POPUP, NULL),
    DEFINE_CONSTANT(WS_CHILD, NULL),
    DEFINE_CONSTANT(WS_MINIMIZE, NULL),
    DEFINE_CONSTANT(WS_VISIBLE, NULL),
    DEFINE_CONSTANT(WS_DISABLED, NULL),
    DEFINE_CONSTANT(WS_CLIPSIBLINGS, NULL),
    DEFINE_CONSTANT(WS_CLIPCHILDREN, NULL),
    DEFINE_CONSTANT(WS_MAXIMIZE, NULL),
    DEFINE_CONSTANT(WS_BORDER, NULL),
    DEFINE_CONSTANT(WS_DLGFRAME, NULL),
    DEFINE_CONSTANT(WS_VSCROLL, NULL),
    DEFINE_CONSTANT(WS_HSCROLL, NULL),
    DEFINE_CONSTANT(WS_SYSMENU, NULL),
    DEFINE_CONSTANT(WS_THICKFRAME, NULL),
};

// WS_* for child window
static UI_VALUEEDITOR_CONSTANT WSChildConsts[] = {
    DEFINE_CONSTANT(WS_GROUP, NULL),
    DEFINE_CONSTANT(WS_TABSTOP, NULL),
};

// WS_* for popup window
static UI_VALUEEDITOR_CONSTANT WSPopupConsts[] = {
    DEFINE_CONSTANT(WS_MINIMIZEBOX, NULL),
    DEFINE_CONSTANT(WS_MAXIMIZEBOX, NULL),
};

// WS_EX_*
static UI_VALUEEDITOR_CONSTANT WSEXConsts[] = {
    DEFINE_CONSTANT(WS_EX_DLGMODALFRAME, NULL),
    DEFINE_CONSTANT(WS_EX_NOPARENTNOTIFY, NULL),
    DEFINE_CONSTANT(WS_EX_TOPMOST, NULL),
    DEFINE_CONSTANT(WS_EX_ACCEPTFILES, NULL),
    DEFINE_CONSTANT(WS_EX_TRANSPARENT, NULL),
    DEFINE_CONSTANT(WS_EX_MDICHILD, NULL),
    DEFINE_CONSTANT(WS_EX_TOOLWINDOW, NULL),
    DEFINE_CONSTANT(WS_EX_WINDOWEDGE, NULL),
    DEFINE_CONSTANT(WS_EX_CLIENTEDGE, NULL),
    DEFINE_CONSTANT(WS_EX_CONTEXTHELP, NULL),
    DEFINE_CONSTANT(WS_EX_RIGHT, NULL),
    DEFINE_CONSTANT(WS_EX_RTLREADING, NULL),
    DEFINE_CONSTANT(WS_EX_LEFTSCROLLBAR, NULL),
    DEFINE_CONSTANT(WS_EX_CONTROLPARENT, NULL),
    DEFINE_CONSTANT(WS_EX_STATICEDGE, NULL),
    DEFINE_CONSTANT(WS_EX_APPWINDOW, NULL),
    DEFINE_CONSTANT(WS_EX_LAYERED, NULL),
    DEFINE_CONSTANT(WS_EX_NOINHERITLAYOUT, NULL),
    DEFINE_CONSTANT(WS_EX_NOREDIRECTIONBITMAP, NULL),
    DEFINE_CONSTANT(WS_EX_LAYOUTRTL, NULL),
    DEFINE_CONSTANT(WS_EX_COMPOSITED, NULL),
    DEFINE_CONSTANT(WS_EX_NOACTIVATE, NULL),
};

// DS_* for dialog box
static UI_VALUEEDITOR_CONSTANT DSConsts[] = {
    DEFINE_CONSTANT(DS_ABSALIGN, NULL),
    DEFINE_CONSTANT(DS_SYSMODAL, NULL),
    DEFINE_CONSTANT(DS_LOCALEDIT, NULL),
    DEFINE_CONSTANT(DS_SETFONT, NULL),
    DEFINE_CONSTANT(DS_MODALFRAME, NULL),
    DEFINE_CONSTANT(DS_NOIDLEMSG, NULL),
    DEFINE_CONSTANT(DS_SETFOREGROUND, NULL),
    DEFINE_CONSTANT(DS_3DLOOK, NULL),
    DEFINE_CONSTANT(DS_FIXEDSYS, NULL),
    DEFINE_CONSTANT(DS_NOFAILCREATE, NULL),
    DEFINE_CONSTANT(DS_CONTROL, NULL),
    DEFINE_CONSTANT(DS_CENTER, NULL),
    DEFINE_CONSTANT(DS_CENTERMOUSE, NULL),
    DEFINE_CONSTANT(DS_CONTEXTHELP, NULL),
    { 0x8000L, L"DS_USEPIXELS", NULL }
};

// ACS_* for Animation Control
static UI_VALUEEDITOR_CONSTANT ACSConsts[] = {
    DEFINE_CONSTANT(ACS_CENTER, NULL),
    DEFINE_CONSTANT(ACS_TRANSPARENT, NULL),
    DEFINE_CONSTANT(ACS_AUTOPLAY, NULL),
    DEFINE_CONSTANT(ACS_TIMER, NULL),
};

// DTS_* for Date and Time Picker Control
static UI_VALUEEDITOR_CONSTANT DTSConsts[] = {
    DEFINE_CONSTANT(DTS_UPDOWN, NULL),
    DEFINE_CONSTANT(DTS_SHOWNONE, NULL),
    DEFINE_CONSTANT(DTS_SHORTDATEFORMAT, NULL),
    DEFINE_CONSTANT(DTS_LONGDATEFORMAT, NULL),
    DEFINE_CONSTANT(DTS_SHORTDATECENTURYFORMAT, NULL),
    DEFINE_CONSTANT(DTS_TIMEFORMAT, NULL),
    DEFINE_CONSTANT(DTS_APPCANPARSE, NULL),
    DEFINE_CONSTANT(DTS_RIGHTALIGN, NULL),
};

// MCS_* for Month Calendar Control
static UI_VALUEEDITOR_CONSTANT MCSConsts[] = {
    DEFINE_CONSTANT(MCS_DAYSTATE, NULL),
    DEFINE_CONSTANT(MCS_MULTISELECT, NULL),
    DEFINE_CONSTANT(MCS_WEEKNUMBERS, NULL),
    DEFINE_CONSTANT(MCS_NOTODAYCIRCLE, NULL),
    DEFINE_CONSTANT(MCS_NOTODAY, NULL),
    DEFINE_CONSTANT(MCS_NOTRAILINGDATES, NULL),
    DEFINE_CONSTANT(MCS_SHORTDAYSOFWEEK, NULL),
    DEFINE_CONSTANT(MCS_NOSELCHANGEONNAV, NULL),
};

// PBS_* for Progress Bar Control
static UI_VALUEEDITOR_CONSTANT PBSConsts[] = {
    DEFINE_CONSTANT(PBS_MARQUEE, NULL),
    DEFINE_CONSTANT(PBS_SMOOTH, NULL),
    DEFINE_CONSTANT(PBS_SMOOTHREVERSE, NULL),
    DEFINE_CONSTANT(PBS_VERTICAL, NULL),
};

// RBS_* for Rebar Control
static UI_VALUEEDITOR_CONSTANT RBSConsts[] = {
    DEFINE_CONSTANT(RBS_TOOLTIPS, NULL),
    DEFINE_CONSTANT(RBS_VARHEIGHT, NULL),
    DEFINE_CONSTANT(RBS_BANDBORDERS, NULL),
    DEFINE_CONSTANT(RBS_FIXEDORDER, NULL),
    DEFINE_CONSTANT(RBS_REGISTERDROP, NULL),
    DEFINE_CONSTANT(RBS_AUTOSIZE, NULL),
    DEFINE_CONSTANT(RBS_VERTICALGRIPPER, NULL),
    DEFINE_CONSTANT(RBS_DBLCLKTOGGLE, NULL),
};

// SBARS_* for Status Bar
static UI_VALUEEDITOR_CONSTANT SBARSConsts[] = {
    DEFINE_CONSTANT(SBARS_SIZEGRIP, NULL),
    DEFINE_CONSTANT(SBARS_TOOLTIPS, NULL),
};

// TBSTYLE_* for Status Bar
static UI_VALUEEDITOR_CONSTANT TBSTYLEConsts[] = {
    DEFINE_CONSTANT(TBSTYLE_BUTTON, NULL),
    DEFINE_CONSTANT(TBSTYLE_SEP, NULL),
    DEFINE_CONSTANT(TBSTYLE_CHECK, NULL),
    DEFINE_CONSTANT(TBSTYLE_GROUP, NULL),
    DEFINE_CONSTANT(TBSTYLE_DROPDOWN, NULL),
    DEFINE_CONSTANT(TBSTYLE_AUTOSIZE, NULL),
    DEFINE_CONSTANT(TBSTYLE_NOPREFIX, NULL),
    DEFINE_CONSTANT(TBSTYLE_TOOLTIPS, NULL),
    DEFINE_CONSTANT(TBSTYLE_WRAPABLE, NULL),
    DEFINE_CONSTANT(TBSTYLE_ALTDRAG, NULL),
    DEFINE_CONSTANT(TBSTYLE_FLAT, NULL),
    DEFINE_CONSTANT(TBSTYLE_LIST, NULL),
    DEFINE_CONSTANT(TBSTYLE_CUSTOMERASE, NULL),
    DEFINE_CONSTANT(TBSTYLE_REGISTERDROP, NULL),
    DEFINE_CONSTANT(TBSTYLE_TRANSPARENT, NULL),
    DEFINE_CONSTANT(BTNS_SHOWTEXT, NULL),
    DEFINE_CONSTANT(BTNS_WHOLEDROPDOWN, NULL),
};

// TTS_* for Tooltip
static UI_VALUEEDITOR_CONSTANT TTSConsts[] = {
    DEFINE_CONSTANT(TTS_ALWAYSTIP, NULL),
    DEFINE_CONSTANT(TTS_NOPREFIX, NULL),
    DEFINE_CONSTANT(TTS_NOANIMATE, NULL),
    DEFINE_CONSTANT(TTS_NOFADE, NULL),
    DEFINE_CONSTANT(TTS_BALLOON, NULL),
    DEFINE_CONSTANT(TTS_CLOSE, NULL),
    DEFINE_CONSTANT(TTS_USEVISUALSTYLE, NULL),
};

// TBS_* for Trackbar Control
static UI_VALUEEDITOR_CONSTANT TBSConsts[] = {
    DEFINE_CONSTANT(TBS_AUTOTICKS, NULL),
    DEFINE_CONSTANT(TBS_VERT, NULL),
    DEFINE_CONSTANT(TBS_HORZ, NULL),
    DEFINE_CONSTANT(TBS_TOP, NULL),
    DEFINE_CONSTANT(TBS_BOTTOM, NULL),
    DEFINE_CONSTANT(TBS_LEFT, NULL),
    DEFINE_CONSTANT(TBS_RIGHT, NULL),
    DEFINE_CONSTANT(TBS_BOTH, NULL),
    DEFINE_CONSTANT(TBS_NOTICKS, NULL),
    DEFINE_CONSTANT(TBS_ENABLESELRANGE, NULL),
    DEFINE_CONSTANT(TBS_FIXEDLENGTH, NULL),
    DEFINE_CONSTANT(TBS_NOTHUMB, NULL),
    DEFINE_CONSTANT(TBS_TOOLTIPS, NULL),
    DEFINE_CONSTANT(TBS_REVERSED, NULL),
    DEFINE_CONSTANT(TBS_DOWNISLEFT, NULL),
    DEFINE_CONSTANT(TBS_NOTIFYBEFOREMOVE, NULL),
    DEFINE_CONSTANT(TBS_TRANSPARENTBKGND, NULL),
};

// UDS_* for Up-Down Control
static UI_VALUEEDITOR_CONSTANT UDSConsts[] = {
    DEFINE_CONSTANT(UDS_WRAP, NULL),
    DEFINE_CONSTANT(UDS_SETBUDDYINT, NULL),
    DEFINE_CONSTANT(UDS_ALIGNRIGHT, NULL),
    DEFINE_CONSTANT(UDS_ALIGNLEFT, NULL),
    DEFINE_CONSTANT(UDS_AUTOBUDDY, NULL),
    DEFINE_CONSTANT(UDS_ARROWKEYS, NULL),
    DEFINE_CONSTANT(UDS_HORZ, NULL),
    DEFINE_CONSTANT(UDS_NOTHOUSANDS, NULL),
    DEFINE_CONSTANT(UDS_HOTTRACK, NULL),
};

// BS_* for Button Control
static UI_VALUEEDITOR_CONSTANT BSConsts[] = {
    DEFINE_CONSTANT(BS_OWNERDRAW, NULL),
    DEFINE_CONSTANT(BS_PUSHBOX, NULL),
    DEFINE_CONSTANT(BS_AUTORADIOBUTTON, NULL),
    DEFINE_CONSTANT(BS_USERBUTTON, NULL),
    DEFINE_CONSTANT(BS_GROUPBOX, NULL),
    DEFINE_CONSTANT(BS_AUTO3STATE, NULL),
    DEFINE_CONSTANT(BS_3STATE, NULL),
    DEFINE_CONSTANT(BS_RADIOBUTTON, NULL),
    DEFINE_CONSTANT(BS_AUTOCHECKBOX, NULL),
    DEFINE_CONSTANT(BS_CHECKBOX, NULL),
    DEFINE_CONSTANT(BS_DEFPUSHBUTTON, NULL),
    DEFINE_CONSTANT(BS_LEFTTEXT, NULL),
    DEFINE_CONSTANT(BS_ICON, NULL),
    DEFINE_CONSTANT(BS_BITMAP, NULL),
    DEFINE_CONSTANT(BS_LEFT, NULL),
    DEFINE_CONSTANT(BS_RIGHT, NULL),
    DEFINE_CONSTANT(BS_CENTER, NULL),
    DEFINE_CONSTANT(BS_TOP, NULL),
    DEFINE_CONSTANT(BS_BOTTOM, NULL),
    DEFINE_CONSTANT(BS_VCENTER, NULL),
    DEFINE_CONSTANT(BS_PUSHLIKE, NULL),
    DEFINE_CONSTANT(BS_MULTILINE, NULL),
    DEFINE_CONSTANT(BS_NOTIFY, NULL),
    DEFINE_CONSTANT(BS_FLAT, NULL),
};

// CBS_* for Combo Box
static UI_VALUEEDITOR_CONSTANT CBSConsts[] = {
    DEFINE_CONSTANT(CBS_DROPDOWNLIST, NULL),
    DEFINE_CONSTANT(CBS_DROPDOWN, NULL),
    DEFINE_CONSTANT(CBS_SIMPLE, NULL),
    DEFINE_CONSTANT(CBS_OWNERDRAWFIXED, NULL),
    DEFINE_CONSTANT(CBS_OWNERDRAWVARIABLE, NULL),
    DEFINE_CONSTANT(CBS_AUTOHSCROLL, NULL),
    DEFINE_CONSTANT(CBS_OEMCONVERT, NULL),
    DEFINE_CONSTANT(CBS_SORT, NULL),
    DEFINE_CONSTANT(CBS_HASSTRINGS, NULL),
    DEFINE_CONSTANT(CBS_NOINTEGRALHEIGHT, NULL),
    DEFINE_CONSTANT(CBS_DISABLENOSCROLL, NULL),
    DEFINE_CONSTANT(CBS_UPPERCASE, NULL),
    DEFINE_CONSTANT(CBS_LOWERCASE, NULL),
};

// CBS_* for ComboBoxEx Control
static UI_VALUEEDITOR_CONSTANT CBESConsts[] = {
    DEFINE_CONSTANT(CBS_DROPDOWNLIST, NULL),
    DEFINE_CONSTANT(CBS_DROPDOWN, NULL),
    DEFINE_CONSTANT(CBS_SIMPLE, NULL),
};

// ES_* for Edit Control
static UI_VALUEEDITOR_CONSTANT ESConsts[] = {
    DEFINE_CONSTANT(ES_CENTER, NULL),
    DEFINE_CONSTANT(ES_RIGHT, NULL),
    DEFINE_CONSTANT(ES_MULTILINE, NULL),
    DEFINE_CONSTANT(ES_UPPERCASE, NULL),
    DEFINE_CONSTANT(ES_LOWERCASE, NULL),
    DEFINE_CONSTANT(ES_PASSWORD, NULL),
    DEFINE_CONSTANT(ES_AUTOVSCROLL, NULL),
    DEFINE_CONSTANT(ES_AUTOHSCROLL, NULL),
    DEFINE_CONSTANT(ES_NOHIDESEL, NULL),
    DEFINE_CONSTANT(ES_OEMCONVERT, NULL),
    DEFINE_CONSTANT(ES_READONLY, NULL),
    DEFINE_CONSTANT(ES_WANTRETURN, NULL),
    DEFINE_CONSTANT(ES_NUMBER, NULL),
};

// HDS_* for Header Control
static UI_VALUEEDITOR_CONSTANT HDSConsts[] = {
    DEFINE_CONSTANT(HDS_BUTTONS, NULL),
    DEFINE_CONSTANT(HDS_HOTTRACK, NULL),
    DEFINE_CONSTANT(HDS_HIDDEN, NULL),
    DEFINE_CONSTANT(HDS_DRAGDROP, NULL),
    DEFINE_CONSTANT(HDS_FULLDRAG, NULL),
    DEFINE_CONSTANT(HDS_FILTERBAR, NULL),
    DEFINE_CONSTANT(HDS_FLAT, NULL),
    DEFINE_CONSTANT(HDS_CHECKBOXES, NULL),
    DEFINE_CONSTANT(HDS_NOSIZING, NULL),
    DEFINE_CONSTANT(HDS_OVERFLOW, NULL),
};

// LBS_* for List Box
static UI_VALUEEDITOR_CONSTANT LBSConsts[] = {
    DEFINE_CONSTANT(LBS_NOTIFY, NULL),
    DEFINE_CONSTANT(LBS_SORT, NULL),
    DEFINE_CONSTANT(LBS_NOREDRAW, NULL),
    DEFINE_CONSTANT(LBS_MULTIPLESEL, NULL),
    DEFINE_CONSTANT(LBS_OWNERDRAWFIXED, NULL),
    DEFINE_CONSTANT(LBS_OWNERDRAWVARIABLE, NULL),
    DEFINE_CONSTANT(LBS_HASSTRINGS, NULL),
    DEFINE_CONSTANT(LBS_USETABSTOPS, NULL),
    DEFINE_CONSTANT(LBS_NOINTEGRALHEIGHT, NULL),
    DEFINE_CONSTANT(LBS_MULTICOLUMN, NULL),
    DEFINE_CONSTANT(LBS_WANTKEYBOARDINPUT, NULL),
    DEFINE_CONSTANT(LBS_EXTENDEDSEL, NULL),
    DEFINE_CONSTANT(LBS_DISABLENOSCROLL, NULL),
    DEFINE_CONSTANT(LBS_NODATA, NULL),
    DEFINE_CONSTANT(LBS_NOSEL, NULL),
    DEFINE_CONSTANT(LBS_COMBOBOX, NULL),
};

// LWS_* for SysLink Control
static UI_VALUEEDITOR_CONSTANT LWSConsts[] = {
    DEFINE_CONSTANT(LWS_TRANSPARENT, NULL),
    DEFINE_CONSTANT(LWS_IGNORERETURN, NULL),
    DEFINE_CONSTANT(LWS_NOPREFIX, NULL),
    DEFINE_CONSTANT(LWS_USEVISUALSTYLE, NULL),
    DEFINE_CONSTANT(LWS_USECUSTOMTEXT, NULL),
    DEFINE_CONSTANT(LWS_RIGHT, NULL),
};

// LVS_* for List-View
static UI_VALUEEDITOR_CONSTANT LVSConsts[] = {
    DEFINE_CONSTANT(LVS_LIST, NULL),
    DEFINE_CONSTANT(LVS_SMALLICON, NULL),
    DEFINE_CONSTANT(LVS_REPORT, NULL),
    DEFINE_CONSTANT(LVS_SINGLESEL, NULL),
    DEFINE_CONSTANT(LVS_SHOWSELALWAYS, NULL),
    DEFINE_CONSTANT(LVS_SORTASCENDING, NULL),
    DEFINE_CONSTANT(LVS_SORTDESCENDING, NULL),
    DEFINE_CONSTANT(LVS_SHAREIMAGELISTS, NULL),
    DEFINE_CONSTANT(LVS_NOLABELWRAP, NULL),
    DEFINE_CONSTANT(LVS_AUTOARRANGE, NULL),
    DEFINE_CONSTANT(LVS_EDITLABELS, NULL),
    DEFINE_CONSTANT(LVS_OWNERDATA, NULL),
    DEFINE_CONSTANT(LVS_NOSCROLL, NULL),
    DEFINE_CONSTANT(LVS_ALIGNLEFT, NULL),
    DEFINE_CONSTANT(LVS_NOSCROLL, NULL),
    DEFINE_CONSTANT(LVS_OWNERDRAWFIXED, NULL),
    DEFINE_CONSTANT(LVS_NOCOLUMNHEADER, NULL),
    DEFINE_CONSTANT(LVS_NOSORTHEADER, NULL),
};

// PGS_* for Pager Control
static UI_VALUEEDITOR_CONSTANT PGSConsts[] = {
    DEFINE_CONSTANT(PGS_HORZ, NULL),
    DEFINE_CONSTANT(PGS_AUTOSCROLL, NULL),
    DEFINE_CONSTANT(PGS_DRAGNDROP, NULL),
};

// SBS_* for Scroll Bar Control
static UI_VALUEEDITOR_CONSTANT SBSConsts[] = {
    DEFINE_CONSTANT(SBS_VERT, NULL),
    DEFINE_CONSTANT(SBS_TOPALIGN, NULL),
    DEFINE_CONSTANT(SBS_LEFTALIGN, NULL),
    DEFINE_CONSTANT(SBS_BOTTOMALIGN, NULL),
    DEFINE_CONSTANT(SBS_RIGHTALIGN, NULL),
    DEFINE_CONSTANT(SBS_SIZEBOXTOPLEFTALIGN, NULL),
    DEFINE_CONSTANT(SBS_SIZEBOXBOTTOMRIGHTALIGN, NULL),
    DEFINE_CONSTANT(SBS_SIZEBOX, NULL),
    DEFINE_CONSTANT(SBS_SIZEGRIP, NULL),
};

// SS_* for Static Control
static UI_VALUEEDITOR_CONSTANT SSConsts[] = {
    DEFINE_CONSTANT(SS_ETCHEDFRAME, NULL),
    DEFINE_CONSTANT(SS_ETCHEDVERT, NULL),
    DEFINE_CONSTANT(SS_ETCHEDHORZ, NULL),
    DEFINE_CONSTANT(SS_ENHMETAFILE, NULL),
    DEFINE_CONSTANT(SS_BITMAP, NULL),
    DEFINE_CONSTANT(SS_OWNERDRAW, NULL),
    DEFINE_CONSTANT(SS_LEFTNOWORDWRAP, NULL),
    DEFINE_CONSTANT(SS_SIMPLE, NULL),
    DEFINE_CONSTANT(SS_USERITEM, NULL),
    DEFINE_CONSTANT(SS_WHITEFRAME, NULL),
    DEFINE_CONSTANT(SS_GRAYFRAME, NULL),
    DEFINE_CONSTANT(SS_BLACKFRAME, NULL),
    DEFINE_CONSTANT(SS_WHITERECT, NULL),
    DEFINE_CONSTANT(SS_GRAYRECT, NULL),
    DEFINE_CONSTANT(SS_BLACKRECT, NULL),
    DEFINE_CONSTANT(SS_ICON, NULL),
    DEFINE_CONSTANT(SS_RIGHT, NULL),
    DEFINE_CONSTANT(SS_CENTER, NULL),
    DEFINE_CONSTANT(SS_REALSIZECONTROL, NULL),
    DEFINE_CONSTANT(SS_NOPREFIX, NULL),
    DEFINE_CONSTANT(SS_NOTIFY, NULL),
    DEFINE_CONSTANT(SS_CENTERIMAGE, NULL),
    DEFINE_CONSTANT(SS_RIGHTJUST, NULL),
    DEFINE_CONSTANT(SS_REALSIZEIMAGE, NULL),
    DEFINE_CONSTANT(SS_SUNKEN, NULL),
    DEFINE_CONSTANT(SS_EDITCONTROL, NULL),
    DEFINE_CONSTANT(SS_ENDELLIPSIS, NULL),
    DEFINE_CONSTANT(SS_PATHELLIPSIS, NULL),
    DEFINE_CONSTANT(SS_WORDELLIPSIS, NULL),
};

// TCS_* for Tab Control
static UI_VALUEEDITOR_CONSTANT TCSConsts[] = {
    DEFINE_CONSTANT(TCS_SCROLLOPPOSITE, NULL),
    DEFINE_CONSTANT(TCS_BOTTOM, NULL),
    DEFINE_CONSTANT(TCS_MULTISELECT, NULL),
    DEFINE_CONSTANT(TCS_FLATBUTTONS, NULL),
    DEFINE_CONSTANT(TCS_FORCEICONLEFT, NULL),
    DEFINE_CONSTANT(TCS_FORCELABELLEFT, NULL),
    DEFINE_CONSTANT(TCS_HOTTRACK, NULL),
    DEFINE_CONSTANT(TCS_VERTICAL, NULL),
    DEFINE_CONSTANT(TCS_BUTTONS, NULL),
    DEFINE_CONSTANT(TCS_SINGLELINE, NULL),
    DEFINE_CONSTANT(TCS_MULTILINE, NULL),
    DEFINE_CONSTANT(TCS_FIXEDWIDTH, NULL),
    DEFINE_CONSTANT(TCS_RAGGEDRIGHT, NULL),
    DEFINE_CONSTANT(TCS_FOCUSONBUTTONDOWN, NULL),
    DEFINE_CONSTANT(TCS_OWNERDRAWFIXED, NULL),
    DEFINE_CONSTANT(TCS_TOOLTIPS, NULL),
    DEFINE_CONSTANT(TCS_FOCUSNEVER, NULL),
};

// TVS_* for Tree-View Control
static UI_VALUEEDITOR_CONSTANT TVSConsts[] = {
    DEFINE_CONSTANT(TVS_HASBUTTONS, NULL),
    DEFINE_CONSTANT(TVS_HASLINES, NULL),
    DEFINE_CONSTANT(TVS_LINESATROOT, NULL),
    DEFINE_CONSTANT(TVS_EDITLABELS, NULL),
    DEFINE_CONSTANT(TVS_DISABLEDRAGDROP, NULL),
    DEFINE_CONSTANT(TVS_SHOWSELALWAYS, NULL),
    DEFINE_CONSTANT(TVS_RTLREADING, NULL),
    DEFINE_CONSTANT(TVS_NOTOOLTIPS, NULL),
    DEFINE_CONSTANT(TVS_CHECKBOXES, NULL),
    DEFINE_CONSTANT(TVS_TRACKSELECT, NULL),
    DEFINE_CONSTANT(TVS_SINGLEEXPAND, NULL),
    DEFINE_CONSTANT(TVS_INFOTIP, NULL),
    DEFINE_CONSTANT(TVS_FULLROWSELECT, NULL),
    DEFINE_CONSTANT(TVS_NOSCROLL, NULL),
    DEFINE_CONSTANT(TVS_NONEVENHEIGHT, NULL),
    DEFINE_CONSTANT(TVS_NOHSCROLL, NULL),
};

// MDIS_* for MDI Client
static UI_VALUEEDITOR_CONSTANT MDISConsts[] = {
    DEFINE_CONSTANT(MDIS_ALLCHILDSTYLES, NULL),
};

#pragma endregion

#pragma region Classes

typedef struct _AW_SYSCLASS_INFO {
    PCWSTR ClassName;
    PCWSTR DisplayName;
    PUI_VALUEEDITOR_CONSTANT StyleConsts;
    ULONG StyleConstsCount;
} AW_SYSCLASS_INFO, * PAW_SYSCLASS_INFO;

#define AW_DATABASE_SYSCTLLIB_COMMCTLINDEX 2
#define DEFINE_CLASS_INFO_0(ClassName, DisplayName) { ClassName, (PCWSTR)Precomp4C_I18N_All_##DisplayName, NULL, 0 }
#define DEFINE_CLASS_INFO_1(ClassName, DisplayName, StyleConstants) { ClassName, (PCWSTR)Precomp4C_I18N_All_##DisplayName, StyleConstants, ARRAYSIZE(StyleConstants) }

static AW_SYSCLASS_INFO g_astSysClassInfo[] = {

    // Top-level
    DEFINE_CLASS_INFO_0(L"#32769", Desktop),
    DEFINE_CLASS_INFO_1(WC_DIALOG, Dialog, DSConsts),

    // Common Controls
    DEFINE_CLASS_INFO_1(ANIMATE_CLASSW, Animation, ACSConsts),
    DEFINE_CLASS_INFO_1(DATETIMEPICK_CLASSW, DateTimePicker, DTSConsts),
    DEFINE_CLASS_INFO_0(HOTKEY_CLASSW, HotKey),
    DEFINE_CLASS_INFO_1(MONTHCAL_CLASSW, Calendar, MCSConsts),
    DEFINE_CLASS_INFO_1(PROGRESS_CLASSW, ProgressBar, PBSConsts),
    DEFINE_CLASS_INFO_1(REBARCLASSNAMEW, ReBar, RBSConsts),
    DEFINE_CLASS_INFO_1(STATUSCLASSNAMEW, StatusBar, SBARSConsts),
    DEFINE_CLASS_INFO_1(TOOLBARCLASSNAMEW, ToolBar, TBSConsts),
    DEFINE_CLASS_INFO_1(TOOLTIPS_CLASSW, ToolTips, TTSConsts),
    DEFINE_CLASS_INFO_1(TRACKBAR_CLASSW, SliderBar, TBSConsts),
    DEFINE_CLASS_INFO_1(UPDOWN_CLASSW, UpDownControl, UDSConsts),
    DEFINE_CLASS_INFO_1(WC_BUTTONW, Button, BSConsts),
    DEFINE_CLASS_INFO_1(WC_COMBOBOXW, ComboBox, CBSConsts),
    DEFINE_CLASS_INFO_1(WC_COMBOBOXEXW, ExtendedComboBox, CBESConsts),
    DEFINE_CLASS_INFO_1(WC_EDITW, EditControl, ESConsts),
    DEFINE_CLASS_INFO_1(WC_HEADERW, HeaderControl, HDSConsts),
    DEFINE_CLASS_INFO_1(WC_LISTBOXW, ListBox, LBSConsts),
    DEFINE_CLASS_INFO_0(WC_IPADDRESSW, IPAddressControl),
    DEFINE_CLASS_INFO_1(WC_LINK, Hyperlink, LWSConsts),
    DEFINE_CLASS_INFO_1(WC_LISTVIEWW, ListView, LVSConsts),
    DEFINE_CLASS_INFO_0(WC_NATIVEFONTCTLW, NativeFont),
    DEFINE_CLASS_INFO_1(WC_PAGESCROLLERW, PageScroller, PGSConsts),
    DEFINE_CLASS_INFO_1(WC_SCROLLBARW, ScrollBar, SBSConsts),
    DEFINE_CLASS_INFO_1(WC_STATICW, StaticControl, SSConsts),
    DEFINE_CLASS_INFO_1(WC_TABCONTROLW, TabControl, TCSConsts),
    DEFINE_CLASS_INFO_1(WC_TREEVIEWW, TreeView, TVSConsts),

    // Additional
    DEFINE_CLASS_INFO_1(L"MDIClient", MDIClient, MDISConsts),
};

#pragma endregion

#pragma region Functions

VOID
AW_InitClassDatabase(VOID)
{
    AW_InitI18NArrayEx(g_astSysClassInfo,
                       sizeof(g_astSysClassInfo[0]),
                       ARRAYSIZE(g_astSysClassInfo),
                       UFIELD_OFFSET(TYPE_OF(g_astSysClassInfo[0]), DisplayName));
}

static
PAW_SYSCLASS_INFO
FindSysClassInfoByName(
    _In_ PCWSTR ClassName)
{
    UINT i;
    WCHAR szClassOrdName[7]; // "#65535"
    PCWSTR pszName;

    for (i = 0; i < ARRAYSIZE(g_astSysClassInfo); i++)
    {
        if ((ULONG_PTR)g_astSysClassInfo[i].ClassName >= MAXINTATOM)
        {
            pszName = g_astSysClassInfo[i].ClassName;
        } else
        {
            if (Str_PrintfW(szClassOrdName, L"#%hu", LOWORD(g_astSysClassInfo[i].ClassName)) <= 0)
            {
                return NULL;
            }
            pszName = szClassOrdName;
        }
        if (Str_EqualW(pszName, ClassName))
        {
            return &g_astSysClassInfo[i];
        }
    }

    return NULL;
}

_Ret_maybenull_z_
PCWSTR
AW_GetSysClassDisplayName(
    _In_ PCWSTR ClassName)
{
    PAW_SYSCLASS_INFO Info = FindSysClassInfoByName(ClassName);
    return Info == NULL ? NULL : Info->DisplayName;
}

#pragma endregion
