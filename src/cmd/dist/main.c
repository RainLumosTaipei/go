// Copyright 2012 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "a.h"

int vflag;
char *argv0;

// cmdtab records the available commands.
// alias command table
// this are all cmd for bootstrap, can be called from cmd/dist/dist
static struct {
	char *name; // func name
	void (*f)(int, char**); // func pointer
} cmdtab[] = {
	{"banner", cmdbanner},
	{"bootstrap", cmdbootstrap}, // this is the enter func
	{"clean", cmdclean},
	{"env", cmdenv},
	{"install", cmdinstall},
	{"version", cmdversion},
};

// The OS-specific main calls into the portable code here.
// portable main func
// the real main func is in unix.c/windows.c
void
xmain(int argc, char **argv)
{
	int i;

    // print hint info
	if(argc <= 1)
		usage();

	// nelem is a macro define for counting array nums
	for(i=0; i<nelem(cmdtab); i++) {

	    // find the proper func to call
	    // streq is the portable for strcmp, see a.h
		if(streq(cmdtab[i].name, argv[1])) {

		    // arg num--, arg pointer++
			cmdtab[i].f(argc-1, argv+1);
			return;
		}
	}

	xprintf("unknown command %s\n", argv[1]);
	usage();
}
