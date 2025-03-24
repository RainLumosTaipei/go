#!/usr/bin/env bash
# Copyright 2009 The Go Authors. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

# when any of the command fails,
# the current bash will be terminated.
# ensure every cmd is well performed
set -e
# check if the file make.bash is exist
if [ ! -f make.bash ]; then
	echo 'all.bash must be run from $GOROOT/src' 1>&2
	exit 1
fi
# save the old path
OLDPATH="$PATH"

# here use .(source) run the make bash,
# so this is running in current env
# it inherits the vars and functions.
# if make is exit, the whole bash will exit too.
. ./make.bash --no-banner

# note this is using bash to exe the run.bash,
# it will be run in a new sub bash,
# so it will not disturb the current bash
bash run.bash --no-rebuild

# reset the path
PATH="$OLDPATH"
$GOTOOLDIR/dist banner  # print build info
