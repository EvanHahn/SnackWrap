ACRAC! After Changing, Run A Command
====================================

The problem
-----------

Sometimes, when you modify a file, you want to run some shell script. Like what
if you're using CoffeeScript:

    coffee foo.coffee

Or LESS CSS?

    lessc styles.less > styles.css

Some of these programs have some awesome CLI "watch" flags, but what if you just
want to watch everything and not worry about it?

The solution: ACRAC!
--------------------

Make a config file (let's call ours `config.txt`) and let's put this inside of
it:

    foo.coffee     coffee foo.coffee
    styles.less    lessc styles.less > styles.css

Save it and then run ACRAC in the terminal:

    $ acrac config.txt

You're done! Now, every time you change any of those files, that shell script
will run without you having to think about it. ACRAC!

More info
---------

* ACRAC is pronounced "ack wrack"; both syllables rhyme with "snack". Very
  important.

* ACRAC was developed by Evan Hahn. It's not required, but if you like ACRAC,
  I'd appreciate it if you gave me some credit for it.

* ACRAC is licensed under the Unlicense. For more info, check out UNLICENSE.txt
  and <http://www.unlicense.org>.

* Enjoy!

