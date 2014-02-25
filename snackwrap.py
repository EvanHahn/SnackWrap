#!/usr/bin/env python

import os
import re
from sys import stderr, argv
from glob import iglob
from time import sleep, ctime

HELP = '''
Usage: snackwrap [config-file]

By default, Snackwrap looks for a file called "snackwrap.txt". You can
also specify your own config file:

    snackwrap config.txt
    snackwrap    # looks for snackwrap.txt

On each line of the config, you write the file's path, any amount of
whitespace, and then the shell command to run. For example:

    my_file.c  make test
    src/*.h    make

Empty lines and lines starting with # are ignored.

Enjoy!'''

ERROR_NOT_FOUND = 'Error! Snackwrap config not found.\nAdd the -h flag for help.'

if __name__ == '__main__':

    if len(argv) < 2:
        config_path = 'snackwrap.txt'
    elif (argv[1] == '-h') or (argv[1] == '--help'):
        print HELP
        exit(0)
    else:
        config_path = argv[1]

    if not os.path.isfile(config_path):
        print >> stderr, ERROR_NOT_FOUND
        exit(1)

    patterns = {}

    for line in open(config_path):

        if line[0] == '#' or line[0] == '\n':
            continue

        split = re.split('\s+', line, 1)
        pattern = split[0]
        command = split[1]

        patterns[pattern] = {
            'modified': None,
            'command': command
        }

    print 'Snackwrap found ' + str(len(patterns)) + ' directives.'
    print 'Press ^C to exit...'

    while True:

        for pattern in patterns:

            files = iglob(pattern)

            newest = None
            for file_path in files:
                modified = ctime(os.path.getmtime(file_path))
                if newest is None or modified > newest:
                    newest = modified

            if newest is None:
                continue

            modified = patterns[pattern]['modified']

            if modified is not None and modified < newest:
                command = patterns[pattern]['command']
                os.system(command)

            patterns[pattern]['modified'] = newest

        try:
            sleep(.25)
        except KeyboardInterrupt:
            exit(0)
