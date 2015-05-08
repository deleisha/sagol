server:
	clang -o server main.c src/http_server.c libuv-tls/uv_tls.c libuv-tls/tls_engine.c \
             src/http_parser.c -I libuv-tls -I ./src -lcrypto -lpthread -lssl libuv-tls/libuv/out/Debug/libuv.a



clean:
	-rm server 
