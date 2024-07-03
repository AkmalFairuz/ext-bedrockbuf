# ext-bedrockbuf
A high performance extension to serialize and deserialize Minecraft: Bedrock Edition packets. 

## !! Experimental !!

## Features
- Compared `unpack()` and `pack()`, this extension encode `short`,`triad`,`int`,`long` ~2x faster
- VarInt and VarLong encoding and decoding is ~8-10x faster
