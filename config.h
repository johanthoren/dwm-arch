/* See LICENSE file for copyright and license details. */

/* swallowing */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

/* systray */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#3C3836";
static const char col_gray3[]       = "#504945";
static const char col_gray4[]       = "#665c54";
static const char col_cream0[]      = "#eddbb2";
static const char col_cream1[]      = "#fbf1c7";
static const char col_aqua[]        = "#689d6a";
static const char col_cyan0[]       = "#458588";
static const char col_cyan1[]       = "#076678";
static const char col_green[]       = "#98971a";
static const char col_orange[]      = "#d65d0e";
static const char col_purple[]      = "#b16286";
static const char col_red[]         = "#cc241d";
static const char col_yellow[]      = "#d79921";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
  [SchemeNorm] = { col_cream0, col_gray1, col_gray2 },
  [SchemeSel]  = { col_cream1, col_cyan1, col_yellow  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance        title           tags mask    iscenter  isfloating  isterminal  noswallow  monitor */
  { "Gimp",            NULL,             NULL,           0,         0,         1,         0,           0,        -1 },
	{ "Chromium",        NULL,             NULL,           1 << 1,    0,         0,         0,           0,        -1 },
	{ "Emacs",           NULL,             NULL,           1 << 2,    0,         0,         0,           0,        -1 },
	{ NULL,              "itrs.slack.com", NULL,           1 << 0,    0,         0,         0,           0,         1 },
	{ NULL,              "web.fuze.com",   NULL,           1 << 1,    0,         0,         0,           0,         1 },
	{ "St",              NULL,             NULL,           0,         0,         0,         1,           1,        -1 },
	{ NULL,              NULL,             "Event Tester", 0,         0,         1,         0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_cream1, "-sb", col_cyan1, "-sf", col_cream1, topbar ? NULL : "-b", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *filecmd[]  = { "st", "-e", "ranger", NULL };
static const char *webcmd[]  = { "chromium", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("emacsclient -c -a 'emacs'") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webcmd } },
  { 0,                            XK_F1,     spawn,          SHCMD("pactl -- set-sink-mute @DEFAULT_SINK@ toggle") },
  { 0,                            XK_F2,     spawn,          SHCMD("pactl -- set-sink-volume @DEFAULT_SINK@ -5%") },
  { 0,                            XK_F3,     spawn,          SHCMD("pactl -- set-sink-volume @DEFAULT_SINK@ +5%") },
  { 0,                            XK_F4,     spawn,          SHCMD("playerctl play-pause") },
  { 0,                            XK_F5,     spawn,          SHCMD("playerctl previous") },
  { 0,                            XK_F6,     spawn,          SHCMD("playerctl next") },
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("$HOME/bin/screen_script.sh") },
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("$HOME/bin/screen_script.sh -a") },
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("$HOME/.screenlayout/mobile.sh") },
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("$HOME/bin/connect_airpods.sh") },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("i3lock-fancy-rapid 5 2") },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

static const char *const autostart[] = {
  /* "xrandr", "--setprovideroutputsource", "modesetting", "NVIDIA-0", NULL, */
  /* "xrandr", "--auto", NULL, */
  "start-pulseaudio-x11", NULL,
  "xrdb", "-merge", "$HOME/.Xresources", NULL,
  "xss-lock", "--", "/usr/bin/i3lock-fancy-rapid", "5", "2", NULL,
  "dunst", NULL,
  "xbanish", NULL,
  "numlockx", NULL,
  "nm-applet", NULL,
  "picom", NULL,
  "dwmblocks", NULL,
  "sh", "-c", "$HOME/bin/screen_script.sh", NULL,
  "sh", "-c", "$HOME/bin/set_wallpaper.sh", NULL,
  "piactl", "connect", NULL,
  NULL /* terminate */
};
