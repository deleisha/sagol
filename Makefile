server:
	clang -Wall -g -o server main.c src/http_server.c     \
	         libuv-tls/uv_tls.c libuv-tls/tls_engine.c \
             src/http_parser.c src/connection.c        \
			 -I libuv-tls -I ./src -lcrypto -lpthread -lssl \
			 libuv-tls/libuv/out/Debug/libuv.a



clean:
	-rm server 
