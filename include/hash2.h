/*
 * hash2.h: function header file for hash.c
 *
 * Written by Scott H Kilau
 *
 * CopyRight(c) 1997
 *
 * See the COPYRIGHT file, or do a HELP IRCII COPYRIGHT
 *
 * @(#)$Id: hash2.h,v 1.5 2012/08/09 04:11:08 fb Exp $
 */

#ifndef _HASH2_H_
#define _HASH2_H_

#include "struct.h"
#include "whowas.h"
#include "hash.h"

/* Generic List type hash list */
void	BX_add_name_to_genericlist (char *, HashEntry *, unsigned int);
List	*BX_find_name_in_genericlist (char *, HashEntry *, unsigned int, int);
List	*BX_next_namelist(HashEntry *, List *, unsigned int);

void	BX_add_nicklist_to_channellist(Nick *, Channel *);

void	BX_add_whowas_userhost_channel (WhowasList *, WhowasWrapList *);

WhowasList *BX_find_userhost_channel (char *, char *, int, WhowasWrapList *);

int	BX_remove_oldest_whowas_hashlist (WhowasWrapList *, time_t, int);

WhowasList *BX_next_userhost(WhowasWrapList *, WhowasList *);

Nick *BX_find_nicklist_in_channellist(char *, Channel *, int);

void	clear_nicklist_hashtable(Channel *);
void	show_nicklist_hashtable(Channel *);

void show_whowas_hashtable(WhowasWrapList *cptr, char *);
int show_wholeft_hashtable(WhowasWrapList *cptr, time_t ltime, int *total, int *hook, char *);

/* Added to sort a hash'd nicklist and them remove the sorted list */
NickSort *BX_sorted_nicklist(Channel *, int);
void BX_clear_sorted_nicklist(NickSort **);


/* Warning: These numeric values can be taken directly from scripts via
 * the $channel() function - so BEWARE if you change them! */
#define NICKSORT_NORMAL 0
#define NICKSORT_NONE 1
#define NICKSORT_NICK 2
#define NICKSORT_HOST 3
#define NICKSORT_TIME 4
#define NICKSORT_IP 5
#define NICKSORT_STAT 6

Flooding *BX_find_name_in_floodlist(char *, char *, HashEntry *, unsigned int, int);
Flooding *BX_add_name_to_floodlist(char *, char *, char *, HashEntry *, unsigned int);

unsigned long hash_nickname(char *, unsigned int);

int nick_match(Nick *nick, char *mask);

#define BX_add_nicklist_to_channellist add_nicklist_to_channellist
#define BX_find_userhost_channel find_userhost_channel
#define BX_next_userhost next_userhost
#define BX_next_nicklist next_nicklist
#define BX_sorted_nicklist sorted_nicklist
#define BX_clear_sorted_nicklist clear_sorted_nicklist
#define BX_find_nicklist_in_channellist find_nicklist_in_channellist
#define BX_remove_oldest_whowas_hashlist remove_oldest_whowas_hashlist
#define BX_add_whowas_userhost_channel add_whowas_userhost_channel

#endif
