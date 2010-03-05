#ifndef __struct_h__
#define __struct_h__

#include <stdio.h>
#include "hash.h"
#include "window.h"

typedef struct wset_array_struc
{
	char *name;
	int type;
	int offset;
	int format_offset;
	void (*func) (Window *, char *, int);
	int flag;
}	WSetArray;

typedef struct _cset_stru
{
	struct _cset_stru *next;
	char	*channel;
	int	set_aop;		/* channel specific /set */
	int	set_annoy_kick;		/* channel specific /set */
	int	set_ainv;		/* channel specific /set */
	int	set_auto_join_on_invite;
	int	set_auto_rejoin;	/* channel specific /set */
	int	set_ctcp_flood_ban;
	int	set_deop_on_deopflood;	/* channel specific /set */
	int	set_deop_on_kickflood;	/* channel specific /set */
	int	set_deopflood;		/* channel specific /set */
	int	set_deopflood_time;	/* channel specific /set */
	int	set_hacking;		/* channel specific /set */
	int	set_kick_on_deopflood;	/* channel specific /set */
	int	set_kick_on_joinflood;
	int	set_kick_on_kickflood;	/* channel specific /set */
	int	set_kick_on_nickflood;	/* channel specific /set */
	int	set_kick_on_pubflood;	/* channel specific /set */
	int	set_kickflood;		/* channel specific /set */
	int	set_kickflood_time;	/* channel specific /set */
	int	set_nickflood;		/* channel specific /set */
	int	set_nickflood_time;	/* channel specific /set */
	int	set_joinflood;		/* channel specific /set */
	int	set_joinflood_time;	/* channel specific /set */
	int	set_pubflood;		/* channel specific /set */
	int	set_pubflood_ignore;	/* channel ignore time val */
	int	set_pubflood_time;	/* channel specific /set */
	int	set_userlist;		/* channel specific /set */
	int	set_shitlist;		/* channel specific /set */
	int	set_lame_ident;		/* channel specific /set */
	int	set_lamelist;		/* channel specific /set */
	int	set_kick_if_banned;     /* channel specific /set */
	int	bitch_mode;		/* channel specific /set */
	int	compress_modes;		/* channel specific /set */
	int	set_kick_ops;
	int	set_auto_limit;
	int	channel_log;
	int	set_bantime;
	char	*channel_log_file;
	char	*chanmode;
	unsigned long channel_log_level;
	char	*log_level;
} CSetList;

typedef struct cset_array_struc
{
	char *name;
	int type;
	int offset;
	void (*func) (struct cset_array_struc *, CSetList *);
	int flag;
}	CSetArray;

typedef struct WinSetStru
{
/* These are copied over from /set's */
	char	*status_mode;
	char	*status_topic;
	char	*status_umode;
	char	*status_hold_lines;
	char	*status_hold;
	char	*status_voice;
	char	*status_channel;
	char	*status_notify;
	char	*status_oper_kills;
	char	*status_lag;
	char	*status_mail;
	char	*status_query;
	char	*status_server;
	char	*status_clock;
	char	*status_users;
	char	*status_away;
	char	*status_dcccount;
	char	*status_cdcccount;
	char	*status_chanop;
	char	*status_cpu_saver;
	char	*status_msgcount;
	char	*status_nick;	
	char	*status_flag;
	char	*status_halfop;
							
/* These are the various formats from a window make_status() creates these */ 
	char    *mode_format;
	char    *umode_format;
	char    *topic_format;
	char    *query_format;
	char    *clock_format;
	char    *hold_lines_format;
	char    *channel_format;
	char    *mail_format;
	char    *server_format;
	char    *notify_format;
	char    *kills_format;
	char    *status_users_format;
	char    *lag_format;
	char	*cpu_saver_format;
	char	*msgcount_format;
	char	*dcccount_format;
	char	*cdcc_format;
	char	*nick_format;
	char	*flag_format;
	char	*away_format;
	
//#define MAX_FUNCTIONS		36
	char	*status_user_formats0;
	char	*status_user_formats1;
	char	*status_user_formats2;
	char	*status_user_formats3;
	char	*status_user_formats4;
	char	*status_user_formats5;
	char	*status_user_formats6;
	char	*status_user_formats7;
	char	*status_user_formats8;
	char	*status_user_formats9;
	char	*status_user_formats10;
	char	*status_user_formats11;
	char	*status_user_formats12;
	char	*status_user_formats13;
	char	*status_user_formats14;
	char	*status_user_formats15;
	char	*status_user_formats16;
	char	*status_user_formats17;
	char	*status_user_formats18;
	char	*status_user_formats19;
	char	*status_user_formats20;
	char	*status_user_formats21;
	char	*status_user_formats22;
	char	*status_user_formats23;
	char	*status_user_formats24;
	char	*status_user_formats25;
	char	*status_user_formats26;
	char	*status_user_formats27;
	char	*status_user_formats28;
	char	*status_user_formats29;
	char	*status_user_formats30;
	char	*status_user_formats31;
	char	*status_user_formats32;
	char	*status_user_formats33;
	char	*status_user_formats34;
	char	*status_user_formats35;
	char	*status_user_formats36;
	char	*status_user_formats37;
	char	*status_user_formats38;
	char	*status_user_formats39;
	char	*status_scrollback;
	char	*status_window;
		
	char	*status_line[3];	/* The status lines string current display */
	char	*status_format[4];	/* holds formated status info from build_status */
	char	*format_status[4];	/* holds raw format for window from /set */	

	char	*window_special_format;
}	 WSet;

typedef struct
{
	char *name;
	u_32int_t hash;
	int type;
	int integer;
	char *string;
/* XXX */
//	void (*func)(Window *, char *, int);
	void (*func)(void *);
	char int_flags;
	unsigned short flags;
} BX_IrcVariable;

/* BanList: structure for the list of bans on a channel */
typedef struct ban_stru
{
	struct	ban_stru	*next;  /* pointer to next ban entry */
	char	*ban;			/* the ban */
	char	*setby;			/* person who set the ban */
	int	sent_unban;		/* flag if sent unban or not */
	time_t	sent_unban_time;	/* sent unban's time */
	time_t	time;			/* time ban was set */
	int	count;
}	BanList;

typedef struct chan_flags_stru {

	unsigned int got_modes : 1;
	unsigned int got_who : 1;
	unsigned int got_bans : 1;
	unsigned int got_exempt : 1;
} chan_flags;

#if 0
/* ChannelList: structure for the list of channels you are current on */
typedef	struct	channel_stru
{
	struct	channel_stru	*next;	/* pointer to next channel entry */
	char	*channel;		/* channel name */
	Window	*window;		/* the window that the channel is "on" */
	int	refnum;			/* window refnum */
	int	server;			/* server index for this channel */
	u_long	mode;			/* Current mode settings for channel */
	u_long	i_mode;			/* channel mode for cached string */
	char	*s_mode;		/* cached string version of modes */
	char	*topic;
	int	topic_lock;
		
	char 	*modelock_key;
	long	modelock_val;
	
	int	limit;			/* max users for the channel */
	time_t	limit_time;		/* time of last limit set */
	char	*key;			/* key for this channel */
	char	chop;			/* true if you are chop */
	char	hop;			/* true if you are a half op */
	char	voice;			/* true if you are voice */
	char	bound;			/* true if channel is bound */
	char	*chanpass;		/* if TS4 then this has the channel pass */
	char	connected;		/* true if this channel is actually connected */

	
	HashEntry	NickListTable[NICKLIST_HASHSIZE];

	chan_flags	flags;


	time_t	max_idle;		/* max idle time for this channel */
	int	tog_limit;
	int	check_idle;		/* toggle idle check */
	int	do_scan;		/* flag for checking auto stuff */
	struct timeval	channel_create;		/* time for channel creation */
	struct timeval	join_time;		/* time of last join */


	int	stats_ops;		/* total ops I have seen in channel */
	int	stats_dops;		/* total dops I have seen in channel */
	int	stats_bans;		/* total bans I have seen in channel */
	int	stats_unbans;		/* total unbans I have seen in channel */

	int	stats_sops;		/* total server ops I have seen in channel */
	int	stats_sdops;		/* total server dops I have seen in channel */
	int	stats_shops;
	int	stats_sdehops;
	int	stats_sebans;
	int	stats_sunebans;
	int	stats_sbans;		/* total server bans I have seen in channel */
	int	stats_sunbans;		/* total server unbans I have seen in channel */

	int	stats_topics;		/* total topics I have seen in channel */
	int	stats_kicks;		/* total kicks I have seen in channel */
	int	stats_pubs;		/* total pubs I have seen in channel */
	int	stats_parts;		/* total parts I have seen in channel */
	int	stats_signoffs;		/* total signoffs I have seen in channel */
	int	stats_joins;		/* total joins I have seen in channel */
	int	stats_ebans;
	int	stats_unebans;
	int	stats_chanpass;
	int	stats_hops;
	int	stats_dhops;
		
	CSetList *csets;		/* All Channel sets */

	
	
	int	msglog_on;
	FILE	*msglog_fp;
	char	*logfile;
	unsigned long log_level;
		
	int	totalnicks;		/* total number of users in channel */
	int	maxnicks;		/* max number of users I have seen */
	time_t	maxnickstime;		/* time of max users */

	int	totalbans;		/* total numbers of bans on channel */


	BanList	*bans;			/* pointer to list of bans on channel */
	BanList	*exemptbans;		/* pointer to list of bans on channel */
	int	maxbans;		/* max number of bans I have seen */
	time_t	maxbanstime;		/* time of max bans */
	struct {
		char 	*op;
		int	type;
	} cmode[4];

	char	*mode_buf;
	int	mode_len;	

}	ChannelList;
#endif

#endif
