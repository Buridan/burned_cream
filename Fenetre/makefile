TARGET   = fenetre

CC       = gcc
CFLAGS   = -std=c99 -Wall -I. -pedantic -g
LINKER   = gcc
LFLAGS   = -Wall -I. -lm -lSDL2

SRCDIR   = src
DATADIR  = data
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DATAS	 := $(wildcard $(SRCDIR)/$(DATADIR)/*)
RM       = rm -rf
MD	 	 := mkdir
CP		 := cp -r 


#TODO : ajouter l'execution automatique
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"
	$(MD) $(BINDIR)/$(DATADIR)
	@$(CP) $(SRCDIR)/$(DATADIR) $(BINDIR)/

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: init
init:	
	@$(MD) $(BINDIR)
	@$(MD) $(OBJDIR)
	@$(MD) $(SRCDIR)

.PHONY: clean
clean:
	@$(RM) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(RM) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
	@$(RM) $(BINDIR)/$(DATADIR)
