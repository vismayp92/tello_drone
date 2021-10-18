CC=gcc
SRCDIR := src
INCDIR := include
BINDIR := bin
TELLOAPP := $(BINDIR)/tello_app

TELLOSRC := $(wildcard $(SRCDIR)/*.c)
TELLOINC := $(wildcard $(INCDIR)/*.h)

$(TELLOAPP): $(TELLOSRC) $(TELLOINC) $(BINDIR)
	$(CC) -I$(INCDIR) $(TELLOSRC) -o $@

$(BINDIR):
	mkdir -p $@

clean:
	rm -rf *.o $(BINDIR)
