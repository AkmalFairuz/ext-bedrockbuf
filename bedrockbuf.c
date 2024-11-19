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

#define CHECK_DATA_LENGTH(data, length) \
	if(ZSTR_LEN(data) != length) { \
		RETURN_NULL(); \
	}

#define GET_ZDATA_STRING(zdata) \
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
		Z_PARAM_STR(zdata) \
	ZEND_PARSE_PARAMETERS_END(); \

#define BEDROCKBUF_READ_INT(name, length, parsing, datatype) \
	PHP_FUNCTION(bedrockbuf_read##name) { \
		zend_string *zdata; \
		GET_ZDATA_STRING(zdata); \
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
BEDROCKBUF_READ_INT(Short, 2, (( (a[0] << 8) | a[1]) << 48 >> 48), int64_t)
BEDROCKBUF_READ_INT(UnsignedShort, 2, (a[0] << 8) | a[1], uint16_t)
BEDROCKBUF_READ_INT(Byte, 1, a[0], int8_t)
BEDROCKBUF_READ_INT(UnsignedByte, 1, a[0], uint8_t)

BEDROCKBUF_READ_INT(LInt, 4, (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0], int32_t)
BEDROCKBUF_READ_INT(LLong, 8, ((uint64_t)a[7] << 56) | ((uint64_t)a[6] << 48) | ((uint64_t)a[5] << 40) | ((uint64_t)a[4] << 32) | ((uint64_t)a[3] << 24) | ((uint64_t)a[2] << 16) | ((uint64_t)a[1] << 8) | a[0], int64_t)
BEDROCKBUF_READ_INT(LTriad, 3, (a[2] << 16) | (a[1] << 8) | a[0], int32_t)
BEDROCKBUF_READ_INT(LShort, 2, (( (a[1] << 8) | a[0]) << 48 >> 48), int64_t)
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
BEDROCKBUF_WRITE_INT(Long, 8, a[0] = ((uint64_t)value >> 56) & 0xFF; a[1] = ((uint64_t)value >> 48) & 0xFF; a[2] = ((uint64_t)value >> 40) & 0xFF; a[3] = ((uint64_t)value >> 32) & 0xFF; a[4] = ((uint64_t)value >> 24) & 0xFF; a[5] = ((uint64_t)value >> 16) & 0xFF; a[6] = ((uint64_t)value >> 8) & 0xFF; a[7] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Triad, 3, a[0] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[2] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Short, 2, a[0] = (value >> 8) & 0xFF; a[1] = value & 0xFF)
BEDROCKBUF_WRITE_INT(Byte, 1, a[0] = value & 0xFF)

BEDROCKBUF_WRITE_INT(LInt, 4, a[3] = (value >> 24) & 0xFF; a[2] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LLong, 8, a[7] = ((uint64_t)value >> 56) & 0xFF; a[6] = ((uint64_t)value >> 48) & 0xFF; a[5] = ((uint64_t)value >> 40) & 0xFF; a[4] = ((uint64_t)value >> 32) & 0xFF; a[3] = ((uint64_t)value >> 24) & 0xFF; a[2] = ((uint64_t)value >> 16) & 0xFF; a[1] = ((uint64_t)value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LTriad, 3, a[2] = (value >> 16) & 0xFF; a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)
BEDROCKBUF_WRITE_INT(LShort, 2, a[1] = (value >> 8) & 0xFF; a[0] = value & 0xFF)

union bedrockbuf_FloatToBytes {
    float f;
    uint32_t u;
    unsigned char bytes[4];
};

void bedrockbuf_float_to_char(float value, unsigned char result[4], int little_endian) {
    union bedrockbuf_FloatToBytes converter;
    converter.f = value;
    if (little_endian) {
        result[0] = converter.bytes[0];
        result[1] = converter.bytes[1];
        result[2] = converter.bytes[2];
        result[3] = converter.bytes[3];
    } else {
        result[0] = converter.bytes[3];
        result[1] = converter.bytes[2];
        result[2] = converter.bytes[1];
        result[3] = converter.bytes[0];
    }
}

union bedrockbuf_DoubleToBytes {
    double f;
    uint64_t u;
    unsigned char bytes[8];
};

void bedrockbuf_double_to_char(double value, unsigned char result[8], int little_endian) {
    union bedrockbuf_DoubleToBytes converter;
    converter.f = value;
    if (little_endian) {
        result[0] = converter.bytes[0];
        result[1] = converter.bytes[1];
        result[2] = converter.bytes[2];
        result[3] = converter.bytes[3];
        result[4] = converter.bytes[4];
        result[5] = converter.bytes[5];
        result[6] = converter.bytes[6];
        result[7] = converter.bytes[7];
        result[8] = converter.bytes[8];
    } else {
    	result[0] = converter.bytes[7];
		result[1] = converter.bytes[6];
		result[2] = converter.bytes[5];
		result[3] = converter.bytes[4];
		result[4] = converter.bytes[3];
		result[5] = converter.bytes[2];
		result[6] = converter.bytes[1];
		result[7] = converter.bytes[0];
    }
}

union bedrockbuf_BytesToFloat {
    float f;
    uint32_t u;
    unsigned char bytes[4];
};

float bedrockbuf_char_to_float(const unsigned char bytes[4], int little_endian) {
    union bedrockbuf_BytesToFloat converter;

    if (little_endian) {
        converter.bytes[0] = bytes[0];
        converter.bytes[1] = bytes[1];
        converter.bytes[2] = bytes[2];
        converter.bytes[3] = bytes[3];
    } else {
        converter.bytes[3] = bytes[0];
        converter.bytes[2] = bytes[1];
        converter.bytes[1] = bytes[2];
        converter.bytes[0] = bytes[3];
    }

    return converter.f;
}

union bedrockbuf_BytesToDouble {
    double f;
    uint64_t u;
    unsigned char bytes[8];
};

double bedrockbuf_char_to_double(const unsigned char bytes[8], int little_endian) {
    union bedrockbuf_BytesToDouble converter;

    if (little_endian) {
        converter.bytes[0] = bytes[0];
        converter.bytes[1] = bytes[1];
        converter.bytes[2] = bytes[2];
        converter.bytes[3] = bytes[3];
        converter.bytes[4] = bytes[4];
        converter.bytes[5] = bytes[5];
        converter.bytes[6] = bytes[6];
        converter.bytes[7] = bytes[7];
    } else {
        converter.bytes[7] = bytes[0];
        converter.bytes[6] = bytes[1];
        converter.bytes[5] = bytes[2];
        converter.bytes[4] = bytes[3];
        converter.bytes[3] = bytes[4];
        converter.bytes[2] = bytes[5];
        converter.bytes[1] = bytes[6];
        converter.bytes[0] = bytes[7];
    }

    return converter.f;
}

#define BEDROCKBUF_READ_FLOAT(name, length, swap) \
    PHP_FUNCTION(bedrockbuf_read##name) { \
        zend_string *zdata; \
        GET_ZDATA_STRING(zdata); \
        CHECK_DATA_LENGTH(zdata, length); \
        \
        unsigned char *a = (unsigned char *)ZSTR_VAL(zdata); \
        double value; \
        if (length == 8) { \
			value = bedrockbuf_char_to_double(a, swap); \
		} else { \
			value = bedrockbuf_char_to_float(a, swap); \
		} \
		RETURN_DOUBLE(value); \
    }

BEDROCKBUF_READ_FLOAT(Float, 4, 0)
BEDROCKBUF_READ_FLOAT(LFloat, 4, 1)
BEDROCKBUF_READ_FLOAT(Double, 8, 0)
BEDROCKBUF_READ_FLOAT(LDouble, 8, 1)

#define BEDROCKBUF_WRITE_FLOAT(name, length, swap) \
    PHP_FUNCTION(bedrockbuf_write##name) { \
        double value; \
        ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
            Z_PARAM_DOUBLE(value) \
        ZEND_PARSE_PARAMETERS_END(); \
        \
        if (length == 8) { \
        	unsigned char a[8]; \
			bedrockbuf_double_to_char(value, a, swap); \
			RETURN_STRINGL(a, length); \
        } \
        float value2 = (float)value; \
        unsigned char a[4]; \
        bedrockbuf_float_to_char(value2, a, swap); \
		RETURN_STRINGL(a, length); \
    }

BEDROCKBUF_WRITE_FLOAT(Float, 4, 0)
BEDROCKBUF_WRITE_FLOAT(LFloat, 4, 1)
BEDROCKBUF_WRITE_FLOAT(Double, 8, 0)
BEDROCKBUF_WRITE_FLOAT(LDouble, 8, 1)

int32_t VarIntDecodeZigZag32(uint32_t n) {
	return (n >> 1) ^ -(n & 1);
}

int64_t VarIntDecodeZigZag64(uint64_t n) {
	return (n >> 1) ^ -(n & 1);
}

uint32_t VarIntEncodeZigZag32(int32_t n) {
	return (n << 1) ^ (n >> 31);
}

uint64_t VarIntEncodeZigZag64(int64_t n) {
	return (n << 1) ^ (n >> 63);
}

PHP_FUNCTION(bedrockbuf_readVarInt) {
    zend_string *zdata;
    bool is_signed;
    zval *offsetz = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_STR(zdata)
        Z_PARAM_ZVAL(offsetz)
        Z_PARAM_BOOL(is_signed)
    ZEND_PARSE_PARAMETERS_END();

    char *data = ZSTR_VAL(zdata);
    size_t data_len = (size_t)ZSTR_LEN(zdata);
	zend_long offsetLval = Z_LVAL_P(Z_REFVAL_P(offsetz));
    uint32_t offset = (uint32_t)offsetLval;
    uint32_t value = 0;
    for(uint32_t i = 0; i <= 28; i += 7){
        if(offset >= data_len){
            //zend_throw_exception(NULL, "No bytes left in buffer", 0);
            RETURN_NULL();
        }
        unsigned char b = data[offset++];
        value |= ((b & 0x7f) << i);

        if((b & 0x80) == 0){
       		ZEND_TRY_ASSIGN_REF_LONG(offsetz, (zend_long)offset);
        	if(is_signed){
                RETURN_LONG(VarIntDecodeZigZag32(value));
			}
            RETURN_LONG(value);
        }
    }

    //zend_throw_exception(NULL, "VarInt did not terminate after 5 bytes!", 0);
    RETURN_NULL();
}

PHP_FUNCTION(bedrockbuf_readVarLong) {
    zend_string *zdata;
    bool is_signed;
    zval *offsetz = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_STR(zdata)
        Z_PARAM_ZVAL(offsetz)
        Z_PARAM_BOOL(is_signed)
    ZEND_PARSE_PARAMETERS_END();

    char *data = ZSTR_VAL(zdata);
    size_t data_len = (size_t)ZSTR_LEN(zdata);
	zend_long offsetLval = Z_LVAL_P(Z_REFVAL_P(offsetz));
    uint32_t offset = (uint32_t)offsetLval;
    uint64_t value = 0;
    for(uint32_t i = 0; i <= 63; i += 7){
        if(offset >= data_len){
            //zend_throw_exception(NULL, "No bytes left in buffer", 0);
            RETURN_NULL();
        }
        unsigned char b = data[offset++];
        value |= ((uint64_t)(b & 0x7f) << i);

        if((b & 0x80) == 0){
        	ZEND_TRY_ASSIGN_REF_LONG(offsetz, (zend_long)offset);
        	if(is_signed){
        		RETURN_LONG(VarIntDecodeZigZag64(value));
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

	uint32_t raw = (uint32_t)value;
	if(is_signed){
		raw = VarIntEncodeZigZag32(raw);
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

	uint64_t raw = (uint64_t)value;
	if(is_signed){
		raw = VarIntEncodeZigZag64(raw);
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

PHP_FUNCTION(bedrockbuf_writeVector3IntLE) {
    zend_long x, y, z;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_LONG(x)
        Z_PARAM_LONG(y)
        Z_PARAM_LONG(z)
    ZEND_PARSE_PARAMETERS_END();

    unsigned char a[12];
    a[0] = x & 0xFF;
    a[1] = (x >> 8) & 0xFF;
    a[2] = (x >> 16) & 0xFF;
    a[3] = (x >> 24) & 0xFF;
    a[4] = y & 0xFF;
    a[5] = (y >> 8) & 0xFF;
    a[6] = (y >> 16) & 0xFF;
    a[7] = (y >> 24) & 0xFF;
    a[8] = z & 0xFF;
    a[9] = (z >> 8) & 0xFF;
    a[10] = (z >> 16) & 0xFF;
    a[11] = (z >> 24) & 0xFF;

    RETURN_STRINGL(a, 12);
}

PHP_FUNCTION(bedrockbuf_writeVector3FloatLE) {
    double x, y, z;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    unsigned char a[12];
    bedrockbuf_float_to_char((float)x, a, 1);
    bedrockbuf_float_to_char((float)y, a + 4, 1);
    bedrockbuf_float_to_char((float)z, a + 8, 1);

    RETURN_STRINGL(a, 12);
}

PHP_FUNCTION(bedrockbuf_readVector3IntLE) {
    zend_string *zdata;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_STR(zdata)
    ZEND_PARSE_PARAMETERS_END();

    CHECK_DATA_LENGTH(zdata, 12);

    unsigned char *a = (unsigned char *)ZSTR_VAL(zdata);
    int32_t x = (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
    int32_t y = (a[7] << 24) | (a[6] << 16) | (a[5] << 8) | a[4];
    int32_t z = (a[11] << 24) | (a[10] << 16) | (a[9] << 8) | a[8];

    array_init(return_value);
    add_next_index_long(return_value, x);
    add_next_index_long(return_value, y);
    add_next_index_long(return_value, z);

    RETURN_ARR(Z_ARRVAL_P(return_value));
}

PHP_FUNCTION(bedrockbuf_readVector3FloatLE) {
    zend_string *zdata;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_STR(zdata)
    ZEND_PARSE_PARAMETERS_END();

    CHECK_DATA_LENGTH(zdata, 12);

    unsigned char *a = (unsigned char *)ZSTR_VAL(zdata);
    float x = bedrockbuf_char_to_float(a, 1);
    float y = bedrockbuf_char_to_float(a + 4, 1);
    float z = bedrockbuf_char_to_float(a + 8, 1);

    array_init(return_value);
    add_next_index_double(return_value, x);
    add_next_index_double(return_value, y);
    add_next_index_double(return_value, z);

    RETURN_ARR(Z_ARRVAL_P(return_value));
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
