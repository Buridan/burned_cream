TARGET   = fenetre

CC 		=	$(LINCC)
LINCC = gcc
W64CC = i686-w64-mingw32-gcc 
W32CC = i586-mingw32msvc-gcc

CFLAGS   = -std=c99 -Wall -I. -pedantic -g `pkg-config gtk+-3.0 --cflags`
LINKER   = gcc
LFLAGS   = -Wall -I. -lm -lgcc `pkg-config gtk+-3.0 --libs`

SRCDIR   = src
DATADIR  = data
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DATAS	 := $(wildcard $(SRCDIR)/$(DATADIR)/*)
RM       = rm -rf
MD	 	 := mkdir -p
CP		 := cp -r 

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"
	@$(MD) $(BINDIR)/$(DATADIR)
	@$(CP) $(SRCDIR)/$(DATADIR) $(BINDIR)/

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: init
init:	
	@$(MD) $(BINDIR)
	@$(MD) $(OBJDIR)
	@$(MD) $(SRCDIR)
	@$(MD) $(SRCDIR)/$(DATADIR)

.PHONY: clean
clean:
	@$(RM) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(RM) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
	@$(RM) $(BINDIR)/$(DATADIR)
