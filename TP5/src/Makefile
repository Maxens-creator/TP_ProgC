CC ?= gcc
CFLAGS ?= -Wall -Wextra -Wpedantic -g

COBJS ?= client.o
SOBJS ?= serveur.o

SERVER = serveur
CLIENT = client

.PHONY: all clean

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(COBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER) $(CLIENT) $(SOBJS) $(COBJS)