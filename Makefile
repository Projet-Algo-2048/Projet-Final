################# VARIABLE ###################
NAME = 2048
INPUT_FILE = Main.c

TEMPDIR = .temp/
SRCDIR = src/
BINDIR = bin/
TESTDIR = test/
RESDIR = ressources/
##############################################

############ EXECUTION PARAMETERS ############
.DEFAULT_GOAL = help
.PHONY = help install run test zip clean mrproper

VPATH = $(SRCDIR) $(TESTDIR) $(BINDIR)
##############################################

################### Targets ##################

# Affiche l'aide sur les commande de disponible dans le Makefile
help :	## Show this help
	@echo "\033[5m List of available sub-commands : \033[0m" 
	@grep -E '(^[a-zA-Z_-]+ :.*?##.*$$)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf " >> \033[32m%-20s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'


SRC = $(wildcard $(SRCDIR)*.c)
SRC = $(wildcard $(SRCDIR)*/*.c) # Recherche dans les sous dossier (pas de meilleur moyen trouver)
SRC_OBJ = $(addprefix $(TEMPDIR), $(subst .c,.o, $(notdir $(SRC))))

# Compile tout les fichier necessaire pour l'execution de l'application
2048 : $(BINDIR) $(SRC_OBJ) ## Compile all files
	@gcc -o $(BINDIR)$(NAME) $(SRCDIR)$(INPUT_FILE) #$(SRC_OBJ) currently useless in our case

# Compilation générique
$(TEMPDIR)%.o : %.c	$(TEMPDIR)
	@echo "\033[33m Compiling \033[36m $< \033[0m \033[33m... \033[0m"
	@gcc -o $@ -c $<

# Creation du dossier temporaire
$(TEMPDIR) :
	@echo "\033[33m Creating temprary directory : $@ \033[0m"
	@mkdir -p $@

$(BINDIR) :
	@echo "\033[33m Creating binaries directory : $@ \033[0m"
	@mkdir -p $@


# Install et compile tout les fichier necessaire pour l'execution de l'application
install : 2048 $(BINDIR) ## Install and update app
	@echo "\033[33m Copying ressource files ... \033[0m"
	@cp -r $(SRCDIR)$(RESDIR) $(BINDIR)


run : install ## Run and update app
	@./$(BINDIR)$(NAME)


TEST ?= $(wildcard $(TESTDIR)*Test.c)
TEST_OBJ = $(addprefix $(TEMPDIR),$(subst .c,.o, $(notdir $(TEST)) ))
TEST_EXEC = $(addprefix $(BINDIR)$(TESTDIR),$(subst .c,.out, $(notdir $(TEST))))

# Execute un code de test
test : $(TEST_EXEC) ## run all tests selected. Select a test by typing make test TEST=<testName>
	@for i in $(BINDIR)$(TESTDIR)*; do $$i; done

# Create and run tests 
$(BINDIR)$(TESTDIR)%.out : $(TEMPDIR)%.o $(BINDIR)$(TESTDIR)
	@gcc -o $@ $<

# Create directory for tests binaries
$(BINDIR)$(TESTDIR) : $(BINDIR)	
	@echo "\033[33m Creating binaries test directory : $@ \033[0m"
	@mkdir -p $@
	

# Creer un ficher compresser contenant le projet
zip : ## Compress folder as zip
	@echo "\033[33m Compressing folder ... \033[0m"
	@zip -r "Projet-Finale-"`date +%Y-%m-%d-%H-%M-%S` Makefile $(SRCDIR) $(BINDIR) $(TESTDIR) "Planificateur de projet.xlsx" "Compte Rendu.docx" Readme.md TODO.txt


# Efface le dossier temporaire
clean : ## Clean temprary file and binary test
	@echo "\033[33m Cleaning temporary files and binaries tests \033[0m"
	@rm -rf $(TEMPDIR)
	@rm -rf $(TESTDIR)$(BINDIR)


# Efface tout les fichie temporaire et compilé
mrproper : clean ## Clean all files created and set the folder as it was at the beginning.
	@echo "\033[33m Full Cleaning \033[0m"
	@rm -rf $(BINDIR)

##############################################