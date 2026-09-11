CC       ?= gcc
CFLAGS   ?= -O2 -Wall -Wextra -fPIC -std=c11
CPPFLAGS += -Iinclude
AR       ?= ar

BUILD    := build
LIB      := $(BUILD)/libsable.a
EXAMPLE  := $(BUILD)/ppm_demo

LIB_SRCS := $(wildcard src/*.c)
LIB_OBJS := $(patsubst src/%.c,$(BUILD)/obj/%.o,$(LIB_SRCS))

EX_SRCS  := $(wildcard examples/*.c)
EX_OBJS  := $(patsubst examples/%.c,$(BUILD)/examples/%.o,$(EX_SRCS))

CC_VERSION   := $(shell $(CC) --version 2>/dev/null)
CC_IS_CLANG  := $(findstring clang,$(CC_VERSION))

ifneq (,$(CC_IS_CLANG))
  OVERRIDE_FLAG := -Wno-initializer-overrides
else
  OVERRIDE_FLAG := -Wno-override-init -Wno-override-init-side-effects
endif

CFLAGS ?= -O2 -Wall -Wextra -fPIC -std=c11
CFLAGS += $(OVERRIDE_FLAG)

all: $(LIB)

$(LIB): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD)/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

example: $(EXAMPLE)

$(EXAMPLE): $(EX_OBJS) $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(EX_OBJS) $(LIB) -lm -o $@

$(BUILD)/examples/%.o: examples/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: example
	@cd $(BUILD) && ./ppm_demo

clean:
	rm -rf $(BUILD)

.PHONY: all example run clean