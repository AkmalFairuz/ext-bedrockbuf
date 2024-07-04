<?php
function bedrockbuf_readInt(string $data): ?int {}

function bedrockbuf_readLong(string $data): ?int {}

function bedrockbuf_readTriad(string $data): ?int {}

function bedrockbuf_readShort(string $data): ?int {}

function bedrockbuf_readByte(string $data): ?int {}

function bedrockbuf_readLInt(string $data): ?int {}

function bedrockbuf_readLLong(string $data): ?int {}

function bedrockbuf_readLTriad(string $data): ?int {}

function bedrockbuf_readLShort(string $data): ?int {}

function bedrockbuf_readUnsignedShort(string $data): ?int {}

function bedrockbuf_readUnsignedByte(string $data): ?int {}

function bedrockbuf_readLUnsignedShort(string $data): ?int {}

function bedrockbuf_writeInt(int $value): string {}

function bedrockbuf_writeLong(int $value): string {}

function bedrockbuf_writeTriad(int $value): string {}

function bedrockbuf_writeShort(int $value): string {}

function bedrockbuf_writeByte(int $value): string {}

function bedrockbuf_writeLInt(int $value): string {}

function bedrockbuf_writeLLong(int $value): string {}

function bedrockbuf_writeLTriad(int $value): string {}

function bedrockbuf_writeLShort(int $value): string {}

function bedrockbuf_writeFloat(float $value): string {}

function bedrockbuf_writeLFloat(float $value): string {}

function bedrockbuf_writeDouble(float $value): string {}

function bedrockbuf_writeLDouble(float $value): string {}

function bedrockbuf_readFloat(string $data): float {}

function bedrockbuf_readLFloat(string $data): float {}

function bedrockbuf_readDouble(string $data): float {}

function bedrockbuf_readLDouble(string $data): float {}

function bedrockbuf_readVarInt(string $data, int &$offset, bool $is_signed): ?int {}

function bedrockbuf_readVarLong(string $data, int &$offset, bool $is_signed): ?int {}

function bedrockbuf_writeVarInt(int $value, bool $is_signed): string {}

function bedrockbuf_writeVarLong(int $value, bool $is_signed): string {}
