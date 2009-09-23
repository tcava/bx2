#include "irc.h"
#include "ircaux.h"
#include "cset.h"
#include "server.h"

#ifdef HAVE_UNAME
#include <sys/utsname.h>
#endif

char tcl_versionstr[] = "";

BUILT_IN_COMMAND(BX_show_version)
{
const char *nick;
char *version_buf = NULL;
extern char tcl_versionstr[];

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
