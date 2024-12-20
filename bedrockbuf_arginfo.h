#define DEFINE_READ_INT_FUNC(name) \
    ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 1, IS_LONG, 0) \
        ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0) \
    ZEND_END_ARG_INFO() \
    ZEND_FUNCTION(name);

DEFINE_READ_INT_FUNC(bedrockbuf_readInt)
DEFINE_READ_INT_FUNC(bedrockbuf_readLong)
DEFINE_READ_INT_FUNC(bedrockbuf_readTriad)
DEFINE_READ_INT_FUNC(bedrockbuf_readShort)
DEFINE_READ_INT_FUNC(bedrockbuf_readByte)
DEFINE_READ_INT_FUNC(bedrockbuf_readLInt)
DEFINE_READ_INT_FUNC(bedrockbuf_readLLong)
DEFINE_READ_INT_FUNC(bedrockbuf_readLTriad)
DEFINE_READ_INT_FUNC(bedrockbuf_readLShort)
DEFINE_READ_INT_FUNC(bedrockbuf_readUnsignedShort)
DEFINE_READ_INT_FUNC(bedrockbuf_readUnsignedByte)
DEFINE_READ_INT_FUNC(bedrockbuf_readLUnsignedShort)

#define DEFINE_WRITE_INT_FUNC(name) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 1, IS_STRING, 0) \
		ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_WRITE_INT_FUNC(bedrockbuf_writeInt)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeLong)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeTriad)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeShort)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeByte)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeLInt)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeLLong)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeLTriad)
DEFINE_WRITE_INT_FUNC(bedrockbuf_writeLShort)

#define DEFINE_WRITE_FLOAT_FUNC(name) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 1, IS_STRING, 0) \
		ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_WRITE_FLOAT_FUNC(bedrockbuf_writeFloat)
DEFINE_WRITE_FLOAT_FUNC(bedrockbuf_writeLFloat)
DEFINE_WRITE_FLOAT_FUNC(bedrockbuf_writeDouble)
DEFINE_WRITE_FLOAT_FUNC(bedrockbuf_writeLDouble)

#define DEFINE_READ_FLOAT_FUNC(name) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 1, IS_DOUBLE, 0) \
		ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_READ_FLOAT_FUNC(bedrockbuf_readFloat)
DEFINE_READ_FLOAT_FUNC(bedrockbuf_readLFloat)
DEFINE_READ_FLOAT_FUNC(bedrockbuf_readDouble)
DEFINE_READ_FLOAT_FUNC(bedrockbuf_readLDouble)

#define DEFINE_READ_VAR_INT_FUNC(name) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 3, IS_LONG, 0) \
		ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0) \
		ZEND_ARG_TYPE_INFO(1, offset, IS_LONG, 0) \
		ZEND_ARG_TYPE_INFO(0, is_signed, _IS_BOOL, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

#define DEFINE_WRITE_VAR_INT_FUNC(name) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 2, IS_STRING, 0) \
		ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0) \
		ZEND_ARG_TYPE_INFO(0, is_signed, _IS_BOOL, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_READ_VAR_INT_FUNC(bedrockbuf_readVarInt)
DEFINE_READ_VAR_INT_FUNC(bedrockbuf_readVarLong)
DEFINE_WRITE_VAR_INT_FUNC(bedrockbuf_writeVarInt)
DEFINE_WRITE_VAR_INT_FUNC(bedrockbuf_writeVarLong)

#define DEFINE_WRITE_VECTOR3_FUNC(name, type) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 3, IS_STRING, 0) \
		ZEND_ARG_TYPE_INFO(0, x, type, 0) \
		ZEND_ARG_TYPE_INFO(0, y, type, 0) \
		ZEND_ARG_TYPE_INFO(0, z, type, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_WRITE_VECTOR3_FUNC(bedrockbuf_writeVector3IntLE, IS_LONG)
DEFINE_WRITE_VECTOR3_FUNC(bedrockbuf_writeVector3FloatLE, IS_DOUBLE)

#define DEFINE_READ_VECTOR3_FUNC(name, type) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_##name, 0, 1, IS_ARRAY, 0) \
		ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0) \
	ZEND_END_ARG_INFO() \
	ZEND_FUNCTION(name);

DEFINE_READ_VECTOR3_FUNC(bedrockbuf_readVector3IntLE, IS_STRING)
DEFINE_READ_VECTOR3_FUNC(bedrockbuf_readVector3FloatLE, IS_STRING)

static const zend_function_entry ext_functions[] = {
	ZEND_FE(bedrockbuf_readInt, arginfo_bedrockbuf_readInt)
	ZEND_FE(bedrockbuf_readLong, arginfo_bedrockbuf_readLong)
	ZEND_FE(bedrockbuf_readTriad, arginfo_bedrockbuf_readTriad)
	ZEND_FE(bedrockbuf_readShort, arginfo_bedrockbuf_readShort)
	ZEND_FE(bedrockbuf_readByte, arginfo_bedrockbuf_readByte)
	ZEND_FE(bedrockbuf_readFloat, arginfo_bedrockbuf_readFloat)
	ZEND_FE(bedrockbuf_readLFloat, arginfo_bedrockbuf_readLFloat)
	ZEND_FE(bedrockbuf_readDouble, arginfo_bedrockbuf_readDouble)
	ZEND_FE(bedrockbuf_readLDouble, arginfo_bedrockbuf_readLDouble)
	ZEND_FE(bedrockbuf_writeInt, arginfo_bedrockbuf_writeInt)
	ZEND_FE(bedrockbuf_writeLong, arginfo_bedrockbuf_writeLong)
	ZEND_FE(bedrockbuf_writeTriad, arginfo_bedrockbuf_writeTriad)
	ZEND_FE(bedrockbuf_writeShort, arginfo_bedrockbuf_writeShort)
	ZEND_FE(bedrockbuf_writeByte, arginfo_bedrockbuf_writeByte)
	ZEND_FE(bedrockbuf_writeFloat, arginfo_bedrockbuf_writeFloat)
	ZEND_FE(bedrockbuf_writeLFloat, arginfo_bedrockbuf_writeLFloat)
	ZEND_FE(bedrockbuf_writeDouble, arginfo_bedrockbuf_writeDouble)
	ZEND_FE(bedrockbuf_writeLDouble, arginfo_bedrockbuf_writeLDouble)
	ZEND_FE(bedrockbuf_readVarInt, arginfo_bedrockbuf_readVarInt)
	ZEND_FE(bedrockbuf_readVarLong, arginfo_bedrockbuf_readVarLong)
	ZEND_FE(bedrockbuf_writeVarInt, arginfo_bedrockbuf_writeVarInt)
	ZEND_FE(bedrockbuf_writeVarLong, arginfo_bedrockbuf_writeVarLong)
	ZEND_FE(bedrockbuf_readLLong, arginfo_bedrockbuf_readLLong)
    ZEND_FE(bedrockbuf_writeLLong, arginfo_bedrockbuf_writeLLong)
    ZEND_FE(bedrockbuf_readLTriad, arginfo_bedrockbuf_readLTriad)
    ZEND_FE(bedrockbuf_writeLTriad, arginfo_bedrockbuf_writeLTriad)
    ZEND_FE(bedrockbuf_readLShort, arginfo_bedrockbuf_readLShort)
    ZEND_FE(bedrockbuf_writeLShort, arginfo_bedrockbuf_writeLShort)
    ZEND_FE(bedrockbuf_readUnsignedShort, arginfo_bedrockbuf_readUnsignedShort)
    ZEND_FE(bedrockbuf_readUnsignedByte, arginfo_bedrockbuf_readUnsignedByte)
    ZEND_FE(bedrockbuf_readLUnsignedShort, arginfo_bedrockbuf_readLUnsignedShort)
    ZEND_FE(bedrockbuf_readLInt, arginfo_bedrockbuf_readLInt)
    ZEND_FE(bedrockbuf_writeLInt, arginfo_bedrockbuf_writeLInt)
	ZEND_FE(bedrockbuf_readVector3IntLE, arginfo_bedrockbuf_readVector3IntLE)
	ZEND_FE(bedrockbuf_writeVector3IntLE, arginfo_bedrockbuf_writeVector3IntLE)
	ZEND_FE(bedrockbuf_readVector3FloatLE, arginfo_bedrockbuf_readVector3FloatLE)
	ZEND_FE(bedrockbuf_writeVector3FloatLE, arginfo_bedrockbuf_writeVector3FloatLE)
	ZEND_FE_END
};
