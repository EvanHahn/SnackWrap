Snackwrap
=========

After changing a file, run a command.

Let's say I want to run a build script every time I save a file in *src/*. I also want to scream every time you edit a forbidden file.

I'll make *snackwrap.txt*:

    src/*           ./build.sh
    forbidden.txt   echo "AUUUGHH!!"

Now, I run Snackwrap.

    $ snackwrap

Now, every time I change a file in *src/*, I'll run *build.sh*. And every time I edit *forbidden.txt*, I'll scream.

You can run Snackwrap in a few ways:

    $ python snackwrap.py
    $ ./snackwrap.py
    $ # put snackwrap.py somewhere in your PATH and type snackwrap

For more help:

    $ snackwrap -h
