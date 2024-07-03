/* bedrockbuf extension for PHP */

#ifndef PHP_BEDROCKBUF_H
# define PHP_BEDROCKBUF_H

extern zend_module_entry bedrockbuf_module_entry;
# define phpext_bedrockbuf_ptr &bedrockbuf_module_entry

# define PHP_BEDROCKBUF_VERSION "1.0.0-dev"

# if defined(ZTS) && defined(COMPILE_DL_BEDROCKBUF)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_BEDROCKBUF_H */
