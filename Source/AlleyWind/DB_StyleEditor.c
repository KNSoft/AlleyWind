#include "AlleyWind.h"

// I18N strings for Dlg_ValueEditor
PCWSTR DB_lpszDVE[7];
PCWSTR DB_lpszDRE[9];

// ********** Data **********

// CS_*
DLG_VALUEEDITOR_CONST stCSDVEConsts[] = {
    { CS_VREDRAW, L"CS_VREDRAW", NULL },
    { CS_HREDRAW, L"CS_HREDRAW", NULL },
    { CS_DBLCLKS, L"CS_DBLCLKS", NULL },
    { CS_OWNDC, L"CS_OWNDC", NULL },
    { CS_CLASSDC, L"CS_CLASSDC", NULL },
    { CS_PARENTDC, L"CS_PARENTDC", NULL },
    { CS_NOCLOSE, L"CS_NOCLOSE", NULL },
    { CS_SAVEBITS, L"CS_SAVEBITS", NULL },
    { CS_BYTEALIGNCLIENT, L"CS_BYTEALIGNCLIENT", NULL },
    { CS_BYTEALIGNWINDOW, L"CS_BYTEALIGNWINDOW", NULL },
    { CS_GLOBALCLASS, L"CS_GLOBALCLASS", NULL },
    { CS_IME, L"CS_IME", NULL },
    { CS_DROPSHADOW, L"CS_DROPSHADOW", NULL },
    { CS_VREDRAW, L"CS_VREDRAW", NULL }
};

// WS_*
DLG_VALUEEDITOR_CONST stWSDVEConsts[] = {
    { WS_POPUP, L"WS_POPUP", NULL },
    { WS_CHILD, L"WS_CHILD", NULL },
    { WS_MINIMIZE, L"WS_MINIMIZE", NULL },
    { WS_VISIBLE, L"WS_VISIBLE", NULL },
    { WS_DISABLED, L"WS_DISABLED", NULL },
    { WS_CLIPSIBLINGS, L"WS_CLIPSIBLINGS", NULL },
    { WS_CLIPCHILDREN, L"WS_CLIPCHILDREN", NULL },
    { WS_MAXIMIZE, L"WS_MAXIMIZE", NULL },
    { WS_BORDER, L"WS_BORDER", NULL },
    { WS_DLGFRAME, L"WS_DLGFRAME", NULL },
    { WS_VSCROLL, L"WS_VSCROLL", NULL },
    { WS_HSCROLL, L"WS_HSCROLL", NULL },
    { WS_SYSMENU, L"WS_SYSMENU", NULL },
    { WS_THICKFRAME, L"WS_THICKFRAME", NULL }
};
// WS_* for child window
DLG_VALUEEDITOR_CONST stWSCDVEConsts[] = {
    { WS_GROUP, L"WS_GROUP", NULL },
    { WS_TABSTOP, L"WS_TABSTOP", NULL }
};
// WS_* for popup window
DLG_VALUEEDITOR_CONST stWSPDVEConsts[] = {
    { WS_MINIMIZEBOX, L"WS_MINIMIZEBOX", NULL },
    { WS_MAXIMIZEBOX, L"WS_MAXIMIZEBOX", NULL }
};

// WS_EX_*
DLG_VALUEEDITOR_CONST stWSEXDVEConsts[] = {
    { WS_EX_DLGMODALFRAME, L"WS_EX_DLGMODALFRAME", NULL },
    { WS_EX_NOPARENTNOTIFY, L"WS_EX_NOPARENTNOTIFY", NULL },
    { WS_EX_TOPMOST, L"WS_EX_TOPMOST", NULL },
    { WS_EX_ACCEPTFILES, L"WS_EX_ACCEPTFILES", NULL },
    { WS_EX_TRANSPARENT, L"WS_EX_TRANSPARENT", NULL },
    { WS_EX_MDICHILD, L"WS_EX_MDICHILD", NULL },
    { WS_EX_TOOLWINDOW, L"WS_EX_TOOLWINDOW", NULL },
    { WS_EX_WINDOWEDGE, L"WS_EX_WINDOWEDGE", NULL },
    { WS_EX_CLIENTEDGE, L"WS_EX_CLIENTEDGE", NULL },
    { WS_EX_CONTEXTHELP, L"WS_EX_CONTEXTHELP", NULL },
    { WS_EX_RIGHT, L"WS_EX_RIGHT", NULL },
    { WS_EX_RTLREADING, L"WS_EX_RTLREADING", NULL },
    { WS_EX_LEFTSCROLLBAR, L"WS_EX_LEFTSCROLLBAR", NULL },
    { WS_EX_CONTROLPARENT, L"WS_EX_CONTROLPARENT", NULL },
    { WS_EX_STATICEDGE, L"WS_EX_STATICEDGE", NULL },
    { WS_EX_APPWINDOW, L"WS_EX_APPWINDOW", NULL },
    { WS_EX_LAYERED, L"WS_EX_LAYERED", NULL },
    { WS_EX_NOINHERITLAYOUT, L"WS_EX_NOINHERITLAYOUT", NULL },
    { WS_EX_NOREDIRECTIONBITMAP, L"WS_EX_NOREDIRECTIONBITMAP", NULL },
    { WS_EX_LAYOUTRTL, L"WS_EX_LAYOUTRTL", NULL },
    { WS_EX_COMPOSITED, L"WS_EX_COMPOSITED", NULL },
    { WS_EX_NOACTIVATE, L"WS_EX_NOACTIVATE", NULL }
};

// DS_* for dialog box
DLG_VALUEEDITOR_CONST stDSDVEConsts[] = {
    { DS_ABSALIGN, L"DS_ABSALIGN", NULL },
    { DS_SYSMODAL, L"DS_SYSMODAL", NULL },
    { DS_LOCALEDIT, L"DS_LOCALEDIT", NULL },
    { DS_SETFONT, L"DS_SETFONT", NULL },
    { DS_MODALFRAME, L"DS_MODALFRAME", NULL },
    { DS_NOIDLEMSG, L"DS_NOIDLEMSG", NULL },
    { DS_SETFOREGROUND, L"DS_SETFOREGROUND", NULL },
    { DS_3DLOOK, L"DS_3DLOOK", NULL },
    { DS_FIXEDSYS, L"DS_FIXEDSYS", NULL },
    { DS_NOFAILCREATE, L"DS_NOFAILCREATE", NULL },
    { DS_CONTROL, L"DS_CONTROL", NULL },
    { DS_CENTER, L"DS_CENTER", NULL },
    { DS_CENTERMOUSE, L"DS_CENTERMOUSE", NULL },
    { DS_CONTEXTHELP, L"DS_CONTEXTHELP", NULL },
    { 0x8000L, L"DS_USEPIXELS", NULL }
};

// ACS_* for Animation Control
DLG_VALUEEDITOR_CONST stACSDVEConsts[] = {
    { ACS_CENTER, L"ACS_CENTER", NULL },
    { ACS_TRANSPARENT, L"ACS_TRANSPARENT", NULL },
    { ACS_AUTOPLAY, L"ACS_AUTOPLAY", NULL },
    { ACS_TIMER, L"ACS_TIMER", NULL }
};

// DTS_* for Date and Time Picker Control
DLG_VALUEEDITOR_CONST stDTSDVEConsts[] = {
    { DTS_UPDOWN, L"DTS_UPDOWN", NULL },
    { DTS_SHOWNONE, L"DTS_SHOWNONE", NULL },
    { DTS_SHORTDATEFORMAT, L"DTS_SHORTDATEFORMAT", NULL },
    { DTS_LONGDATEFORMAT, L"DTS_LONGDATEFORMAT", NULL },
    { DTS_SHORTDATECENTURYFORMAT, L"DTS_SHORTDATECENTURYFORMAT", NULL },
    { DTS_TIMEFORMAT, L"DTS_TIMEFORMAT", NULL },
    { DTS_APPCANPARSE, L"DTS_APPCANPARSE", NULL },
    { DTS_RIGHTALIGN, L"DTS_RIGHTALIGN", NULL }
};

// MCS_* for Month Calendar Control
DLG_VALUEEDITOR_CONST stMCSDVEConsts[] = {
    { MCS_DAYSTATE, L"MCS_DAYSTATE", NULL },
    { MCS_MULTISELECT, L"MCS_MULTISELECT", NULL },
    { MCS_WEEKNUMBERS, L"MCS_WEEKNUMBERS", NULL },
    { MCS_NOTODAYCIRCLE, L"MCS_NOTODAYCIRCLE", NULL },
    { MCS_NOTODAY, L"MCS_NOTODAY", NULL },
    { MCS_NOTRAILINGDATES, L"MCS_NOTRAILINGDATES", NULL },
    { MCS_SHORTDAYSOFWEEK, L"MCS_SHORTDAYSOFWEEK", NULL },
    { MCS_NOSELCHANGEONNAV, L"MCS_NOSELCHANGEONNAV", NULL }
};

// PBS_* for Progress Bar Control
DLG_VALUEEDITOR_CONST stPBSDVEConsts[] = {
    { PBS_MARQUEE, L"PBS_MARQUEE", NULL },
    { PBS_SMOOTH, L"PBS_SMOOTH", NULL },
    { PBS_SMOOTHREVERSE, L"PBS_SMOOTHREVERSE", NULL },
    { PBS_VERTICAL, L"PBS_VERTICAL", NULL }
};

// RBS_* for Rebar Control
DLG_VALUEEDITOR_CONST stRBSDVEConsts[] = {
    { RBS_TOOLTIPS, L"RBS_TOOLTIPS", NULL },
    { RBS_VARHEIGHT, L"RBS_VARHEIGHT", NULL },
    { RBS_BANDBORDERS, L"RBS_BANDBORDERS", NULL },
    { RBS_FIXEDORDER, L"RBS_FIXEDORDER", NULL },
    { RBS_REGISTERDROP, L"RBS_REGISTERDROP", NULL },
    { RBS_AUTOSIZE, L"RBS_AUTOSIZE", NULL },
    { RBS_VERTICALGRIPPER, L"RBS_VERTICALGRIPPER", NULL },
    { RBS_DBLCLKTOGGLE, L"RBS_DBLCLKTOGGLE", NULL }
};

// SBARS_* for Status Bar
DLG_VALUEEDITOR_CONST stSBARSDVEConsts[] = {
    { SBARS_SIZEGRIP, L"SBARS_SIZEGRIP", NULL },
    { SBARS_TOOLTIPS, L"SBARS_TOOLTIPS", NULL }
};

// TBSTYLE_* for Status Bar
DLG_VALUEEDITOR_CONST stTBSTYLEDVEConsts[] = {
    { TBSTYLE_BUTTON, L"TBSTYLE_BUTTON", NULL },
    { TBSTYLE_SEP, L"TBSTYLE_SEP", NULL },
    { TBSTYLE_CHECK, L"TBSTYLE_CHECK", NULL },
    { TBSTYLE_GROUP, L"TBSTYLE_GROUP", NULL },
    { TBSTYLE_DROPDOWN, L"TBSTYLE_DROPDOWN", NULL },
    { TBSTYLE_AUTOSIZE, L"TBSTYLE_AUTOSIZE", NULL },
    { TBSTYLE_NOPREFIX, L"TBSTYLE_NOPREFIX", NULL },
    { TBSTYLE_TOOLTIPS, L"TBSTYLE_TOOLTIPS", NULL },
    { TBSTYLE_WRAPABLE, L"TBSTYLE_WRAPABLE", NULL },
    { TBSTYLE_ALTDRAG, L"TBSTYLE_ALTDRAG", NULL },
    { TBSTYLE_FLAT, L"TBSTYLE_FLAT", NULL },
    { TBSTYLE_LIST, L"TBSTYLE_LIST", NULL },
    { TBSTYLE_CUSTOMERASE, L"TBSTYLE_CUSTOMERASE", NULL },
    { TBSTYLE_REGISTERDROP, L"TBSTYLE_REGISTERDROP", NULL },
    { TBSTYLE_TRANSPARENT, L"TBSTYLE_TRANSPARENT", NULL },
    { BTNS_SHOWTEXT, L"BTNS_SHOWTEXT", NULL },
    { BTNS_WHOLEDROPDOWN, L"BTNS_WHOLEDROPDOWN", NULL }
};

// TTS_* for Tooltip
DLG_VALUEEDITOR_CONST stTTSDVEConsts[] = {
    { TTS_ALWAYSTIP, L"TTS_ALWAYSTIP", NULL },
    { TTS_NOPREFIX, L"TTS_NOPREFIX", NULL },
    { TTS_NOANIMATE, L"TTS_NOANIMATE", NULL },
    { TTS_NOFADE, L"TTS_NOFADE", NULL },
    { TTS_BALLOON, L"TTS_BALLOON", NULL },
    { TTS_CLOSE, L"TTS_CLOSE", NULL },
    { TTS_USEVISUALSTYLE, L"TTS_USEVISUALSTYLE", NULL }
};

// TBS_* for Trackbar Control
DLG_VALUEEDITOR_CONST stTBSDVEConsts[] = {
    { TBS_AUTOTICKS, L"TBS_AUTOTICKS", NULL },
    { TBS_VERT, L"TBS_VERT", NULL },
    { TBS_HORZ, L"TBS_HORZ", NULL },
    { TBS_TOP, L"TBS_TOP", NULL },
    { TBS_BOTTOM, L"TBS_BOTTOM", NULL },
    { TBS_LEFT, L"TBS_LEFT", NULL },
    { TBS_RIGHT, L"TBS_RIGHT", NULL },
    { TBS_BOTH, L"TBS_BOTH", NULL },
    { TBS_NOTICKS, L"TBS_NOTICKS", NULL },
    { TBS_ENABLESELRANGE, L"TBS_ENABLESELRANGE", NULL },
    { TBS_FIXEDLENGTH, L"TBS_FIXEDLENGTH", NULL },
    { TBS_NOTHUMB, L"TBS_NOTHUMB", NULL },
    { TBS_TOOLTIPS, L"TBS_TOOLTIPS", NULL },
    { TBS_REVERSED, L"TBS_REVERSED", NULL },
    { TBS_DOWNISLEFT, L"TBS_DOWNISLEFT", NULL },
    { TBS_NOTIFYBEFOREMOVE, L"TBS_NOTIFYBEFOREMOVE", NULL },
    { TBS_TRANSPARENTBKGND, L"TBS_TRANSPARENTBKGND", NULL }
};

// UDS_* for Up-Down Control
DLG_VALUEEDITOR_CONST stUDSDVEConsts[] = {
    { UDS_WRAP, L"UDS_WRAP", NULL },
    { UDS_SETBUDDYINT, L"UDS_SETBUDDYINT", NULL },
    { UDS_ALIGNRIGHT, L"UDS_ALIGNRIGHT", NULL },
    { UDS_ALIGNLEFT, L"UDS_ALIGNLEFT", NULL },
    { UDS_AUTOBUDDY, L"UDS_AUTOBUDDY", NULL },
    { UDS_ARROWKEYS, L"UDS_ARROWKEYS", NULL },
    { UDS_HORZ, L"UDS_HORZ", NULL },
    { UDS_NOTHOUSANDS, L"UDS_NOTHOUSANDS", NULL },
    { UDS_HOTTRACK, L"UDS_HOTTRACK", NULL }
};

// BS_* for Button Control
DLG_VALUEEDITOR_CONST stBSDVEConsts[] = {
    { BS_OWNERDRAW, L"BS_OWNERDRAW", NULL },
    { BS_PUSHBOX, L"BS_PUSHBOX", NULL },
    { BS_AUTORADIOBUTTON, L"BS_AUTORADIOBUTTON", NULL },
    { BS_USERBUTTON, L"BS_USERBUTTON", NULL },
    { BS_GROUPBOX, L"BS_GROUPBOX", NULL },
    { BS_AUTO3STATE, L"BS_AUTO3STATE", NULL },
    { BS_3STATE, L"BS_3STATE", NULL },
    { BS_RADIOBUTTON, L"BS_RADIOBUTTON", NULL },
    { BS_AUTOCHECKBOX, L"BS_AUTOCHECKBOX", NULL },
    { BS_CHECKBOX, L"BS_CHECKBOX", NULL },
    { BS_DEFPUSHBUTTON, L"BS_DEFPUSHBUTTON", NULL },
    { BS_LEFTTEXT, L"BS_LEFTTEXT", NULL },
    { BS_ICON, L"BS_ICON", NULL },
    { BS_BITMAP, L"BS_BITMAP", NULL },
    { BS_LEFT, L"BS_LEFT", NULL },
    { BS_RIGHT, L"BS_RIGHT", NULL },
    { BS_CENTER, L"BS_CENTER", NULL },
    { BS_TOP, L"BS_TOP", NULL },
    { BS_BOTTOM, L"BS_BOTTOM", NULL },
    { BS_VCENTER, L"BS_VCENTER", NULL },
    { BS_PUSHLIKE, L"BS_PUSHLIKE", NULL },
    { BS_MULTILINE, L"BS_MULTILINE", NULL },
    { BS_NOTIFY, L"BS_NOTIFY", NULL },
    { BS_FLAT, L"BS_FLAT", NULL }
};

// CBS_* for Combo Box
DLG_VALUEEDITOR_CONST stCBSDVEConsts[] = {
    { CBS_DROPDOWNLIST, L"CBS_DROPDOWNLIST", NULL },
    { CBS_DROPDOWN, L"CBS_DROPDOWN", NULL },
    { CBS_SIMPLE, L"CBS_SIMPLE", NULL },
    { CBS_OWNERDRAWFIXED, L"CBS_OWNERDRAWFIXED", NULL },
    { CBS_OWNERDRAWVARIABLE, L"CBS_OWNERDRAWVARIABLE", NULL },
    { CBS_AUTOHSCROLL, L"CBS_AUTOHSCROLL", NULL },
    { CBS_OEMCONVERT, L"CBS_OEMCONVERT", NULL },
    { CBS_SORT, L"CBS_SORT", NULL },
    { CBS_HASSTRINGS, L"CBS_HASSTRINGS", NULL },
    { CBS_NOINTEGRALHEIGHT, L"CBS_NOINTEGRALHEIGHT", NULL },
    { CBS_DISABLENOSCROLL, L"CBS_DISABLENOSCROLL", NULL },
    { CBS_UPPERCASE, L"CBS_UPPERCASE", NULL },
    { CBS_LOWERCASE, L"CBS_LOWERCASE", NULL }
};

// CBS_* for ComboBoxEx Control
DLG_VALUEEDITOR_CONST stCBESDVEConsts[] = {
    { CBS_DROPDOWNLIST, L"CBS_DROPDOWNLIST", NULL },
    { CBS_DROPDOWN, L"CBS_DROPDOWN", NULL },
    { CBS_SIMPLE, L"CBS_SIMPLE", NULL }
};

// ES_* for Edit Control
DLG_VALUEEDITOR_CONST stESDVEConsts[] = {
    { ES_CENTER, L"ES_CENTER", NULL },
    { ES_RIGHT, L"ES_RIGHT", NULL },
    { ES_MULTILINE, L"ES_MULTILINE", NULL },
    { ES_UPPERCASE, L"ES_UPPERCASE", NULL },
    { ES_LOWERCASE, L"ES_LOWERCASE", NULL },
    { ES_PASSWORD, L"ES_PASSWORD", NULL },
    { ES_AUTOVSCROLL, L"ES_AUTOVSCROLL", NULL },
    { ES_AUTOHSCROLL, L"ES_AUTOHSCROLL", NULL },
    { ES_NOHIDESEL, L"ES_NOHIDESEL", NULL },
    { ES_OEMCONVERT, L"ES_OEMCONVERT", NULL },
    { ES_READONLY, L"ES_READONLY", NULL },
    { ES_WANTRETURN, L"ES_WANTRETURN", NULL },
    { ES_NUMBER, L"ES_NUMBER", NULL }
};

// HDS_* for Header Control
DLG_VALUEEDITOR_CONST stHDSDVEConsts[] = {
    { HDS_BUTTONS, L"HDS_BUTTONS", NULL },
    { HDS_HOTTRACK, L"HDS_HOTTRACK", NULL },
    { HDS_HIDDEN, L"HDS_HIDDEN", NULL },
    { HDS_DRAGDROP, L"HDS_DRAGDROP", NULL },
    { HDS_FULLDRAG, L"HDS_FULLDRAG", NULL },
    { HDS_FILTERBAR, L"HDS_FILTERBAR", NULL },
    { HDS_FLAT, L"HDS_FLAT", NULL },
    { HDS_CHECKBOXES, L"HDS_CHECKBOXES", NULL },
    { HDS_NOSIZING, L"HDS_NOSIZING", NULL },
    { HDS_OVERFLOW, L"HDS_OVERFLOW", NULL }
};

// LBS_* for List Box
DLG_VALUEEDITOR_CONST stLBSDVEConsts[] = {
    { LBS_NOTIFY, L"LBS_NOTIFY", NULL },
    { LBS_SORT, L"LBS_SORT", NULL },
    { LBS_NOREDRAW, L"LBS_NOREDRAW", NULL },
    { LBS_MULTIPLESEL, L"LBS_MULTIPLESEL", NULL },
    { LBS_OWNERDRAWFIXED, L"LBS_OWNERDRAWFIXED", NULL },
    { LBS_OWNERDRAWVARIABLE, L"LBS_OWNERDRAWVARIABLE", NULL },
    { LBS_HASSTRINGS, L"LBS_HASSTRINGS", NULL },
    { LBS_USETABSTOPS, L"LBS_USETABSTOPS", NULL },
    { LBS_NOINTEGRALHEIGHT, L"LBS_NOINTEGRALHEIGHT", NULL },
    { LBS_MULTICOLUMN, L"LBS_MULTICOLUMN", NULL },
    { LBS_WANTKEYBOARDINPUT, L"LBS_WANTKEYBOARDINPUT", NULL },
    { LBS_EXTENDEDSEL, L"LBS_EXTENDEDSEL", NULL },
    { LBS_DISABLENOSCROLL, L"LBS_DISABLENOSCROLL", NULL },
    { LBS_NODATA, L"LBS_NODATA", NULL },
    { LBS_NOSEL, L"LBS_NOSEL", NULL },
    { LBS_COMBOBOX, L"LBS_COMBOBOX", NULL }
};

// LWS_* for SysLink Control
DLG_VALUEEDITOR_CONST stLWSDVEConsts[] = {
    { LWS_TRANSPARENT, L"LWS_TRANSPARENT", NULL },
    { LWS_IGNORERETURN, L"LWS_IGNORERETURN", NULL },
    { LWS_NOPREFIX, L"LWS_NOPREFIX", NULL },
    { LWS_USEVISUALSTYLE, L"LWS_USEVISUALSTYLE", NULL },
    { LWS_USECUSTOMTEXT, L"LWS_USECUSTOMTEXT", NULL },
    { LWS_RIGHT, L"LWS_RIGHT", NULL }
};

// LVS_* for List-View
DLG_VALUEEDITOR_CONST stLVSDVEConsts[] = {
    { LVS_LIST, L"LVS_LIST", NULL },
    { LVS_SMALLICON, L"LVS_SMALLICON", NULL },
    { LVS_REPORT, L"LVS_REPORT", NULL },
    { LVS_SINGLESEL, L"LVS_SINGLESEL", NULL },
    { LVS_SHOWSELALWAYS, L"LVS_SHOWSELALWAYS", NULL },
    { LVS_SORTASCENDING, L"LVS_SORTASCENDING", NULL },
    { LVS_SORTDESCENDING, L"LVS_SORTDESCENDING", NULL },
    { LVS_SHAREIMAGELISTS, L"LVS_SHAREIMAGELISTS", NULL },
    { LVS_NOLABELWRAP, L"LVS_NOLABELWRAP", NULL },
    { LVS_AUTOARRANGE, L"LVS_AUTOARRANGE", NULL },
    { LVS_EDITLABELS, L"LVS_EDITLABELS", NULL },
    { LVS_OWNERDATA, L"LVS_OWNERDATA", NULL },
    { LVS_NOSCROLL, L"LVS_NOSCROLL", NULL },
    { LVS_ALIGNLEFT, L"LVS_ALIGNLEFT", NULL },
    { LVS_NOSCROLL, L"LVS_NOSCROLL", NULL },
    { LVS_OWNERDRAWFIXED, L"LVS_OWNERDRAWFIXED", NULL },
    { LVS_NOCOLUMNHEADER, L"LVS_NOCOLUMNHEADER", NULL },
    { LVS_NOSORTHEADER, L"LVS_NOSORTHEADER", NULL }
};

// PGS_* for Pager Control
DLG_VALUEEDITOR_CONST stPGSDVEConsts[] = {
    { PGS_HORZ, L"PGS_HORZ", NULL },
    { PGS_AUTOSCROLL, L"PGS_AUTOSCROLL", NULL },
    { PGS_DRAGNDROP, L"PGS_DRAGNDROP", NULL }
};

// SBS_* for Scroll Bar Control
DLG_VALUEEDITOR_CONST stSBSDVEConsts[] = {
    { SBS_VERT, L"SBS_VERT", NULL },
    { SBS_TOPALIGN, L"SBS_TOPALIGN", NULL },
    { SBS_LEFTALIGN, L"SBS_LEFTALIGN", NULL },
    { SBS_BOTTOMALIGN, L"SBS_BOTTOMALIGN", NULL },
    { SBS_RIGHTALIGN, L"SBS_RIGHTALIGN", NULL },
    { SBS_SIZEBOXTOPLEFTALIGN, L"SBS_SIZEBOXTOPLEFTALIGN", NULL },
    { SBS_SIZEBOXBOTTOMRIGHTALIGN, L"SBS_SIZEBOXBOTTOMRIGHTALIGN", NULL },
    { SBS_SIZEBOX, L"SBS_SIZEBOX", NULL },
    { SBS_SIZEGRIP, L"SBS_SIZEGRIP", NULL }
};

// SS_* for Static Control
DLG_VALUEEDITOR_CONST stSSDVEConsts[] = {
    { SS_ETCHEDFRAME, L"SS_ETCHEDFRAME", NULL },
    { SS_ETCHEDVERT, L"SS_ETCHEDVERT", NULL },
    { SS_ETCHEDHORZ, L"SS_ETCHEDHORZ", NULL },
    { SS_ENHMETAFILE, L"SS_ENHMETAFILE", NULL },
    { SS_BITMAP, L"SS_BITMAP", NULL },
    { SS_OWNERDRAW, L"SS_OWNERDRAW", NULL },
    { SS_LEFTNOWORDWRAP, L"SS_LEFTNOWORDWRAP", NULL },
    { SS_SIMPLE, L"SS_SIMPLE", NULL },
    { SS_USERITEM, L"SS_USERITEM", NULL },
    { SS_WHITEFRAME, L"SS_WHITEFRAME", NULL },
    { SS_GRAYFRAME, L"SS_GRAYFRAME", NULL },
    { SS_BLACKFRAME, L"SS_BLACKFRAME", NULL },
    { SS_WHITERECT, L"SS_WHITERECT", NULL },
    { SS_GRAYRECT, L"SS_GRAYRECT", NULL },
    { SS_BLACKRECT, L"SS_BLACKRECT", NULL },
    { SS_ICON, L"SS_ICON", NULL },
    { SS_RIGHT, L"SS_RIGHT", NULL },
    { SS_CENTER, L"SS_CENTER", NULL },
    { SS_REALSIZECONTROL, L"SS_REALSIZECONTROL", NULL },
    { SS_NOPREFIX, L"SS_NOPREFIX", NULL },
    { SS_NOTIFY, L"SS_NOTIFY", NULL },
    { SS_CENTERIMAGE, L"SS_CENTERIMAGE", NULL },
    { SS_RIGHTJUST, L"SS_RIGHTJUST", NULL },
    { SS_REALSIZEIMAGE, L"SS_REALSIZEIMAGE", NULL },
    { SS_SUNKEN, L"SS_SUNKEN", NULL },
    { SS_EDITCONTROL, L"SS_EDITCONTROL", NULL },
    { SS_ENDELLIPSIS, L"SS_ENDELLIPSIS", NULL },
    { SS_PATHELLIPSIS, L"SS_PATHELLIPSIS", NULL },
    { SS_WORDELLIPSIS, L"SS_WORDELLIPSIS", NULL }
};

// TCS_* for Tab Control
DLG_VALUEEDITOR_CONST stTCSDVEConsts[] = {
    { TCS_SCROLLOPPOSITE, L"TCS_SCROLLOPPOSITE", NULL },
    { TCS_BOTTOM, L"TCS_BOTTOM", NULL },
    { TCS_MULTISELECT, L"TCS_MULTISELECT", NULL },
    { TCS_FLATBUTTONS, L"TCS_FLATBUTTONS", NULL },
    { TCS_FORCEICONLEFT, L"TCS_FORCEICONLEFT", NULL },
    { TCS_FORCELABELLEFT, L"TCS_FORCELABELLEFT", NULL },
    { TCS_HOTTRACK, L"TCS_HOTTRACK", NULL },
    { TCS_VERTICAL, L"TCS_VERTICAL", NULL },
    { TCS_BUTTONS, L"TCS_BUTTONS", NULL },
    { TCS_SINGLELINE, L"TCS_SINGLELINE", NULL },
    { TCS_MULTILINE, L"TCS_MULTILINE", NULL },
    { TCS_FIXEDWIDTH, L"TCS_FIXEDWIDTH", NULL },
    { TCS_RAGGEDRIGHT, L"TCS_RAGGEDRIGHT", NULL },
    { TCS_FOCUSONBUTTONDOWN, L"TCS_FOCUSONBUTTONDOWN", NULL },
    { TCS_OWNERDRAWFIXED, L"TCS_OWNERDRAWFIXED", NULL },
    { TCS_TOOLTIPS, L"TCS_TOOLTIPS", NULL },
    { TCS_FOCUSNEVER, L"TCS_FOCUSNEVER", NULL }
};

// TVS_* for Tree-View Control
DLG_VALUEEDITOR_CONST stTVSDVEConsts[] = {
    { TVS_HASBUTTONS, L"TVS_HASBUTTONS", NULL },
    { TVS_HASLINES, L"TVS_HASLINES", NULL },
    { TVS_LINESATROOT, L"TVS_LINESATROOT", NULL },
    { TVS_EDITLABELS, L"TVS_EDITLABELS", NULL },
    { TVS_DISABLEDRAGDROP, L"TVS_DISABLEDRAGDROP", NULL },
    { TVS_SHOWSELALWAYS, L"TVS_SHOWSELALWAYS", NULL },
    { TVS_RTLREADING, L"TVS_RTLREADING", NULL },
    { TVS_NOTOOLTIPS, L"TVS_NOTOOLTIPS", NULL },
    { TVS_CHECKBOXES, L"TVS_CHECKBOXES", NULL },
    { TVS_TRACKSELECT, L"TVS_TRACKSELECT", NULL },
    { TVS_SINGLEEXPAND, L"TVS_SINGLEEXPAND", NULL },
    { TVS_INFOTIP, L"TVS_INFOTIP", NULL },
    { TVS_FULLROWSELECT, L"TVS_FULLROWSELECT", NULL },
    { TVS_NOSCROLL, L"TVS_NOSCROLL", NULL },
    { TVS_NONEVENHEIGHT, L"TVS_NONEVENHEIGHT", NULL },
    { TVS_NOHSCROLL, L"TVS_NOHSCROLL", NULL }
};

// MDIS_* for MDI Client
DLG_VALUEEDITOR_CONST stMDISDVEConsts[] = {
    { MDIS_ALLCHILDSTYLES, L"MDIS_ALLCHILDSTYLES", NULL }
};

#define AW_DATABASE_SYSCTLLIB_COMMCTLINDEX 2

AW_SYSCLASSINFO aAWSysCtlLib[] = {
    { TEXT("#32769"), I18NIndex_Desktop },
    { WC_DIALOG, I18NIndex_Dialog, stDSDVEConsts, ARRAYSIZE(stDSDVEConsts) },
    // Common Controls
    { ANIMATE_CLASS, I18NIndex_Animation, stACSDVEConsts, ARRAYSIZE(stACSDVEConsts) },
    { DATETIMEPICK_CLASS, I18NIndex_DateAndTimePicker, stDTSDVEConsts, ARRAYSIZE(stDTSDVEConsts) },
    { HOTKEY_CLASS, I18NIndex_HotKey, NULL, 0 },
    { MONTHCAL_CLASS, I18NIndex_Calendar, stMCSDVEConsts, ARRAYSIZE(stMCSDVEConsts) },
    { PROGRESS_CLASS, I18NIndex_ProgressBar, stPBSDVEConsts, ARRAYSIZE(stPBSDVEConsts) },
    { REBARCLASSNAME, (UINT_PTR)TEXT("ReBar"), stRBSDVEConsts, ARRAYSIZE(stRBSDVEConsts) },
    { STATUSCLASSNAME, I18NIndex_StatusBar, stSBARSDVEConsts, ARRAYSIZE(stSBARSDVEConsts) },
    { TOOLBARCLASSNAME, I18NIndex_ToolBar, stTBSTYLEDVEConsts, ARRAYSIZE(stTBSTYLEDVEConsts) },
    { TOOLTIPS_CLASS, I18NIndex_ToolTips, stTTSDVEConsts, ARRAYSIZE(stTTSDVEConsts) },
    { TRACKBAR_CLASS, I18NIndex_SliderBar, stTBSDVEConsts, ARRAYSIZE(stTBSDVEConsts) },
    { UPDOWN_CLASS, I18NIndex_UpDownControl, stUDSDVEConsts, ARRAYSIZE(stUDSDVEConsts) },
    { WC_BUTTON, I18NIndex_Button, stBSDVEConsts, ARRAYSIZE(stBSDVEConsts) },
    { WC_COMBOBOX, I18NIndex_ComboBox, stCBSDVEConsts, ARRAYSIZE(stCBSDVEConsts) },
    { WC_COMBOBOXEX, I18NIndex_ExtendedComboBox, stCBESDVEConsts ,ARRAYSIZE(stCBESDVEConsts) },
    { WC_EDIT, I18NIndex_EditControl, stESDVEConsts, ARRAYSIZE(stESDVEConsts) },
    { WC_HEADER, I18NIndex_HeaderControl, stHDSDVEConsts, ARRAYSIZE(stHDSDVEConsts) },
    { WC_LISTBOX, I18NIndex_ListBox, stLBSDVEConsts, ARRAYSIZE(stLBSDVEConsts) },
    { WC_IPADDRESS, I18NIndex_IPAddressControl, NULL, 0 },
    { WC_LINK, I18NIndex_Hyperlink, stLWSDVEConsts, ARRAYSIZE(stLWSDVEConsts) },
    { WC_LISTVIEW, I18NIndex_ListView, stLVSDVEConsts, ARRAYSIZE(stLVSDVEConsts) },
    { WC_NATIVEFONTCTL, I18NIndex_NativeFont, NULL, 0 },
    { WC_PAGESCROLLER, I18NIndex_PageScroller, stPGSDVEConsts, ARRAYSIZE(stPGSDVEConsts) },
    { WC_SCROLLBAR, I18NIndex_ScrollBar, stSBSDVEConsts, ARRAYSIZE(stSBSDVEConsts) },
    { WC_STATIC, I18NIndex_StaticControl, stSSDVEConsts, ARRAYSIZE(stSSDVEConsts) },
    { WC_TABCONTROL, I18NIndex_TabControl, stTCSDVEConsts, ARRAYSIZE(stTCSDVEConsts) },
    { WC_TREEVIEW, I18NIndex_TreeView, stTVSDVEConsts, ARRAYSIZE(stTVSDVEConsts) },
    // Additional
    { L"MDIClient", I18NIndex_MDIClient, stMDISDVEConsts, ARRAYSIZE(stMDISDVEConsts) }
};

// ********** Functions **********

PAW_SYSCLASSINFO AW_DBFindSysClassInfoByName(PTSTR pszClassName) {
    UINT    i;
    TCHAR   szClassOrdName[MAX_WORD_IN_DEC_CCH + 2];
    PTSTR   pszName;
    for (i = 0; i < ARRAYSIZE(aAWSysCtlLib); i++) {
        if (IS_INTRESOURCE(aAWSysCtlLib[i].ClassName)) {
            if (Str_Printf(szClassOrdName, TEXT("#%hu"), LOWORD(aAWSysCtlLib[i].ClassName)) <= 0)
                szClassOrdName[0] = '\0';
            pszName = szClassOrdName;
        } else
            pszName = aAWSysCtlLib[i].ClassName;
        if (Str_Equal(pszClassName, pszName))
            return &aAWSysCtlLib[i];
    }
    return NULL;
}

PAW_SYSCLASSINFO AW_DBFindSysClassInfo(HWND hWnd) {
    TCHAR   szClassName[MAX_CLASSNAME_CCH];
    return GetClassName(hWnd, szClassName, ARRAYSIZE(szClassName)) ?
        AW_DBFindSysClassInfoByName(szClassName) :
        NULL;
}

VOID AWDatabaseInit() {
    // I18N strings for Dlg_ValueEditor
    DB_lpszDVE[0] = I18N_GetString(I18NIndex_CombinedValueEditor);
    DB_lpszDVE[1] = DB_lpszDRE[1] = I18N_GetString(I18NIndex_Reset);
    DB_lpszDVE[2] = DB_lpszDRE[2] = I18N_GetString(I18NIndex_OK);
    DB_lpszDVE[3] = I18N_GetString(I18NIndex_Member);
    DB_lpszDVE[4] = I18N_GetString(I18NIndex_Value);
    DB_lpszDVE[5] = I18N_GetString(I18NIndex_Description);
    DB_lpszDVE[6] = I18N_GetString(I18NIndex_DVEUnknow);
    // I18N strings for Dlg_RectEditor
    DB_lpszDRE[0] = I18N_GetString(I18NIndex_RectEditor);
    DB_lpszDRE[3] = I18N_GetString(I18NIndex_Left);
    DB_lpszDRE[4] = I18N_GetString(I18NIndex_Top);
    DB_lpszDRE[5] = I18N_GetString(I18NIndex_Right);
    DB_lpszDRE[6] = I18N_GetString(I18NIndex_Bottom);
    DB_lpszDRE[7] = I18N_GetString(I18NIndex_Width);
    DB_lpszDRE[8] = I18N_GetString(I18NIndex_Height);
}

BOOL AW_DBEditValue(HWND hDlg, HWND hWnd, AW_VALUETYPE eType, PDWORD lpdwValue) {
    QWORD                   qwValue = *lpdwValue;
    BOOL                    bEdited = FALSE;
    PDLG_VALUEEDITOR_CONST lpstConsts;
    UINT                    uConsts;
    if (eType == AWValueStyle) {
        PDLG_VALUEEDITOR_CONST lpstConstsTemp, lpstConstsSysClass;
        UINT                    uConstsTemp, uConstsSysClass;
        PAW_SYSCLASSINFO        lpstSysClassInfo;
        if (qwValue & WS_CHILD) {
            lpstConstsTemp = stWSCDVEConsts;
            uConstsTemp = ARRAYSIZE(stWSCDVEConsts);
        } else {
            lpstConstsTemp = stWSPDVEConsts;
            uConstsTemp = ARRAYSIZE(stWSPDVEConsts);
        }
        lpstSysClassInfo = AW_DBFindSysClassInfo(hWnd);
        if (lpstSysClassInfo) {
            lpstConstsSysClass = lpstSysClassInfo->StyleConsts;
            uConstsSysClass = lpstSysClassInfo->StyleConstsCount;
        } else {
            lpstConstsSysClass = NULL;
            uConstsSysClass = 0;
        }
        lpstConsts = Data_StructCombine(
            3,
            DLG_VALUEEDITOR_CONST,
            stWSDVEConsts,
            ARRAYSIZE(stWSDVEConsts),
            lpstConstsTemp,
            uConstsTemp,
            lpstConstsSysClass,
            uConstsSysClass
        );
        uConsts = ARRAYSIZE(stWSDVEConsts) + uConstsTemp + uConstsSysClass;
    } else if (eType == AWValueExStyle) {
        lpstConsts = stWSEXDVEConsts;
        uConsts = ARRAYSIZE(stWSEXDVEConsts);
    } else if (eType == AWValueClass) {
        lpstConsts = stCSDVEConsts;
        uConsts = ARRAYSIZE(stCSDVEConsts);
    } else
        return FALSE;
    if (Dlg_ValueEditorEx(hDlg, DVE_TYPE_COMBINATION | DVE_VALUE_HEXDWORD, DB_lpszDVE, &qwValue, lpstConsts, uConsts)) {
        *lpdwValue = (DWORD)qwValue;
        bEdited = TRUE;
    }
    if (eType == AWValueStyle && lpstConsts)
        Mem_HeapFree(lpstConsts);
    return bEdited;
}