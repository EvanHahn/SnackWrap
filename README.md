SnackWrap!
==========

The problem
-----------

Sometimes, when you modify a file, you want to run some shell script. Like what
if you're using CoffeeScript:

    coffee foo.coffee

Or LESS CSS?

    lessc styles.less > styles.css

Some of these programs have some awesome CLI "watch" flags, but what if you just
want to watch everything and not worry about it?

The solution: SnackWrap!
------------------------

Make a config file (let's call ours `config.txt`) and let's put this inside of
it:

    # Compile JavaScript
    foo.coffee     coffee -c foo.coffee
    # Compile CSS
    styles.less    lessc styles.less > styles.css

Save it and then run SnackWrap in the terminal:

    $ snackwrap config.txt

You're done! Now, every time you change any of those files, that shell script
will run without you having to think about it. SnackWrap!

Goals
-----

SnackWrap hopes to accomplish the following goals:

* Watch a number of files
* Be able to do whatever you like with them (compile them, compile everything,
  your call)
* Be quickly configurable
* Don't be a daemon

More info
---------

* SnackWrap used to be called ACRAC (After Changing, Run A Command) but that
  got changed because that was stupid.

* SnackWrap was developed by Evan Hahn. It's not required, but if you like
  SnackWrap, I'd appreciate it if you gave me some credit for it.

* SnackWrap is licensed under the Unlicense. For more info, check out
  UNLICENSE.txt and <http://www.unlicense.org>.

* Enjoy!
