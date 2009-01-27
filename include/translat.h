/*
 * Global stuff for translation tables.
 *
 * Tomten, tomten@solace.hsh.se / tomten@lysator.liu.se
 *
 * @(#)$Id: translat.h,v 1.1 2009/01/27 11:01:46 fb Exp $
 */

#ifndef __translat_h_
# define __translat_h_

extern	void	set_translation (void *);
extern	int	translation;
extern	void	translate_from_server (unsigned char *);
extern	void	translate_to_server (unsigned char *);

#endif /* __translat_h_ */
