/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx    = 6;   /* pixel gap between clients */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */
static const char *fonts[]     = {"Cascadia Code:size=12:antialias=true:autohint=true",
                                  "Hack:size=8:antialias=true:autohint=true",
                                  "Font Awesome 5 Free:size=10:antialias=true:autohint=true"
						     	};
static const char dmenufont[]       = "Cascadia Code:size=12";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#6272a4";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#bd93f9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#include "shiftview.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {   
	/* modifier             key        function        argument */
	{ MODKEY|ControlMask,   XK_d, 	   spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_d, 	   spawn,          CMD("dmenu_run -c -l 20") },
    { MODKEY,               XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,               XK_b,      togglebar,      {0} }, // togle top bar
	{ MODKEY|ShiftMask,     XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,               XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,               XK_h,      setmfact,       {.f = -0.05} },//reduce width of master
	{ MODKEY,               XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,			    XK_space,  zoom,           {0} },
	/*{ MODKEY,               XK_Tab,    view,           {0} },*/
	{ MODKEY,     			XK_q,      killclient,     {0} },
    /*{ MODKEY,               XK_parenright,  setgaps,   {.i = -1 } },
    { MODKEY,               XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_equal,  setgaps,        {.i = 0  } },*/

    /* Layout manipulation */
	{ MODKEY,               XK_Tab,    shiftview,    {.i = +1 } },
    { MODKEY|ShiftMask,     XK_Tab,    shiftview,    {.i = -1 } },
	/*{ MODKEY|ControlMask,   XK_Tab,    cyclelayout,  {.i = +1 } },*/
	/*{ MODKEY,               XK_space,  setlayout,      {0} },*/
	{ MODKEY|ShiftMask,     XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
	{ MODKEY,               XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_g,      setlayout,      {.v = &layouts[3]} },

	/* desktops */
	{ MODKEY,               XK_agrave,      view,      {.ui = ~0 } },
	/*{ MODKEY,               XK_Tab,         view, 	   {.ui = +1 } },*/


	TAGKEYS(                XK_ampersand,              0)
	TAGKEYS(                XK_eacute,                 1)
	TAGKEYS(                XK_quotedbl,               2)
	TAGKEYS(				XK_apostrophe,             3)
	TAGKEYS(				XK_parenleft,              4)
	TAGKEYS(				XK_minus,                  5)
	TAGKEYS(				XK_egrave,                 6)
	TAGKEYS(				XK_underscore,             7)
	TAGKEYS(				XK_ccedilla,               8)

    /* Switching between monitors */
	{ MODKEY,               XK_comma,     focusmon,    {.i = -1 } },
	{ MODKEY,               XK_semicolon, focusmon,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,     tagmon,      {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_semicolon, tagmon,      {.i = +1 } },

	/* app launcher */
	{ MODKEY, 				XK_w,		  spawn,	   CMD("librewolf") },
    { MODKEY|ShiftMask, 	XK_w,		  spawn,	   CMD("firefox-developer-edition") },
	{ MODKEY,				XK_r,		  spawn,	   CMD("pcmanfm") },
	{ MODKEY,				XK_e,		  spawn,	   CMD("codium") },
	{ MODKEY,				XK_F1,		  spawn,	   CMD("pamac-manager") },
	{ MODKEY,				XK_F2,		  spawn,	   CMD("st -e pulsemixer") },
	{ MODKEY,				XK_F3,		  spawn,	   CMD("discord") },
	{ MODKEY,				XK_F4,		  spawn,	   CMD("lutris") },
	{ MODKEY,				XK_F5,		  spawn,	   CMD("steam") },
	{ 0,				    XK_Print,	  spawn,	   CMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,	  spawn,	   CMD("maimpick") },
	{ ControlMask,			XK_Escape,	  spawn,	   CMD("xfce4-taskmanager") },
	
	
    /* Apps Launched with SUPER + ALT + KEY */
	
	{ MODKEY|Mod1Mask,        XK_g,    spawn,          CMD("st -e gtop") },

    
	/*qwrty config 
	TAGKEYS(                  XK_1,          0)
	TAGKEYS(                  XK_2,          1)
	TAGKEYS(                  XK_3,          2)
	TAGKEYS(                  XK_4,          3)
	TAGKEYS(                  XK_5,          4)
	TAGKEYS(                  XK_6,          5)
	TAGKEYS(                  XK_7,          6)
	TAGKEYS(                  XK_8,          7)
	TAGKEYS(                  XK_9,          8)*/

	

	{ MODKEY|ShiftMask,       XK_q,	   quit,		   {0} },
    { MODKEY|ShiftMask,       XK_r,    quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkClientWin|ShiftMask,MODKEY,Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};

