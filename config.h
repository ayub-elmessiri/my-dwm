/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "FiraCode Nerd Font:size=12" };
static const char dmenufont[]       = "FiraCode Nerd Font Mono:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_grayCbg[]	    = "#232330";
static const char col_grayCT[]	    = "#565684";
static const char col_grayCTbrdr[]  = "#7878a6";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const char col_blue[]	    = "#4682B4";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_grayCbg, col_gray2 },
	[SchemeSel]  = { col_white, col_grayCT,  col_grayCTbrdr  },
	[SchemeTitle]  = { col_white, col_grayCT,  col_grayCTbrdr  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *togglelang[] = { "togglelang", NULL };

#include "exitdwm.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       40,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       39,      spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,		65,      spawn,	         {.v = togglelang } },
	{ MODKEY,			55,      spawn,	   SHCMD("amixer -q -D pulse sset Master 10%+; pkill -USR1 slstatus") },
	{ MODKEY|ShiftMask,		55,      spawn,	   SHCMD("amixer -q -D pulse sset Master 10%-; pkill -USR1 slstatus") },
	{ MODKEY|ControlMask,		55,      spawn,	   SHCMD("amixer sset Master toggle; pkill -USR1 slstatus") },
	{ MODKEY,                       56,      togglebar,      {0} },
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             31,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       36, 	 zoom,           {0} },
	{ MODKEY,                       23,      view,           {0} },
	{ MODKEY,		        24,      killclient,     {0} },
	{ MODKEY,                       28,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       41,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       58,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       65,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             41,      togglefloating, {0} },
	{ MODKEY,                       19,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } },
	{ MODKEY,                       59,      focusmon,       {.i = -1 } },
	{ MODKEY,                       60,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             59,  	 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             60,	 tagmon,         {.i = +1 } },
	{ MODKEY,                       114, 	 viewnext,       {0} },
	{ MODKEY,                       113,     viewprev,       {0} },
	{ MODKEY|ShiftMask,             114,     tagtonext,      {0} },
	{ MODKEY|ShiftMask,             113,     tagtoprev,      {0} },
	TAGKEYS(                        10,                      0)
	TAGKEYS(                        11,                      1)
	TAGKEYS(                        12,                      2)
	TAGKEYS(                        13,                      3)
	TAGKEYS(                        14,                      4)
	TAGKEYS(                        15,                      5)
	TAGKEYS(                        16,                      6)
	TAGKEYS(                        17,                      7)
	TAGKEYS(                        18,                      8)
	{ MODKEY|ShiftMask,             24,        quit,           {0} },
	{ MODKEY,	                26,        exitdwm,        {0} },
	{ MODKEY,			27,        quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

