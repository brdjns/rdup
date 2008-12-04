/*
 * Copyright (c) 2009 Miek Gieben
 * See LICENSE for the license
 */

#include "rdup-tr.h"

void
usage_tr(FILE *f)
{
        fprintf(f, _("USAGE: %s [OPTION]... \n"), PROGNAME);
	fputs( _("\
Translate rdup output to something else	and optionally filter it\n\
through other processes.\n\
\n\
\n\
    OPTIONS:\n\
        -c\t\tforce output to screen\n\
        -Pcmd,opt1,...,opt5\n\
	    \t\tfilter through cmd\n\
	\t\tthis may be repeated, output will be filtered\n\
	\t\tthrough all commands\n\
	-h\t\tthis help\n\
	-F\t\tinput format: see rdup\n\
	-V\t\tprint version\n\
        -O\t\toutput format: pax, cpio, tar or rdup\n\
	-v\t\tbe more verbose\n\
\n\
Report bugs to <miek@miek.nl>\n\
Licensed under the GPL version 3.\n\
See the file LICENSE in the source distribution of rdup.\n"), f);
}
