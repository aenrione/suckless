/* See LICENSE file for copyright and license details. */
/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
/* appearance */
static const unsigned int borderpx = 5; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappih = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv = 20;  /* vert inner gap between windows */
static const unsigned int gappoh =
    20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    20; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int showbar = 1;      /* 0 means no bar */
static const int topbar = 1;       /* 0 means bottom bar */
static const int vertpad = 20;     /* vertical padding of bar */
static const int sidepad = 20;     /* horizontal padding of bar */
static const int horizpadbar = 70; /* horizontal padding for statusbar */
static const int vertpadbar = 12;  /* vertical padding for statusbar */
static const char *fonts[] = {"FiraCode Nerd Font:size=12",
                              "Material Design Icons Desktop:size=12"};
// Set theme
static const char col_bg[] = "#2d3139";
static const char col_gray[] = "#6c7689";
static const char col_white[] = "#D9E0EE";
static const char col_border[] = "#770000";
// static const char col_border[]      = "#96CDFB";
static const char *colors[][3] = {
    [SchemeNorm] = {col_gray, col_bg, col_bg},
    [SchemeSel] = {col_white, col_bg, col_border},
};

// ALT TAB
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 200;	/* tab menu height */

static const char *const autostart[] = {
    "/usr/local/bin/bar/bar.sh",
    NULL, // startus bar
    "nitrogen",
    "--restore",
    NULL, // wallpapers
    "picom",
    "-b",
    "--experimental-backends",
    NULL, // compositer
    NULL  /* terminate */
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {"st",     "-n", "spaud",      "-g",
                        "120x34", "-e", "pulsemixer", NULL};
const char *spcmd3[] = {"st",     "-n", "spmus", "-g",
                        "120x34", "-e", "mocp",  NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"spaud", spcmd2},
    {"spmus", spcmd3},
};

/* tagging */
// static const char *tags[] = {" 1 ", " 2 ", " 3 ", " 4 ", " 5 ",
//                              " 6 ", " 7 ", " 8 ", " 9 "};
static char *tags[] = {"", "", "", "", " ", "", ""};
static const unsigned int ulinepad =
    5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke =
    2; /* thickness / height of the underline */
static const unsigned int ulinevoffset =
    0; /* how far above the bottom of the bar the line should appear */
static const int ulineall =
    0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"VirtualBox Manager", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
    {NULL, "spterm", NULL, SPTAG(0), 1, -1},
    {NULL, "spaud", NULL, SPTAG(1), 1, -1},
    {NULL, "spmus", NULL, SPTAG(2), 1, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]", tile}, /* first entry is default */
    {"[M]", monocle},
    {"|@|", spiral},
    {"D", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"HZ", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-c", "-l",    "20", "-g",
                                 "2",         "-p", "Run :", NULL};
static const char *roficmd[] = {"rofi", "-show", "drun", NULL};
static const char *termcmd[] = {"st", NULL};
static const char *fmcmd[] = {"pcmanfm", NULL};
static const char *webcmd[] = {"$BROWSER", NULL};
static const char *scrotcmd[] = {"maim -s | xclip -sel clip -t image/png", NULL};
static const char *profilecmd[] = {"asusctl profile -n", NULL};

#include "movestack.c"
static Key keys[] = {
    // Apps
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = webcmd}},
    {MODKEY, XK_r, spawn, SHCMD(TERMINAL " -e lfrun")},
    {MODKEY, XK_e, spawn, SHCMD(TERMINAL " -e lvim")},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = scrotcmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = roficmd}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_e, spawn, {.v = fmcmd}},
    {MODKEY | ShiftMask, XK_q, spawn, SHCMD("sysact")},
    {MODKEY | ControlMask, XK_k, spawn, SHCMD("change-kb-layout")},
    {MODKEY | ShiftMask, XK_l, spawn, SHCMD("bitwarden")},
    {MODKEY | ShiftMask, XK_m, spawn, SHCMD(TERMINAL " -e htop")},
    {MODKEY, XK_m, spawn, SHCMD("spotify")},
    {MODKEY, XK_n, spawn, SHCMD(TERMINAL " -e nmtui")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("pactl -- set-sink-volume 0 +5%")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("pactl -- set-sink-volume 0 -5%")},
    {0, XF86XK_AudioMute, spawn, SHCMD("pactl -- set-sink-mute 0 toggle")},
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set 15+")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 15-")},
    {0, XF86XK_KbdBrightnessUp, spawn,
     SHCMD("brightnessctl --device='asus::kbd_backlight' set 1+")},
    {0, XF86XK_KbdBrightnessDown, spawn,
     SHCMD("brightnessctl --device='asus::kbd_backlight' set 1-")},
    {0, XF86XK_Launch3, spawn, SHCMD("asusctl led-mode -n")},
    {0, XF86XK_Launch4, spawn, {.v = profilecmd}},
    {MODKEY, XK_F3, spawn, SHCMD("displayselect")},
    {MODKEY, XK_F9, spawn, SHCMD("dmenumount")},
    {MODKEY, XK_F10, spawn, SHCMD("dmenuumount")},
    {0, XK_Print, spawn, SHCMD("maimpick")},
    {ShiftMask, XK_Print, spawn,
     SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")},
    // PlayerCtl
    {MODKEY, XK_p, spawn, SHCMD("playerctl --player=spotify,%any play-pause")},
    {MODKEY, XK_comma, spawn,
     SHCMD("playerctl --player=spotify,%any previous")},
    {MODKEY, XK_period, spawn, SHCMD("playerctl --player=spotify,%any next")},
    {MODKEY | ShiftMask, XK_comma, spawn,
     SHCMD("playerctl --player=spotify,%any volume 0.1-")},
    {MODKEY | ShiftMask, XK_period, spawn,
     SHCMD("playerctl --player=spotify,%any volume 0.1+")},

    // Layout Controls
    {MODKEY, XK_f, togglefloating, {0}},
  	{Mod1Mask, XK_Tab,  altTabStart, {0} },
  	{MODKEY, XK_Tab,  shiftview, {1} },
    {MODKEY | ShiftMask, XK_Tab, shiftview, {-1}},
    {MODKEY, XK_t, cyclelayout, {.i = +1}}, /* cyclelayout*/
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}}, /* default */
    {MODKEY | ShiftMask, XK_space, togglefullscr, {0}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_c, zoom, {0}},
    //{MODKEY, XK_y, setlayout, {.v = &layouts[2]}},             /* spiral */
    //{MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[3]}}, /* dwindle */
    //{MODKEY, XK_u, setlayout, {.v = &layouts[4]}},             /* deck */
    //{MODKEY | ShiftMask, XK_u, setlayout, {.v = &layouts[5]}}, /* monocle */
    {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},
    // Dwm Stuff
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ControlMask, XK_v, incnmaster, {.i = +1}},
    {MODKEY | ControlMask, XK_h, incnmaster, {.i = -1}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_space, focusstack, {.i = +1}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_r, quit, {1}},
    {MODKEY, XK_o, focusmon, {.i = -1}},
    {MODKEY, XK_i, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_o, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_i, tagmon, {.i = +1}},

    // Tags
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)  TAGKEYS(XK_7, 6)// TAGKEYS(XK_8, 7)
            //TAGKEYS(XK_9, 8)
    // Gaps
    {MODKEY | Mod1Mask, XK_u, incrgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_u, incrgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_i, incrigaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_i, incrigaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_o, incrogaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_o, incrogaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_6, incrihgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_6, incrihgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_7, incrivgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_7, incrivgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_8, incrohgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_8, incrohgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_9, incrovgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_9, incrovgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
