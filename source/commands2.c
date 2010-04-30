#include "irc.h"
#include "ircaux.h"
#include "cset.h"
#include "server.h"
#include "vars.h"
#include "hook.h"
#include "misc.h"
#include "window.h"

#ifdef HAVE_UNAME
#include <sys/utsname.h>
#endif

char tcl_versionstr[] = "";

BUILT_IN_COMMAND(BX_show_version)
{
const char *nick;
char *version_buf = NULL;

#ifdef HAVE_UNAME
struct utsname buf;
	
	uname(&buf);
	malloc_strcpy(&version_buf, (const char *) stripansicodes(convert_output_format(fget_string_var(FORMAT_VERSION_FSET), "%s %s %s %s %s", irc_version, internal_version, buf.sysname, buf.release?buf.release:empty_string, tcl_versionstr)));
#else
	malloc_strcpy(&version_buf, (const char *) stripansicodes(convert_output_format(fget_string_var(FORMAT_VERSION_FSET), "%s %s %s %s %s", irc_version, internal_version, "unknown", tcl_versionstr, empty_string)));
#endif
	if (args && *args)
		nick = next_arg(args, &args);
	else
		nick = get_echannel_by_refnum(0);
/* XXX	send_text(from_server, nick, version_buf, "PRIVMSG", 1, 0); */
	send_text(from_server, nick, version_buf, "PRIVMSG", 1);
	new_free(&version_buf);
}

BUILT_IN_COMMAND(tog_fprot)
{
static int here = 0;

	
	if (args && *args)
	{
		if (!my_stricmp(args, "ON"))
			here = 0;
		else if (!my_stricmp(args, "OFF"))
			here = 1;
		else
			return;
	}		

	if (here)
	{
		set_int_var(CTCP_FLOOD_PROTECTION_VAR, 0);
		set_int_var(FLOOD_PROTECTION_VAR, 0);
		here = 0;
	} else
	{
		set_int_var(CTCP_FLOOD_PROTECTION_VAR, 1);
		set_int_var(FLOOD_PROTECTION_VAR, 1);
		here = 1;
	}
	bitchsay("Toggled flood protection - [%s]", on_off(here));
}

BUILT_IN_COMMAND(do_toggle)
{
#ifndef BITCHX_LITE
if (!args || !*args)
{
#ifdef ONLY_STD_CHARS

put_it("%s", convert_output_format("%G-----------%K[ %WBitchX %wToggles %K]%G----------------------------------------------", NULL));
put_it("%s", convert_output_format("%G|   %Cauto_ns%clookup %K[%W$[-3]0%K]    %Cctcp_f%clood_protection %K[%W$[-3]1%K]    %Cbeep%c        %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(AUTO_NSLOOKUP_VAR)), on_off(get_int_var(CTCP_FLOOD_PROTECTION_VAR)), on_off(get_int_var(BEEP_VAR))));
put_it("%s", convert_output_format("%G|   %Cpub%cflood      %K[%W$[-3]0%K]    %Cflood_p%crotection      %K[%W$[-3]1%K]    %Ckickf%clood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(PUBFLOOD_VAR)), on_off(get_int_var(FLOOD_PROTECTION_VAR)), on_off(get_int_var(KICKFLOOD_VAR))));
put_it("%s", convert_output_format("%G|   %Cdcc_a%cutoget   %K[%W$[-3]0%K]    %Cflood_k%cick            %K[%W$[-3]1%K]    %Cmsg%clog      %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(DCC_AUTOGET_VAR)), on_off(get_int_var(FLOOD_KICK_VAR)), on_off(get_int_var(MSGLOG_VAR))));
put_it("%s", convert_output_format("%G|   %Cll%cook         %K[%W$[-3]0%K]    %Cdeop%cflood             %K[%W$[-3]1%K]    %Cjoin%cflood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(LLOOK_VAR)), on_off(get_int_var(DEOPFLOOD_VAR)), on_off(get_int_var(JOINFLOOD_VAR))));
put_it("%s", convert_output_format("%G|   %Cauto_w%chowas   %K[%W$[-3]0%K]    %Cverb%cose_ctcp          %K[%W$[-3]1%K]    %Cnickfl%cood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(AUTO_WHOWAS_VAR)), on_off(get_int_var(CTCP_VERBOSE_VAR)), on_off(get_int_var(NICKFLOOD_VAR))));
put_it("%s", convert_output_format("%G|   %Ccl%coak         %K[%W$[-3]0%K]    %Coper%cview              %K[%W$[-3]1%K]    %Cshit%clist    %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(CLOAK_VAR)), on_off(get_int_var(OV_VAR)), on_off(get_int_var(SHITLIST_VAR))));
put_it("%s", convert_output_format("%G|   %Ckick_o%cps      %K[%W$[-3]0%K]    %Cannoy%c_kick            %K[%W$[-3]1%K]    %Cuser%clist    %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(KICK_OPS_VAR)), on_off(get_int_var(ANNOY_KICK_VAR)), on_off(get_int_var(USERLIST_VAR))));
put_it("%s", convert_output_format("%G|   %Chack%cing       %K[%W$[-3]0%K]    %Cnick_c%completion       %K[%W$[-3]1%K]    %Cauto_r%cejoin %K[%W$[-3]2%K]","%s %s %s", on_off(get_int_var(HACKING_VAR)),on_off(get_int_var(NICK_COMPLETION_VAR)), on_off((get_int_var(AUTO_REJOIN_VAR)?1:0)) ));
put_it("%s", convert_output_format("%K|   %Caop           %K[%W$[-3]0%K]    %Cauto_aw%cay             %K[%W$[-3]1%K]    %Cauto_rec%conn %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(AOP_VAR))),on_off((get_int_var(AUTO_AWAY_VAR))), on_off(get_int_var(AUTO_RECONNECT_VAR))));
put_it("%s", convert_output_format("%K|   %Cbitch         %K[%W$[-3]0%K]    %Cdcc_f%cast              %K[%W$[-3]1%K]    %Ckick_if_ban %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(BITCH_VAR))),on_off((get_int_var(DCC_FAST_VAR))), on_off(get_int_var(KICK_IF_BANNED_VAR))));
put_it("%s", convert_output_format("%g|   %Cftp_g%crab      %K[%W$[-3]0%K]    %Cmircs                 %K[%W$[-3]1%K]    %Chttp%c_grab   %K[%W$[-3]2%K]", "%s %s", on_off((get_int_var(FTP_GRAB_VAR))),on_off((get_int_var(MIRCS_VAR))),on_off((get_int_var(HTTP_GRAB_VAR))) ));
put_it("%s", convert_output_format("%G|   %Cdisp%clay_ansi  %K[%W$[-3]0%K]    %Wtype /toggle <setting>         %Clog         %K[%W$[-3]1%K]", "%s %s", on_off((get_int_var(DISPLAY_ANSI_VAR))),on_off((get_int_var(LOG_VAR))) ));

#else

put_it("%s", convert_output_format("%GÚÄÄÄÄÄ---%gÄ%G-%K[ %WBitchX %wToggles %K]-%gÄÄ%G-%gÄÄÄÄÄÄ---%KÄ%g--%KÄÄ%g-%KÄÄÄÄÄÄÄÄÄ--- --  - --- -- -", NULL));
put_it("%s", convert_output_format("%G³   %Cauto_ns%clookup %K[%W$[-3]0%K]    %Cctcp_f%clood_protection %K[%W$[-3]1%K]    %Cbeep%c        %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(AUTO_NSLOOKUP_VAR)), on_off(get_int_var(CTCP_FLOOD_PROTECTION_VAR)), on_off(get_int_var(BEEP_VAR))));
put_it("%s", convert_output_format("%G³   %Cpub%cflood      %K[%W$[-3]0%K]    %Cflood_p%crotection      %K[%W$[-3]1%K]    %Ckickf%clood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(PUBFLOOD_VAR)), on_off(get_int_var(FLOOD_PROTECTION_VAR)), on_off(get_int_var(KICKFLOOD_VAR))));
put_it("%s", convert_output_format("%g³   %Cdcc_a%cutoget   %K[%W$[-3]0%K]    %Cflood_k%cick            %K[%W$[-3]1%K]    %Cmsg%clog      %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(DCC_AUTOGET_VAR)), on_off(get_int_var(FLOOD_KICK_VAR)), on_off(get_int_var(MSGLOG_VAR))));
put_it("%s", convert_output_format("%G³   %Cll%cook         %K[%W$[-3]0%K]    %Cdeop%cflood             %K[%W$[-3]1%K]    %Cjoin%cflood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(LLOOK_VAR)), on_off(get_int_var(DEOPFLOOD_VAR)), on_off(get_int_var(JOINFLOOD_VAR))));
put_it("%s", convert_output_format("%g|   %Cauto_w%chowas   %K[%W$[-3]0%K]    %Cverb%cose_ctcp          %K[%W$[-3]1%K]    %Cnickfl%cood   %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(AUTO_WHOWAS_VAR)), on_off(get_int_var(CTCP_VERBOSE_VAR)), on_off(get_int_var(NICKFLOOD_VAR))));
put_it("%s", convert_output_format("%G:   %Ccl%coak         %K[%W$[-3]0%K]    %Coper%cview              %K[%W$[-3]1%K]    %Cshit%clist    %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(CLOAK_VAR)), on_off(get_int_var(OV_VAR)), on_off(get_int_var(SHITLIST_VAR))));
put_it("%s", convert_output_format("%G:   %Ckick_o%cps      %K[%W$[-3]0%K]    %Cannoy%c_kick            %K[%W$[-3]1%K]    %Cuser%clist    %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(KICK_OPS_VAR)), on_off(get_int_var(ANNOY_KICK_VAR)), on_off(get_int_var(USERLIST_VAR))));
put_it("%s", convert_output_format("%K|   %Chack%cing       %K[%W$[-3]0%K]    %Cnick_c%completion       %K[%W$[-3]1%K]    %Cauto_rej%coin %K[%W$[-3]2%K]", "%s %s %s", on_off(get_int_var(HACKING_VAR)),on_off(get_int_var(NICK_COMPLETION_VAR)), on_off((get_int_var(AUTO_REJOIN_VAR)?1:0)) ));
put_it("%s", convert_output_format("%K:   %Caop           %K[%W$[-3]0%K]    %Cauto_aw%cay             %K[%W$[-3]1%K]    %Cauto_rec%conn %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(AOP_VAR)?1:0)),on_off((get_int_var(AUTO_AWAY_VAR))), on_off(get_int_var(AUTO_RECONNECT_VAR))));
put_it("%s", convert_output_format("%K:   %Cbitch         %K[%W$[-3]0%K]    %Cdcc_f%cast              %K[%W$[-3]1%K]    %Ckick_if_ban %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(BITCH_VAR))),on_off((get_int_var(DCC_FAST_VAR))), on_off(get_int_var(KICK_IF_BANNED_VAR))));
put_it("%s", convert_output_format("%g:   %Cftp_g%crab      %K[%W$[-3]0%K]    %Cmircs                 %K[%W$[-3]1%K]    %Chttp%c_grab   %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(FTP_GRAB_VAR))),on_off((get_int_var(MIRCS_VAR))),on_off((get_int_var(HTTP_GRAB_VAR))) ));
put_it("%s", convert_output_format("%K:   %Cdisp%clay_ansi  %K[%W$[-3]0%K]    %Ctimestamp             %K[%W$[-3]1%K]    %Clog         %K[%W$[-3]2%K]", "%s %s %s", on_off((get_int_var(DISPLAY_ANSI_VAR))),on_off((get_int_var(TIMESTAMP_VAR))), on_off((get_int_var(LOG_VAR))) ));
put_it("%s", convert_output_format("%K:                             %Wtype /toggle <setting> ", NULL));

#endif
} 
else
{
	char *arg;
	while ((arg = next_arg(args, &args)))
	{
		int var = -1;
		char *str = NULL;
		upper(arg);
		
		if (!my_strnicmp(arg, "auto_nslookup", 7))
		{
			var = AUTO_NSLOOKUP_VAR;
			str = "$G %cToggled %GAuto-NSlookup %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "pubflood", 3))
		{
			var = PUBFLOOD_VAR;
			str = "$G %cToggled %GPub Flood %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "dcc_autoget", 5))
		{
			var = DCC_AUTOGET_VAR;
			str = "$G %cToggled %GDCC Auto Get %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "llook", 2))
		{
			var = LLOOK_VAR;
			str = "$G %cToggled %GLink Look %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "auto_whowas", 6))
		{
			var = AUTO_WHOWAS_VAR;
			str = "$G %cToggled %GAuto-WhoWas %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "cloak", 2))
		{
			var = CLOAK_VAR;
			str = "$G %cToggled %GCloaking %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "kick_ops", 6))
		{
			var = KICK_OPS_VAR;
			str = "$G %cToggled %GKick Ops %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "ctcp_flood_protection", 6))
		{
			var = CTCP_FLOOD_PROTECTION_VAR;
			str = "$G %cToggled %GCtcp Flood Protection %K[%W$[-3]0%K]","%s";
		} else if (!my_strnicmp(arg, "flood_protection",7))
		{
			var = FLOOD_PROTECTION_VAR;
			str = "$G %cToggled %GFlood Protection %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "flood_kick", 7))
		{
			var = FLOOD_KICK_VAR;
			str = "$G %cToggled %GFlood Kicks %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "deopflood",4))
		{
			var = DEOPFLOOD_VAR;
			str = "$G %cToggled %GDeOp Flood %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "verbose_ctcp",4))
		{
			var = CTCP_VERBOSE_VAR;
			str = "$G %cToggled %GVerbose CTCP %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "operview", 4))
		{
			int ov_mode = get_int_var(OV_VAR);
			var = OV_VAR;
// XXX			setup_ov_mode(ov_mode, 0, current_window->log);
			str = "$G %cToggled %GOper View %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "annoy_kick",4))
		{
			var = ANNOY_KICK_VAR;
			str = "$G %cToggled %GAnnoy Kicks %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "beep",4))
		{
			var = BEEP_VAR;
			str = "$G %cToggled %GBeep %K[%W$[-3]0%K]";

		} else if (!my_strnicmp(arg, "kickflood",5))
		{
			var = KICKFLOOD_VAR;
			str = "$G %cToggled %GKick Flood %K[%W$[-3]0%K]","%s";
		} else if (!my_strnicmp(arg, "msglog", 3))
		{
			var = MSGLOG_VAR;
			str = "$G %cToggled %GMSG log %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "joinflood", 4))
		{
			var = JOINFLOOD_VAR;
			str = "$G %cToggled %GJoin Flood %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "nickflood", 6))
		{
			var = NICKFLOOD_VAR;
			str = "$G %cToggled %GNick Flood %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "shitlist", 4))
		{
			var = SHITLIST_VAR;
			str = "$G %cToggled %GShitList %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "userlist", 4))
		{
			var = USERLIST_VAR;
			str = "$G %cToggled %GUserList %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "hacking", 4))
		{
			var = HACKING_VAR;
			str = "$G %cToggled %GHacking %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "auto_rejoin", 8))
		{
			var = AUTO_REJOIN_VAR;
			str = "$G %cToggled %GAuto_Rejoin %K[%W$[-3]0%K]","%s";
		} else if (!my_strnicmp(arg, "nick_completion", 6))
		{
			var = NICK_COMPLETION_VAR;
			str = "$G %cToggled %GNick Completion %K[%W$[-3]0%K]","%s";
		} else if (!my_strnicmp(arg, "aop", 3))
		{
			var = AOP_VAR;
			str = "$G %cToggled %GAOP %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "auto_away", 7))
		{
			var = AUTO_AWAY_VAR;
			str = "$G %cToggled %GAuto Away %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "auto_reconnect", 8))
		{
			var = AUTO_RECONNECT_VAR;
			str = "$G %cToggled %GAuto Reconnect %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "mircs", 5))
		{
			var = MIRCS_VAR;
			str = "$G %cToggled %GmIRC Color %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "bitch", 5))
		{
			var = BITCH_VAR;
			str = "$G %cToggled %GBitch %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "dcc_fast", 5))
		{
			var = DCC_FAST_VAR;
			str = "$G %cToggled %GDCC fast %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "kick_if_banned", 5))
		{
			var = KICK_IF_BANNED_VAR;
			str = "$G %cToggled %GKick banned Users %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "ftp_grab", 5))
		{
			var = FTP_GRAB_VAR;
			str = "$G %cToggled %GFTP grab %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "timestamp", 3))
		{
			var = TIMESTAMP_VAR;
			str = "$G %cToggled %GTimestamps %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "http_grab", 4))
		{
			var = HTTP_GRAB_VAR;
			str = "$G %cToggled %GHTTP grab %K[%W$[-3]0%K]";
		} else if (!my_strnicmp(arg, "display_ansi", 4))
		{
			set_int_var(DISPLAY_ANSI_VAR, get_int_var(DISPLAY_ANSI_VAR)?0:1);
// XXX			toggle_reverse_status(current_window, NULL, get_int_var(DISPLAY_ANSI_VAR));
			if (do_hook(SET_LIST, "%s %s", arg, on_off(get_int_var(DISPLAY_ANSI_VAR))))
				put_it("%s", convert_output_format("$G %cToggled %GAnsi Display %K[%W$[-3]0%K]", "%s", on_off(get_int_var(DISPLAY_ANSI_VAR)) ));
#if 0
			set_input_prompt(current_window, empty_string, 0);
			set_input_prompt(current_window, get_string_var(INPUT_PROMPT_VAR), 0);
			status_update(1);
#endif
			continue;
		} else if (!my_strnicmp(arg, "log", 3))
		{
			int old_window_display = window_display;
			var = LOG_VAR;
			str = "$G %cToggled %GLogging %K[%W$[-3]0%K]";
			window_display = 0;
// XXX			logger(current_window, NULL, get_int_var(LOG_VAR)?0:1);
			window_display = old_window_display;
		}
		if (var != -1)
			set_int_var(var, get_int_var(var)?0:1);
		if (str)
		{
			if (do_hook(SET_LIST, "%s %s", arg, on_off(get_int_var(var))))
				put_it("%s", convert_output_format(str, "%s", on_off(get_int_var(var)) ));
		}
		if (var == -1)
			bitchsay("Unknown /toggle [%s]", arg);
	}
}
#endif
}

BUILT_IN_COMMAND(serv_stat)
{
extern long nick_collisions, oper_kills, serv_fakes, serv_unauth, serv_split;
extern long serv_rejoin, client_connects, serv_rehash, client_exits,serv_klines;
extern long client_floods, client_invalid, stats_req, client_bot, client_bot_alarm;
extern long oper_requests, serv_squits, serv_connects;
#ifdef ONLY_STD_CHARS

put_it("%s", convert_output_format("%G-----------%K[ %WServer %wStats %K]%G----------------------------------------------", NULL));
put_it("%s", convert_output_format("%G| %CN%cick Collisions %K[%W$[-4]0%K]    %CO%cper Kills   %K[%W$[-4]1%K]", "%d %d", nick_collisions, oper_kills));
put_it("%s", convert_output_format("%G| %CF%cake Modes      %K[%W$[-4]0%K]    %CU%cnauth       %K[%W$[-4]1%K]", "%d %d",serv_fakes, serv_unauth));
put_it("%s", convert_output_format("%G| %CH%cigh Traffic    %K[%W$[-4]0%K]    %CN%corm Traffic %K[%W$[-4]1%K]", "%d %d",serv_split, serv_rejoin));
put_it("%s", convert_output_format("%G| %CT%cotal Clients   %K[%W$[-4]0%K]    %CS%cerv rehash  %K[%W$[-4]1%K]", "%d %d",client_connects, serv_rehash));
put_it("%s", convert_output_format("%G| %CC%client exits    %K[%W$[-4]0%K]    %CK%c-lines adds %K[%W$[-4]1%K]", "%d %d",client_exits, serv_klines));
put_it("%s", convert_output_format("%G| %CC%client Floods   %K[%W$[-4]0%K]    %CS%ctats reqs   %K[%W$[-4]1%K]", "%d %d",client_floods, stats_req));
put_it("%s", convert_output_format("%G| %CI%cnvalid User    %K[%W$[-4]0%K]    %CO%cper Reqs    %K[%W$[-4]1%K]", "%d %d",client_invalid, oper_requests));
put_it("%s", convert_output_format("%G| %CP%cossible Bots   %K[%W$[-4]0%K]    %CB%cot Alarms   %K[%W$[-4]1%K]", "%d %d",client_bot, client_bot_alarm));
put_it("%s", convert_output_format("%G| %CS%cerv Squits     %K[%W$[-4]0%K]    %CS%cerv Connect %K[%W$[-4]1%K]", "%d %d",serv_squits, serv_connects));

#else

put_it("%s", convert_output_format("%GÚÄÄÄÄÄ---%gÄ%G-%K[ %WServer %wStats %K]-%gÄÄ%G-%gÄÄÄÄÄÄ---%KÄ%g--%KÄÄ%g-%KÄÄÄÄÄÄÄÄÄ--- --  - --- -- -", NULL));
put_it("%s", convert_output_format("%G³ %CN%cick Collisions %K[%W$[-4]0%K]    %CO%cper Kills   %K[%W$[-4]1%K]", "%l %l", nick_collisions, oper_kills));
put_it("%s", convert_output_format("%G³ %CF%cake Modes      %K[%W$[-4]0%K]    %CU%cnauth       %K[%W$[-4]1%K]", "%l %l",serv_fakes, serv_unauth));
put_it("%s", convert_output_format("%g³ %CH%cigh Traffic    %K[%W$[-4]0%K]    %CN%corm Traffic %K[%W$[-4]1%K]", "%l %l",serv_split, serv_rejoin));
put_it("%s", convert_output_format("%G³ %CT%cotal Clients   %K[%W$[-4]0%K]    %CS%cerv rehash  %K[%W$[-4]1%K]", "%l %l",client_connects, serv_rehash));
put_it("%s", convert_output_format("%g| %CC%client exits    %K[%W$[-4]0%K]    %CK%c-lines adds %K[%W$[-4]1%K]", "%l %l",client_exits, serv_klines));
put_it("%s", convert_output_format("%G: %CC%client Floods   %K[%W$[-4]0%K]    %CS%ctats reqs   %K[%W$[-4]1%K]", "%l %l",client_floods, stats_req));
put_it("%s", convert_output_format("%G: %CI%cnvalid User    %K[%W$[-4]0%K]    %CO%cper Reqs    %K[%W$[-4]1%K]", "%l %l",client_invalid, oper_requests));
put_it("%s", convert_output_format("%K| %CP%cossible Bots   %K[%W$[-4]0%K]    %CB%cot Alarms   %K[%W$[-4]1%K]", "%l %l",client_bot, client_bot_alarm));
put_it("%s", convert_output_format("%g: %CS%cerv Squits     %K[%W$[-4]0%K]    %CS%cerv Connect %K[%W$[-4]1%K]", "%l %l",serv_squits, serv_connects));

#endif

}

BUILT_IN_COMMAND(jnw)
{
	char	*channel;
	int	hidden = 0;

	if ((channel = next_arg(args, &args)))
	{
		Window	*tmp;

		if (*channel == '-' && !my_stricmp(channel, "-hide"))
		{
			if (!(channel = next_arg(args, &args)))
				return;
			hidden = 1;
		}
		if ((tmp = new_window(current_window->screen)))
		{
			int	server = from_server;

			from_server = tmp->server;
			if (!is_channel(channel))
				channel = make_channel(channel);
			if (channel)
			{
				add_waiting_channel(tmp, channel);
				send_to_server("JOIN %s%s%s", channel, args?space:empty_string, args?args:empty_string);
			}
			from_server = server;
			if (hidden)
				hide_window(tmp);
			update_all_windows();
		}
	}
}
