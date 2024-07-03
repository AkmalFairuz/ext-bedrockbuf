PHP_ARG_ENABLE([bedrockbuf],
  [whether to enable bedrockbuf support],
  [AS_HELP_STRING([--enable-bedrockbuf],
    [Enable bedrockbuf support])],
  [no])

if test "$PHP_BEDROCKBUF" != "no"; then
  AC_DEFINE(HAVE_BEDROCKBUF, 1, [ Have bedrockbuf support ])


  PHP_NEW_EXTENSION(bedrockbuf, bedrockbuf.c, $ext_shared,, -DXXH_INLINE_ALL)
  PHP_ADD_INCLUDE($ext_builddir/bedrockbuf)
fi
