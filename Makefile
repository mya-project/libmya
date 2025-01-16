SRCDIR = src
BINBASEDIR = bin
BINDIR = $(BINBASEDIR)/release
DEBUGDIR = $(BINBASEDIR)/debug

BIN = libmya.so
CLFAGS = -std=c11 \
	-Wall \
	-Werror \
	-pedantic-errors \
	-O2 \
	-DTCOLORS \
	-I "src/include"

TESTDIR = tests
TESTOBJ = $(BINBASEDIR)/unity.o


SRCLIST = $(shell find $(SRCDIR) -iname '*.c')
OBJLIST = $(subst .c,.o,$(subst $(SRCDIR)/,$(BINDIR)/,$(SRCLIST)))
OBJSUBDIRS = $(dir $(OBJLIST))

TESTLIST = $(shell find $(TESTDIR) -iname "test_*.c")
TESTBINLIST = $(basename $(notdir $(TESTLIST)))

MAKEFLAGS += --no-print-directory

$(BIN): create_bin_dirs $(OBJLIST)
	@echo "$(OBJLIST) -> $(BINDIR)/$(BIN)"
	@$(CC) $(CLFAGS) $(EXTRA_FLAGS) $(OBJLIST) -shared -o "$(BINDIR)/$(BIN)"

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo "$< -> $@"
	@$(CC) $(CLFAGS) $(EXTRA_FLAGS) -c "$<" -o "$@"

.PHONY: debug
debug:
	@$(MAKE) EXTRA_FLAGS=-g3 BINDIR=$(DEBUGDIR)


.PHONY: create_bin_dirs
create_bin_dirs:
	@mkdir -p $(OBJSUBDIRS)

.PHONY: clean
clean:
	rm -rf $(BINBASEDIR)

.PHONY: test-all
test-all: $(TESTBINLIST)

test_%: CLFAGS += -I "$(TESTDIR)/include"
test_%: $(TESTOBJ) create_bin_dirs $(OBJLIST)
	$(eval TEST_MODULE = $(shell find $(TESTDIR) -name "$@.c"))

	@echo "$(TEST_MODULE) -> $@"
	@$(CC) $(CLFAGS) -c "$(TEST_MODULE)" -o "$(BINBASEDIR)/$@.o"

	@$(CC) $(CLFAGS) $(OBJLIST) $(TESTOBJ) "$(BINBASEDIR)/$@.o" -o "$(BINBASEDIR)/$@"

	@./$(BINBASEDIR)/$@

$(TESTOBJ): CLFAGS += -I "$(TESTDIR)/include"
$(TESTOBJ): $(TESTDIR)/unity.c create_bin_dirs
	@echo "$< -> $@"
	@$(CC) $(CLFAGS) -c "$<" -o "$@"
