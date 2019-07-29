/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[] = { "Source Code Pro:size=16" };
static const char *fonts[] = {
    "Font Awesome 5 Free:size=12",
    "Font Awesome 5 Brands:size=12",
    "Roboto Mono for Powerline:size=12"
};
static const char dmenufont[]       = "Roboto Mono for Powerline:size=12";
//static const char dmenufont[]       = "Terminess Powerline:size=14";
static const char col_gray1[]       = "#111111";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_blue_gray[]   = "#18232A";
static const char col_blue_mid[]   =  "#0A354D";
static const char col_cyan[]        = "#00aaee";
static const char col_orange[]      = "#B66011";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#FFFFFF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_blue_gray, col_gray2 },
	[SchemeSel]  = { col_white, col_blue_mid,  col_orange  },
};

#define fa_mail ""
#define fa_code ""
#define fa_chrome ""
#define fa_tile ""
#define fa_columns ""
#define fa_max ""
#define fa_float ""
#define fa_terminal ""
#define fa_todo ""
#define fa_read ""
#define fa_files ""
#define fa_write ""
#define fa_music ""
#define fa_cog ""
#define fa_chart ""
#define fa_flask ""


/* tagging */
static const char *tags[] = {
    fa_terminal,
    fa_chrome,
    fa_code,
    fa_flask,
    fa_write,
    fa_read,
    fa_todo,
    fa_mail,
    fa_chart,
};

static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class  instance                                title  tags mask  isfloating   monitor */
	{  NULL,  "Mail",                                 NULL,  1 << 7,    0,           -1 },
	{  NULL,  "mailspring",                           NULL,  1 << 7,    0,           -1 },
	{  NULL,  "tsurf",                                NULL,  1 << 1,    0,           -1 },
	{  NULL,  "google-chrome",                        NULL,  1 << 1,    0,           -1 },
	{  NULL,  "crx_ojcflmmmcfpacggndoaaflkmcoblhnbh", NULL,  1 << 6,    0,           -1 }, //wunderlist
	{  NULL,  "gnome-calendar", NULL,  1 << 6,    0,           -1 },
	{  NULL,  NULL,                                   "htop",1 << 8,    0,           -1 }, 
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ fa_tile,      tile },    /* first entry is default */
	{ fa_float,      NULL },    /* no layout function means floating behavior */
    { "[ ]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_blue_gray, "-sf", col_gray4, NULL };
static const char *term_cmd[]  = { "st", "-e", "tmux" };
static const char *slock_cmd[] = { "slock", NULL };
//static const char *zlaunch_cmd[] = { "zlaunch", NULL };
static const char *kill_dwm_cmd[] = { "killall dwm_start", NULL };
static const char *all_displays_cmd[] = { "all_displays", NULL };
static const char *up_vol[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mute_vol[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = term_cmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slock_cmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = kill_dwm_cmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = all_displays_cmd } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = down_vol } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = up_vol } },
	{ 0,         XF86XK_AudioMute,      spawn,          {.v = mute_vol } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term_cmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

