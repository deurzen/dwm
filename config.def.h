/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
  "Misc Tamsyn:size=12",
  "monospace:size=9",
  "tewi:pixelsize=9",
  "Terminus2:pixelsize=12"
};
//static const char dmenufont[]       = "tewi:pixelsize=10";
static const char font[]            = "-xos4-terminus-medium-r-normal--12-*-*-*-*-*-*-*";
static const char dmenufont[]       = "-*-tewi-medium-r-normal-*-11-90-100-100-c-60-iso10646-1";
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#111111";
static const char normfgcolor[]     = "#5911c0";
static const char selbordercolor[]  = "#353535";
static const char selbgcolor[]      = "#111111";
static const char selfgcolor[]      = "#cc00ff";
/* border pixel of windows */
static const unsigned int borderpx  = 1;
/* snap pixel */
static const unsigned int snap      = 0;
/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systraypinning = 0;
/* systray spacing */
static const unsigned int systrayspacing = 2;
/* 1: if pinning fails, display systray on the first monitor,
 * 0: display systray on the last monitor */
static const int systraypinningfailfirst = 1;
/* 0 means no systray */
static const int showsystray = 1;
/* 0 means no bar */
static const int showbar = 1;
/* 0 means bottom bar */
static const int topbar = 1;
/* 0 means no extra bar */
static const int extrabar = 1;
static const int focusonwheel = 0;

/* tagging */
static const char *tags[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class         instance    title       tags mask     isfloating   monitor */
  { "Gimp",        NULL,       NULL,       0,            1,           -1 },
  { "Firefox",     NULL,       NULL,       1 << 8,       0,           -1 },
  { "st-float",    NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
  { "[@]",      spiral },
  { "[\\]",     dwindle },
  { "TTT",      bstack },
  { "===",      bstackhoriz },
  { "|M|",      centeredmaster },
  { ">M>",      centeredfloatingmaster },
  { "|||",      deck },
  { "|+|",      gaplessgrid },
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
static       char dmenumon[2]       = "0"; /* component of dmenucmd, manipulated in spawn() */
// program binds
static const char *dmenucmd[]       = { "rofi", "-run-command", "zsh -i -c '{cmd}'", "-show", "run",
                                        "-font", "tewi 9", "-width", "20", "-lines", "3", NULL };
static const char *rofipass[]       = { "rofi-pass", NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *floattermcmd[]   = { "st", "-c", "\"st-float\"", NULL };
static const char *stregion[]       = { "stregion", NULL };
static const char *qutebrowser[]    = { "qutebrowser", NULL };
static const char *qutebrowseror[]  = { "qutebrowser", "-R", NULL };
static const char *lockscreen[]     = { "7lock", NULL };

// multimedia binds
static const char *volumeup[]       = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *volumedown[]     = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *volumemute[]     = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brightup[]       = { "light", "-A", "15", NULL };
static const char *brightdown[]     = { "light", "-U", "15", NULL };
static const char *lightup[]        = { "light", "-A", "5", NULL };
static const char *lightdown[]      = { "light", "-U", "5", NULL };

// mpc commands
static const char *mpctoggle[]      = { "mpc", "toggle", NULL };
static const char *mpcnext[]        = { "mpc", "next", NULL };
static const char *mpcprev[]        = { "mpc", "prev", NULL };
static const char *mpcstop[]        = { "mpc", "stop", NULL };
static const char *mpcrandom[]      = { "mpc", "random", NULL };
static const char *mpcsingle[]      = { "mpc", "single", NULL };

// general management commands
static const char scratchpadname[]  = "scratchpad";
static const char *scratchpadcmd[]  = { "st", "-t", scratchpadname, "-g", "120x34", NULL };


#include "movestack.c"
static Key keys[] = {
  /* modifier                     key        function        argument */
// program binds
  { MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = floattermcmd } },
  { MODKEY,                       XK_w,      spawn,          {.v = stregion} },
  { MODKEY,                       XK_p,      spawn,          {.v = rofipass} },
  { MODKEY,                       XK_q,      spawn,          {.v = qutebrowser} },
  { MODKEY|ShiftMask,             XK_q,      spawn,          {.v = qutebrowseror} },
  { MODKEY|ShiftMask,             XK_Delete, spawn,          {.v = lockscreen} },
// multimedia binds
  { 0,                            0x1008ff13,spawn,          {.v = volumeup} },
  { 0,                            0x1008ff11,spawn,          {.v = volumedown} },
  { 0,                            0x1008ff12,spawn,          {.v = volumemute} },
  { 0,                            0x1008ff02,spawn,          {.v = brightup} },
  { 0,                            0x1008ff03,spawn,          {.v = brightdown} },
  { ShiftMask,                    0x1008ff02,spawn,          {.v = lightup} },
  { ShiftMask,                    0x1008ff03,spawn,          {.v = lightdown} },
// mpc binds
  { MODKEY|ControlMask,           XK_p,      spawn,          {.v = mpctoggle} },
  { MODKEY|ControlMask,           XK_j,      spawn,          {.v = mpcnext} },
  { MODKEY|ControlMask,           XK_k,      spawn,          {.v = mpcprev} },
  { MODKEY|ControlMask,           XK_BackSpace,spawn,        {.v = mpcstop} },
  { MODKEY|ControlMask,           XK_r,      spawn,          {.v = mpcrandom} },
  { MODKEY|ControlMask,           XK_s,      spawn,          {.v = mpcsingle} },
// layout binds
  { MODKEY,                       XK_BackSpace, zoom,        {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
  { MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[4]} },
  { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[5]} },
  { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} },
  { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[7]} },
  { MODKEY,                       XK_v,      setlayout,      {.v = &layouts[8]} },
  { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[9]} },
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[10]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
  { MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_u,      rotatestack,    {.i = -1 } },
  { MODKEY|ShiftMask,             XK_i,      rotatestack,    {.i = +1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
// general management binds
  { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
  { MODKEY|ControlMask,           XK_b,      toggleextrabar, {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY|ShiftMask|Mod1Mask,    XK_BackSpace,killunsel,    {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY|Mod1Mask|ShiftMask,    XK_x,      quit,           {0} },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
};


/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

