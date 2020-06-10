################# VARIABLE ###################
NAME = 2048
INPU_FILE = Main.c

TEMP_DIR = .temp/
BUILD_DIR = build/
SRC_DIR = src/
BIN_DIR = $(BUILD_DIR)bin/
TEST_DIR = test/
TEST_BIN_DIR = $(BUILD_DIR)bintest/
RES_DIR = ressources/
##############################################

############ EXECUTION PARAMETERS ############
.DEFAULT_GOAL = help
.PHONY = help install run test zip clean mrproper

VPATH = $(SRC_DIR) $(TEST_DIR) $(BIN_DIR)
##############################################

################### Targets ##################

# Affiche l'aide sur les commande de disponible dans le Makefile
help :	## Show this help
	@echo "\033[5m List of available sub-commands : \033[0m" 
	@grep -E '(^[a-zA-Z_-]+ :.*?##.*$$)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf " >> \033[32m%-20s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'


SRC = $(subst $(SRC_DIR)$(INPU_FILE),, $(wildcard $(SRC_DIR)*.c))
SRC_OBJ = $(addprefix $(TEMP_DIR), $(subst .c,.o, $(notdir $(SRC))))

# Compile tout les fichier necessaire pour l'execution de l'application
2048 : $(BIN_DIR) $(SRC_OBJ) ## Compile all files
	@gcc -o $(BIN_DIR)$(NAME) $(SRC_DIR)$(INPU_FILE) $(SRC_OBJ)

# Compilation générique
$(TEMP_DIR)%.o : %.c $(TEMP_DIR)
	@echo "\033[33m Compiling \033[36m $< \033[0m \033[33m... \033[0m"
	@gcc -o $@ -c $< -g

# Creation du dossier temporaire
$(TEMP_DIR) :
	@echo "\033[33m Creating temprary directory : $@ \033[0m"
	@mkdir -p $@

# Creation du dossier binaire
$(BIN_DIR) : $(BUILD_DIR)	
	@echo "\033[33m Creating binaries directory : $@ \033[0m"
	@mkdir -p $@

# Creation du dossier build
$(BUILD_DIR) :	
	@echo "\033[33m Creating build directory : $@ \033[0m"
	@mkdir -p $@


# Install et compile tout les fichier necessaire pour l'execution de l'application
install : 2048 $(BIN_DIR) ## Install and update app
	@echo "\033[33m Copying ressource files ... \033[0m"
	@cp -r $(SRC_DIR)$(RES_DIR) $(BIN_DIR)


run : install ## Run and update app
	@(cd $(BIN_DIR) && ./$(NAME))


TEST ?= $(wildcard $(TEST_DIR)*Test.c)
TEST_EXEC = $(addprefix $(TEST_BIN_DIR),$(subst .c,.out, $(notdir $(TEST))))

# Execute un code de test
test : $(TEST_EXEC) ## run all tests selected. Select a test by typing make test TEST=<testName>
	@for i in $(TEST_EXEC); do $$i; done

# Create and run tests 
$(TEST_BIN_DIR)%.out : $(TEMP_DIR)%.o $(TEST_BIN_DIR) $(SRC_OBJ)
	@gcc -o $@ $< $(SRC_OBJ) -g

# Create directory for tests binaries
$(TEST_BIN_DIR) : $(BUILD_DIR)	
	@echo "\033[33m Creating binaries test directory : $@ \033[0m"
	@mkdir -p $@
	

# Creer un ficher compresser contenant le projet
zip : ## Compress folder as zip
	@echo "\033[33m Compressing folder ... \033[0m"
	@zip -r "Projet-Finale-"`date +%Y-%m-%d-%H-%M-%S` Makefile $(SRC_DIR) $(BUILD_DIR) $(TEST_DIR) "Planificateur de projet.xlsx" "Compte Rendu.docx" Readme.md TODO.txt


# Efface le dossier temporaire
clean : ## Clean temprary file and binary test
	@echo "\033[33m Cleaning temporary files and binaries tests \033[0m"
	@rm -rf $(TEMP_DIR)
	@rm -rf $(TEST_BIN_DIR)


# Efface tout les fichie temporaire et compilé
mrproper : clean ## Clean all files created and set the folder as it was at the beginning.
	@echo "\033[33m Full Cleaning \033[0m"
	@rm -rf $(BUILD_DIR)

##############################################