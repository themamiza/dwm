/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
                                                /* systray has to be sloppy or the alignment of the blocks won't work (as of now) */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static                int smartgaps = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 32;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Iosevka:size=12", "NotoColorEmoji:size=10" };
static const char dmenufont[]       = "Iosevka:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",          NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Pavucontrol",   NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Qalculate-gtk", NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",       NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",            NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,            NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define XK_NO_MOD 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
/* static const char *termcmd[]  = { "st", NULL }; */

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier            key              function        argument */
	{ MODKEY,              XK_d,            spawn,          { .v = dmenucmd }  },
	{ MODKEY,              XK_Return,       spawn,          SHCMD("$TERMINAL") },
	{ MODKEY,              XK_w,            spawn,          SHCMD("$BROWSER")  },
	{ MODKEY|ShiftMask,    XK_w,            spawn,          SHCMD("brave --incognito")  },
	{ MODKEY,              XK_e,            spawn,          SHCMD("emacs")     },
	{ MODKEY,              XK_equal,        spawn,          SHCMD("pamixer --allow-boost -i  5; kill -44 $(pidof dwmblocks)")  },
	{ MODKEY|ShiftMask,    XK_equal,        spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)")  },
	{ MODKEY,              XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d  5; kill -44 $(pidof dwmblocks)")  },
	{ MODKEY|ShiftMask,    XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d  5; kill -44 $(pidof dwmblocks)")  },
	{ MODKEY|ShiftMask,    XK_m,            spawn,          SHCMD("pamixer               -t   ; kill -44 $(pidof dwmblocks)")  },
	{ MODKEY,              XK_bracketright, spawn,          SHCMD("xbacklight -inc 10")  },
	{ MODKEY|ShiftMask,    XK_bracketright, spawn,          SHCMD("xbacklight -inc 25")  },
	{ MODKEY,              XK_bracketleft,  spawn,          SHCMD("xbacklight -dec 25")  },
	{ MODKEY|ShiftMask,    XK_bracketleft,  spawn,          SHCMD("xbacklight -dec 25")  },
	{ XK_NO_MOD,           XK_Print,        spawn,          SHCMD("scrot    ~/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,           XK_Print,        spawn,          SHCMD("scrot -s ~/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,              XK_n,            spawn,          SHCMD("find  ~/.local/share/wallpapers/* | shuf | nsxiv -bit") },
	{ MODKEY|ShiftMask,    XK_n,            spawn,          SHCMD("setbg ~/.local/share/wallpapers ") },
	{ MODKEY|ShiftMask,    XK_slash,        spawn,          SHCMD("switchxkbmap") },
	{ MODKEY,              XK_BackSpace,    spawn,          SHCMD("sysact") },
	{ MODKEY,              XK_r,            spawn,          SHCMD("$TERMINAL -e lfub -single") },
	{ MODKEY|ShiftMask,    XK_h,            spawn,          SHCMD("$TERMINAL -e htop") },
	{ MODKEY|ShiftMask,    XK_i,            spawn,          SHCMD("$TERMINAL -e nmtui") },
	{ MODKEY,              XK_g,            spawn,          SHCMD("thunar") },
	{ ControlMask|AltMask, XK_u,            spawn,          SHCMD("dmenuunicode") },
	{ ControlMask|AltMask, XK_m,            spawn,          SHCMD("dmenumount")   },
	{ ControlMask|AltMask, XK_n,            spawn,          SHCMD("dmenuumount")  },
	{ MODKEY,              XK_b,            togglebar,      {0} },
	{ MODKEY|ShiftMask,    XK_b,            toggletopbar,   {0} },
	{ MODKEY,              XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,              XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,              XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_p,            incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,    XK_Return,       zoom,           {0} },
	{ MODKEY,              XK_s,            togglesticky,   {0} },
	{ MODKEY,              XK_z,            incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_z,            incrgaps,       {.i = -1 } },
	{ MODKEY,              XK_x,            incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_x,            incrigaps,      {.i = -1 } },
	{ MODKEY,              XK_c,            incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_c,            incrogaps,      {.i = -1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrihgaps,     {.i = +1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrihgaps,     {.i = -1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrivgaps,     {.i = +1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrivgaps,     {.i = -1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrohgaps,     {.i = +1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrohgaps,     {.i = -1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrovgaps,     {.i = +1 } },
	{ XK_NO_MOD,           XK_NO_MOD,       incrovgaps,     {.i = -1 } },
	{ MODKEY,              XK_a,            togglegaps,     {0} },
	{ MODKEY|ShiftMask,    XK_a,            defaultgaps,    {0} },
	{ XK_NO_MOD,           XK_NO_MOD,       view,           {0} },
	{ MODKEY,              XK_q,            killclient,     {0} },
	{ MODKEY,              XK_f,            togglefullscr,  {0} },
	{ MODKEY|ControlMask,  XK_comma,        cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,  XK_period,       cyclelayout,    {.i = +1 } },
	{ MODKEY,              XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,    XK_space,        togglefloating, {0} },
	{ MODKEY,              XK_Down,         moveresize,     {.v = "0x 25y 0w 0h"  } },
	{ MODKEY,              XK_Up,           moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,              XK_Right,        moveresize,     {.v = "25x 0y 0w 0h"  } },
	{ MODKEY,              XK_Left,         moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,    XK_Down,         moveresize,     {.v = "0x 0y 0w 25h"  } },
	{ MODKEY|ShiftMask,    XK_Up,           moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,    XK_Right,        moveresize,     {.v = "0x 0y 25w 0h"  } },
	{ MODKEY|ShiftMask,    XK_Left,         moveresize,     {.v = "0x 0y -25w 0h" } },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "t"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "b"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "l"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "r"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "T"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "B"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "L"} },
	{ XK_NO_MOD,           XK_NO_MOD,       moveresizeedge, {.v = "R"} },
	{ MODKEY,              XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,              XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period,       tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_apostrophe,   setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_semicolon,    setborderpx,    {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_f,            setborderpx,    {.i =  0 } },
	TAGKEYS(               XK_1,                      0)
	TAGKEYS(               XK_2,                      1)
	TAGKEYS(               XK_3,                      2)
	TAGKEYS(               XK_4,                      3)
	TAGKEYS(               XK_5,                      4)
	TAGKEYS(               XK_6,                      5)
	TAGKEYS(               XK_7,                      6)
	TAGKEYS(               XK_8,                      7)
	TAGKEYS(               XK_9,                      8)
	{ XK_NO_MOD,           XF86XK_AudioMute,         spawn, SHCMD("pamixer               -t  ; kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD,           XF86XK_AudioLowerVolume,  spawn, SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD,           XF86XK_AudioRaiseVolume,  spawn, SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD,           XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 10") },
	{ XK_NO_MOD,           XF86XK_MonBrightnessUp,   spawn, SHCMD("xbacklight -inc 10") },
	{ XK_NO_MOD,           XK_F6,                    spawn, SHCMD("touchpad-toggle") },
	{ XK_NO_MOD,           XF86XK_Calculator,        spawn, SHCMD("qalculate-gtk") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
