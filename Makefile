SRCDIR = src
BINDIR = bin
BIN = libmya.so
CLFAGS = -std=c11 \
	-Wall \
	-Werror \
	-pedantic-errors \
	-I "src/include"

TESTDIR = tests
TESTOBJ = $(BINDIR)/unity.o


SRCLIST = $(shell find $(SRCDIR) -iname '*.c')
OBJLIST = $(subst .c,.o, \
		$(subst \
				$(SRCDIR)/, \
				$(BINDIR)/, \
				$(SRCLIST) \
		) \
)
OBJSUBDIRS = $(dir $(OBJLIST))

TESTLIST = $(shell find $(TESTDIR) -iname "test_*.c")
TESTBINLIST = $(basename $(notdir $(TESTLIST)))

$(BIN): create_bin_dirs $(OBJLIST)
	@$(CC) $(CLFAGS) $(OBJLIST) -o "$(BINDIR)/$(BIN)"

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo "$< -> $@"
	@$(CC) $(CLFAGS) -c "$<" -o "$@"


.PHONY: create_bin_dirs
create_bin_dirs:
	@mkdir -p $(OBJSUBDIRS)

.PHONY: clean
clean:
	rm -rf $(BINDIR)

.PHONY: test-all
test-all: $(TESTBINLIST)

test_%: CLFAGS += -I "$(TESTDIR)/include"
test_%: $(TESTOBJ) create_bin_dirs $(OBJLIST)
	$(eval TEST_MODULE = $(shell find $(TESTDIR) -name "$@.c"))

	@echo "$(TEST_MODULE) -> $@"
	@$(CC) $(CLFAGS) -c "$(TEST_MODULE)" -o "$@.o"

	@$(CC) $(CLFAGS) $(OBJLIST) $(TESTOBJ) "$@.o" -o "$(BINDIR)/$@"

	@./$(BINDIR)/$@

$(TESTOBJ): CLFAGS += -I "$(TESTDIR)/include"
$(TESTOBJ): $(TESTDIR)/unity.c create_bin_dirs
	@echo "$< -> $@"
	@$(CC) $(CLFAGS) -c "$<" -o "$@"
