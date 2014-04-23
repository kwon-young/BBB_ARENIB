
CXX=g++
DEBUG=yes
STATIC=yes

CIBLE=simu
EXE=$(CIBLE)
EXEC=$(EXE)
SRC_DIR=src
SRC_DIR_CIBLE=$(SRC_DIR)/$(CIBLE)
OBJ_DIR=build
INC_DIR=include
INC_DIR_CIBLE=$(INC_DIR)/$(CIBLE)

SRC=$(wildcard $(SRC_DIR)/*.cpp) 
SRC_CIBLE=$(wildcard $(SRC_DIR_CIBLE)/*.cpp) 
INC=$(wildcard $(INC_DIR)/*.hpp) 
INC_CIBLE=$(wildcard $(INC_DIR_CIBLE)/*.hpp)
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_CIBLE=$(SRC_CIBLE:$(SRC_DIR_CIBLE)/%.cpp=$(OBJ_DIR)/%.o)
CXXFLAGS= -W -Wall -I$(INC_DIR) -I$(INC_DIR_CIBLE) -D SFML_STATIC=1

ifeq ($(CIBLE), simu)
  CXXFLAGS+= -D SIMULATION=1
endif
ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g
  LDFLAGS= -lsfml-network-s-d -lsfml-system-s-d
else 
  CXXFLAGS+= -O2
  LDFLAGS= -lsfml-network-s -lsfml-system-s
endif

all:$(EXEC)
ifeq ($(DEBUG), yes)
	@echo Generation en mode debug
else
	@echo Generation en mode release
endif


build/%.o: $(SRC_DIR_CIBLE)/%.cpp $(INC_CIBLE) $(INC)
	@echo Compilation C++ $< to $@
	$(CXX)  -c $< -o $@ $(CXXFLAGS)

build/%.o: $(SRC_DIR)/%.cpp $(INC) $(INC_CIBLE)
	@echo Compilation C++ $< to $@
	$(CXX)  -c $< -o $@ $(CXXFLAGS)

$(EXEC):$(OBJ) $(OBJ_CIBLE)
	@echo -----LINKAGE-----
	$(CXX) -o $@ $(OBJ) $(OBJ_CIBLE) $(LDFLAGS)

.PHONY : clean run

run:
	$(EXEC)

clean:
	rm -rf $(OBJ_DIR)/*.o *.exe *~ */*~ */*/*~ $(CIBLE)
