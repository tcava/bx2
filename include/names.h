/*
 * names.h: Header for names.c
 *
 * Copyright 1997 EPIC Software Labs
 * See the COPYRIGHT file, or do a HELP IRCII COPYRIGHT 
 */

#ifndef __names_h__
#define __names_h__

#include <stdio.h>
#include "alist.h"
#include "levels.h"
#include "struct.h"

#define nick_isop(nick) (nick->chanop == 1)
#define nick_ishalfop(nick) (nick->half_assed == 1)
#define nick_isvoice(nick) (nick->voice == 1)
#define nick_isircop(nick) (/*nick->oper == 1*/0)

typedef struct nick_stru
{
	char 	*nick;		/* nickname of person on channel */
	u_32int_t hash;		/* Hash of the nickname */
	char	*userhost;	/* Their userhost, if we know it */
	short	suspicious;	/* True if the nick might be truncated */
	short	chanop;		/* True if they are a channel operator */
	short	voice;		/* 1 if they are, 0 if theyre not, -1 if uk */
	short	half_assed;	/* 1 if they are, 0 if theyre not, -1 if uk */
	short	ircop;		/* True if they are an ircop */

	struct	nick_stru	*next;	/* XXX */
	char	*ip;
	char	*server;
	time_t	idle_time;
	ShitList *shitlist;
	UserList *userlist;
}	Nick;

typedef struct nicksort_stru
{
	struct	nicksort_stru	*next;
	char	*nick;
	Nick	*nptr;
} NickSort;

typedef	struct	nick_list_stru
{
	Nick	**list;
	int	max;
	int	max_alloc;
	alist_func func;
	hash_type hash;
}	NickList;

/* ChannelList: structure for the list of channels you are current on */
typedef	struct	channel_stru
{
struct	channel_stru *	next;		/* pointer to next channel */
struct	channel_stru *	prev;		/* pointer to previous channel */
	char *		channel;	/* channel name */
	int		server;		/* The server the channel is "on" */
	int		winref;		/* The window the channel is "on" */
	int		curr_count;	/* Current channel precedence */
	int		waiting;	/* Syncing, waiting for names/who */
	NickList	nicks;		/* alist of nicks on channel */

	char 		base_modes[54];	/* Just the modes w/o args */
	int		limit;		/* max users for the channel */
	char *		key;		/* key for this channel */
	char *		modestr;	/* The whole mode string */

	char		chop;		/* true if i'm a channel operator */
	char		voice;		/* true if i'm a channel voice */
	char		half_assed;	/* true if i'm a channel helper */
	Timeval		join_time;	/* When we joined the channel */

	CSetList	*csets;		/* All Channel sets */
	Timeval		limit_time;	/* time of last limit set */
	FILE *		msglog_fp;
	Mask		log_level;
	time_t		max_idle;	/* max idle time for this channel */
	HashEntry	NickListTable[NICKLIST_HASHSIZE];
	BanList		*bans;
	char 		*topic;		/* cached topic */
	char 		*modelock_key;
}	Channel;

	void	add_channel		(Char *, int); 
	void	remove_channel		(Char *, int);
	void	add_to_channel		(Char *, Char *, int, int, int, int, int);
	void	add_userhost_to_channel	(Char *, Char *, int, Char *);
	void	remove_from_channel	(Char *, Char *, int);
	void	rename_nick		(Char *, Char *, int);
	Char *	check_channel_type	(Char *);
	int	im_on_channel		(Char *, int);
	int	is_on_channel		(Char *, Char *);
	int	is_chanop		(Char *, Char *);
	int	is_chanvoice		(Char *, Char *);
	int	is_halfop		(Char *, Char *);
	int	number_on_channel	(Char *, int);
	char *	create_nick_list	(Char *, int);
	char *	create_chops_list	(Char *, int);
	char *	create_nochops_list	(Char *, int);
	int     chanmodetype		(char);
	int	channel_is_syncing	(Char *, int);
	void	channel_not_waiting	(Char *, int); 
	void	update_channel_mode	(Char *, Char *);
	Char *	get_channel_key		(Char *, int);
	Char *	get_channel_mode	(Char *, int);
	int	is_channel_private	(Char *, int);
	int	is_channel_nomsgs	(Char *, int);
	int	is_channel_anonymous	(Char *, int);
	char *	scan_channel		(char *);
	void	list_channels		(void);
	BUILT_IN_KEYBINDING(switch_channels);
	Char *	window_current_channel	(int, int);
	char *	window_all_channels	(int, int);
	int	is_current_channel	(Char *, int);
	void	destroy_server_channels	(int);
	Char *	what_channel		(Char *, int);
	Char *	walk_channels		(int, Char *);
	Char *	fetch_userhost		(int, Char *, Char *);
	int	get_channel_limit	(Char *, int);
	int	get_channel_oper	(Char *, int);
	int	get_channel_voice	(Char *, int);
	int     get_channel_halfop	(Char *, int);
	int	get_channel_winref	(Char *, int);
	void	set_channel_window	(Char *, int, int, int);
	void	move_channel_to_window	(Char *, int, int, int);
	void	reassign_window_channels (int);
	char *	create_channel_list	(int);
	void	cant_join_channel	(Char *, int);
	int	auto_rejoin_callback	(void *);
	void	channel_server_delete	(int);
	void	channel_check_windows	(void);
	void    channels_swap_winrefs (int oldref, int newref);
	Channel	*find_channel		(const char *, int);
	int	traverse_all_channels	(Channel **, int, int);
	Nick *	find_nick		(int, const char *, const char *);
	void	BX_clear_bans		(Channel *);

#define BX_clear_bans clear_bans

#endif /* _NAMES_H_ */
