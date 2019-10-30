/* See LICENSE file for copyright and license details. */
/* (find-file "~/suckless/dwm/config.h") (shell-command "cp ~/suckless/dwm/config.h ~/config_github/app/dwm/config.h_arco_linux") */
/* (find-file "~/config_github/app/dwm/config.h_arco_linux") (shell-command "cp ~/config_github/app/dwm/config.h_arco_linux ~/suckless/dwm/config.h") */
/* shell_script/ 참조할 것. (shell-command "ln ~/config_github/app/dwm/config.h_arco_linux ~/suckless/dwm/config.h") 이것을 실행하므로서 하드링크로 sync하는 것이 가능하기를 기대한다. */
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_orange[]      = "#FB8200";

static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_orange,  col_orange },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */
void
shiftview(const Arg *arg) {
	Arg shifted;

	if(arg->i > 0) // left circular shift
		shifted.ui = (selmon->tagset[selmon->seltags] << arg->i)
		   | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - arg->i));

	else // right circular shift
		shifted.ui = selmon->tagset[selmon->seltags] >> (- arg->i)
		   | selmon->tagset[selmon->seltags] << (LENGTH(tags) + arg->i);

	view(&shifted);
}

/* tagging */

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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },    /* first entry is default */
	{ "[M]",	monocle },
 	//{ "[@]",	spiral }, /*둘 중에 한가지를 선택함 select in */
  { "[@]",	dwindle }, /* dwindle을 나는 선택함 */
	{ "|M|",	centeredmaster },
	{ "><>",	NULL },    /* no layout function means floating behavior */
	{ ">M>",	centeredfloatingmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "combi", NULL }; // ~/.config/rofi/config 에 설정을 가지고 있다.
/* static const char *roficmd[] = { "rofi", "-combi", "window,run", "-show", "combi", NULL }; */
//static const char *terminal_dwm[] = { "st", NULL }; // 투명한 기능에 st 매력적이다. xcompmgr compmgr 을 설치후 st로 변경함
static const char *terminal_dwm[] = { "urxvt", NULL }; // 투명한 기능에 매력적이다.
//static const char *fm_dwm[] = { "st", "-T", "emacsQ", "-e", "$HOME/.bin/emacsQ", NULL }; // 투명한 emacsQ 일단 File Manager.
static const char *fm_dwm[] = { "urxvt", "-e", "sh", "-c", "$HOME/.bin/emacsq", NULL }; // 투명한 emacsQ 일단 File Manager.
//static const char *urxvt_fmcmd[] = { "urxvt", "-e", "sh", "-c", "$HOME/.bin/emacsQ", NULL }; // 투명한 emacsQ 일단 File Manager.
//static const char *urxvt_fmcmd[] = { "urxvt", "-e", "sh", "-c", "ranger", NULL }; // 투명한 ranger 일단 File Manager.
//static const char *urxvt_fmcmd[] = { "urxvt", "-e", "sh", "-c", "mc" NULL }; // 투명한 mc 대안 File Manager.
// 대안의 항목 dolphin, spacefm, worker, mc, ranger, lscd, hunter ...

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,                       XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,                       XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,		movestack,	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,		movestack,	{.i = -1 } },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY,                       XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,                       XK_l,		setmfact,	{.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_i,		incnmaster,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,	{.i = -1 } },
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY,			XK_f,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY,			XK_o,		setlayout,	{.v = &layouts[5]} },
	//{ MODKEY,			XK_Tab,		view,		{0} }, /*macosx와 유사한 Tab이동을 만들기전의 원본 아래의 4줄이 대신 추가됨*/
	//{ MODKEY,			XK_~,		shiftview,	{ .i = 1 } }, /* 탭의 위의 키는 tag가 전진함.*/
	//{ MODKEY,			XK_`,		view,		{0} }, /* 탭의 위의 키 + Shift키는 이전의 tag로 전환함.*/
	{ MODKEY,			XK_Tab,		focusstack,	{.i = +1 } }, /* Mac의 CMD+Tab과 동일한 기능*/
	//{ MODKEY|ShiftMask,		XK_Tab,		focusstack,	{.i = -1 } }, /* Mac의 CMD+Shift+Tab과 동일한 기능*/ /*사용되지만 일단 임시로 다른 것으로 전환*/
	{ MODKEY|ShiftMask,		XK_Tab,		shiftview,	{ .i = 1 } }, /* 임시로 이전탭으로 전환하는 것으로 일단 사용함.*/ /*사용되지만 일단 임시로 다른 것으로 전환*/
	{ MODKEY,			XK_backslash,	view,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(			XK_1,			0)
	TAGKEYS(			XK_2,			1)
	TAGKEYS(			XK_3,			2)
	TAGKEYS(			XK_4,			3)
	TAGKEYS(			XK_5,			4)
	TAGKEYS(			XK_6,			5)
	TAGKEYS(			XK_7,			6)
	TAGKEYS(			XK_8,			7)
	TAGKEYS(			XK_9,			8)
	{ MODKEY,                       XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_F2,		quit,		{0} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_d,		spawn,		{ .v = dmenucmd } },
	{ MODKEY,			XK_r,		spawn,		{ .v = roficmd } },
  { MODKEY,         			XK_Return,		spawn,		{ .v = terminal_dwm } },    /* 투명터미널 실행을 목적 */
  { MODKEY|ShiftMask,			XK_Return,		spawn,		{ .v = fm_dwm } }, /* 투명파일매니져 열어냄 */
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = 1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = dmenucmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

