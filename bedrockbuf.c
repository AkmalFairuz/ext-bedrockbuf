/* bedrockbuf extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_bedrockbuf.h"
#include "bedrockbuf_arginfo.h"
#include "Zend/zend_long.h"

#ifndef ZEND_ENABLE_ZVAL_LONG64
# error "ext-bedrockbuf requires a 64-bit build of PHP"
#endif

uint32_t portable_bswap32(uint32_t x) {
    return ((x & 0xff000000) >> 24) |
           ((x & 0x00ff0000) >> 8) |
           ((x & 0x0000ff00) << 8) |
           ((x & 0x000000ff) << 24);
}

uint64_t portable_bswap64(uint64_t x) {
	return ((x & 0xff00000000000000) >> 56) |
		   ((x & 0x00ff000000000000) >> 40) |
		   ((x & 0x0000ff0000000000) >> 24) |
		   ((x & 0x000000ff00000000) >> 8) |
		   ((x & 0x00000000ff000000) << 8) |
		   ((x & 0x0000000000ff0000) << 24) |
		   ((x & 0x000000000000ff00) << 40) |
		   ((x & 0x00000000000000ff) << 56);
}

#define CHECK_DATA_LENGTH(data, length) \
	if(ZSTR_LEN(data) != length) { \
		RETURN_NULL(); \
	}

#define GET_ZDATA_STRING(data, zdata) \
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
		Z_PARAM_STR(zdata) \
	ZEND_PARSE_PARAMETERS_END(); \

#define BEDROCKBUF_READ_INT(name, length, parsing, datatype) \
	PHP_FUNCTION(bedrockbuf_read##name) { \
		zend_string *zdata; \
		GET_ZDATA_STRING(data, zdata); \
		CHECK_DATA_LENGTH(zdata, length); \
		\
		unsigned char *a = (unsigned char *)ZSTR_VAL(zdata); \
		datatype value; \
		value = parsing; \
		RETURN_LONG(value); \
	}

BEDROCKBUF_READ_INT(Int, 4, (a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3], int32_t)
BEDROCKBUF_READ_INT(Long, 8, ((uint64_t)a[0] << 56) | ((uint64_t)a[1] << 48) | ((uint64_t)a[2] << 40) | ((uint64_t)a[3] << 32) | ((uint64_t)a[4] << 24) | ((uint64_t)a[5] << 16) | ((uint64_t)a[6] << 8) | a[7], int64_t)
BEDROCKBUF_READ_INT(Triad, 3, (a[0] << 16) | (a[1] << 8) | a[2], int32_t)
BEDROCKBUF_READ_INT(Short, 2, (a[0] << 8) | a[1], int16_t)
BEDROCKBUF_READ_INT(UnsignedShort, 2, (a[0] << 8) | a[1], uint16_t)
BEDROCKBUF_READ_INT(Byte, 1, a[0], int8_t)
BEDROCKBUF_READ_INT(UnsignedByte, 1, a[0], uint8_t)

BEDROCKBUF_READ_INT(LInt, 4, (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0], int32_t)
BEDROCKBUF_READ_INT(LLong, 8, ((uint64_t)a[7] << 56) | ((uint64_t)a[6] << 48) | ((uint64_t)a[5] << 40) | ((uint64_t)a[4] << 32) | ((uint64_t)a[3] << 24) | ((uint64_t)a[2] << 16) | ((uint64_t)a[1] << 8) | a[0], int64_t)
BEDROCKBUF_READ_INT(LTriad, 3, (a[2] << 16) | (a[1] << 8) | a[0], int32_t)
BEDROCKBUF_READ_INT(LShort, 2, (a[1] << 8) | a[0], int32_t)
BEDROCKBUF_READ_INT(LUnsignedShort, 2, (a[1] << 8) | a[0], uint16_t)

#define BEDROCKBUF_WRITE_INT(name, length, parsing) \
	PHP_FUNCTION(bedrockbuf_write##name) { \
		zend_long value; \
		ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
			Z_PARAM_LONG(value) \
		ZEND_PARSE_PARAMETERS_END(); \
		\
		unsigned char a[length]; \
		parsing; \
		\
		RETURN_STRINGL((char *)a, length); \
	}

BEDROCKBUF_WRITE_INT(Int, 4, a[0] = (value >> 24) & 0xFF; a[1] = (value >> 16) & 0xFF; a[2] = (value >> 8) & 0xFF; a[3] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Long, 8, a[0] = (value >> 56) & 0xFF; a[1] = (value >> 48) & 0xFF; a[2] = (value >> 40) & 0xFF; a[3] = (value >> 32) & 0xFF; a[4] = (value >> 24) & 0xFF; a[5] = (value >> 16) & 0xFF; a[6] = (value >> 8) & 0xFF; a[7] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Triad, 3, a[0] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[2] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Short, 2, a[0] = (value >> 8) & 0xFF; a[1] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Byte, 1, a[0] = value & 0xFF)

BEDROCKBUF_WRITE_INT(LInt, 4, a[3] = (value >> 24) & 0xFF; a[2] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LLong, 8, a[7] = (value >> 56) & 0xFF; a[6] = (value >> 48) & 0xFF; a[5] = (value >> 40) & 0xFF; a[4] = (value >> 32) & 0xFF; a[3] = (value >> 24) & 0xFF; a[2] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LTriad, 3, a[2] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LShort, 2, a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)

#define BEDROCKBUF_READ_FLOAT(name, type, length, bitsize, swap) \
    PHP_FUNCTION(bedrockbuf_read##name) { \
        zend_string *zdata; \
        GET_ZDATA_STRING(data, zdata); \
        CHECK_DATA_LENGTH(zdata, length); \
        \
        unsigned char *a = (unsigned char *)ZSTR_VAL(zdata); \
        type value; \
        memcpy(&value, a, length); \
        \
        if(swap) { \
            value = portable_bswap##bitsize(*(uint##bitsize##_t *)&value); \
        } \
        \
        RETURN_DOUBLE(value); \
    }

BEDROCKBUF_READ_FLOAT(Float, float, 4, 32, 0)
BEDROCKBUF_READ_FLOAT(LFloat, float, 4, 32, 1)
BEDROCKBUF_READ_FLOAT(Double, double, 8, 32, 0)
BEDROCKBUF_READ_FLOAT(LDouble, double, 8, 32, 1)

#define BEDROCKBUF_WRITE_FLOAT(name, type, length, swap) \
    PHP_FUNCTION(bedrockbuf_write##name) { \
        double value; \
        ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
            Z_PARAM_DOUBLE(value) \
        ZEND_PARSE_PARAMETERS_END(); \
        \
        type val = (type)value; \
        unsigned char a[length]; \
        memcpy(a, &val, length); \
        \
        if(swap) { \
            uint##length##_t *p = (uint##length##_t *)a; \
            *p = portable_bswap##length(*p); \
        } \
        \
        RETURN_STRINGL((char *)a, length); \
    }

BEDROCKBUF_WRITE_FLOAT(Float, float, 32, 0)
BEDROCKBUF_WRITE_FLOAT(LFloat, float, 32, 1)
BEDROCKBUF_WRITE_FLOAT(Double, double, 64, 0)
BEDROCKBUF_WRITE_FLOAT(LDouble, double, 64, 1)

PHP_FUNCTION(bedrockbuf_readVarInt) {
    char *data;
    size_t data_len;
    bool is_signed;
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_STRING(data, data_len)
        Z_PARAM_LONG(offset)
        Z_PARAM_BOOL(is_signed)
    ZEND_PARSE_PARAMETERS_END();

    uint32_t value = 0;
    for(uint32_t i = 0; i <= 28; i += 7){
        if(offset >= data_len){
            //zend_throw_exception(NULL, "No bytes left in buffer", 0);
            //return;
            RETURN_NULL();
        }
        unsigned char b = data[offset++];
        value |= ((b & 0x7f) << i);

        if((b & 0x80) == 0){
        	if(is_signed){
                uint32_t raw = value;
                int32_t temp = (((raw << 31) >> 31) ^ raw) >> 1;
                RETURN_LONG(temp ^ (raw & (1 << 31)));
			}
            RETURN_LONG(value);
        }
    }

    //zend_throw_exception(NULL, "VarInt did not terminate after 5 bytes!", 0);
    RETURN_NULL();
}

PHP_FUNCTION(bedrockbuf_readVarLong) {
    char *data;
    size_t data_len;
    bool is_signed;
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_STRING(data, data_len)
        Z_PARAM_LONG(offset)
        Z_PARAM_BOOL(is_signed)
    ZEND_PARSE_PARAMETERS_END();

    uint64_t value = 0;
    for(uint32_t i = 0; i <= 63; i += 7){
        if(offset >= data_len){
            //zend_throw_exception(NULL, "No bytes left in buffer", 0);
            //return;
            RETURN_NULL();
        }
        unsigned char b = data[offset++];
        value |= ((uint64_t)(b & 0x7f) << i);

        if((b & 0x80) == 0){
        	if(is_signed){
        		uint64_t raw = value;
				int64_t temp = (((raw << 63) >> 63) ^ raw) >> 1;
				RETURN_LONG(temp ^ (raw & (1 << 63)));
        	}
            RETURN_LONG(value);
        }
    }

    //zend_throw_exception(NULL, "VarLong did not terminate after 10 bytes!", 0);
    RETURN_NULL();
}

PHP_FUNCTION(bedrockbuf_writeVarInt) {
	zend_long value;
	bool is_signed;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
		Z_PARAM_LONG(value)
		Z_PARAM_BOOL(is_signed)
	ZEND_PARSE_PARAMETERS_END();

	uint32_t raw = value;
	if(is_signed){
		raw = (raw << 1) ^ (raw >> 31);
	}

	char a[5];
	uint32_t temp = raw;
	for(uint32_t i = 0; i < 5; i++){
		if((temp & ~0x7F) != 0){
			a[i] = (temp & 0x7F) | 0x80;
		}else{
			a[i] = temp & 0x7F;
			RETURN_STRINGL(a, i + 1);
		}
		temp >>= 7;
	}
}

PHP_FUNCTION(bedrockbuf_writeVarLong) {
	zend_long value;
	bool is_signed;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
		Z_PARAM_LONG(value)
		Z_PARAM_BOOL(is_signed)
	ZEND_PARSE_PARAMETERS_END();

	uint64_t raw = value;
	if(is_signed){
		raw = (raw << 1) ^ (raw >> 63);
	}

	char a[10];
	uint64_t temp = raw;
	for(uint32_t i = 0; i < 10; i++){
		if((temp & ~0x7F) != 0){
			a[i] = (temp & 0x7F) | 0x80;
		}else{
			a[i] = temp & 0x7F;
			RETURN_STRINGL(a, i + 1);
		}
		temp >>= 7;
	}
}

PHP_MINFO_FUNCTION(bedrockbuf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bedrockbuf support", "enabled");
	php_info_print_table_end();
}

/* {{{ bedrockbuf_module_entry */
zend_module_entry bedrockbuf_module_entry = {
	STANDARD_MODULE_HEADER,
	"bedrockbuf",
	ext_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(bedrockbuf),
	PHP_BEDROCKBUF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BEDROCKBUF
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(bedrockbuf)
#endif
