/* @(#)fgetline.c	1.7 04/08/08 Copyright 1986, 1996-2003 J. Schilling */
/*
 *	Copyright (c) 1986, 1996-2003 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "schilyio.h"

/*
 * XXX should we check if HAVE_USG_STDIO is defined and
 * XXX use something line memccpy to speed things up ???
 */

EXPORT int
fgetline(f, buf, len)
	register	FILE	*f;
			char	*buf;
	register	int	len;
{
	register int	c	= '\0';
	register char	*bp	= buf;
	register int	nl	= '\n';

	down2(f, _IOREAD, _IORW);

	for (;;) {
		if ((c = getc(f)) < 0)
			break;
		if (c == nl)
			break;
		if (--len > 0) {
			*bp++ = c;
		} else {
			/*
			 * Read up to end of line
			 */
			while ((c = getc(f)) >= 0 && c != nl)
				;
			break;
		}
	}
	*bp = '\0';
	/*
	 * If buffer is empty and we hit EOF, return EOF
	 */
	if (c < 0 && bp == buf)
		return (c);

	return (bp - buf);
}

EXPORT int
getline(buf, len)
	char	*buf;
	int	len;
{
	return (fgetline(stdin, buf, len));
}
