SOURCES = \
  main.c  \
  src/http_server.c \
  libuv-tls/uv_tls.c \
  libuv-tls/tls_engine.c \
  src/http_parser.c      \
  src/connection.c   \
  src/route.c   \
  src/router.c  \
  src/response.c \
  src/utils/dyn_str.c \

server:
	cd libuv-tls/libuv && python gyp_uv.py
	cd libuv-tls/libuv && make -C out
	clang -Wall -g -o server $(SOURCES) -I libuv-tls -I./src -lcrypto -lpthread -lssl -I src/utils \
			 -Llibuv-tls/libuv/out/Debug -luv



clean:
	-rm server 
