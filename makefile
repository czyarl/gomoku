CXXFLAGS = -O2 -std=c++14
TARG_NAME = gomoku
TARG_NUM = v0.7.4.1
TARG_WIN_FULL = $(TARG_NAME)_$(TARG_NUM)_full.exe
TARG_WIN_DOS = $(TARG_NAME)_$(TARG_NUM)_dos.exe
TARG_LIN_DOS = $(TARG_NAME)_$(TARG_NUM)_dos
SBJS = EntityControl.o dosplay.o
SBJS_UI = main.o paint.o
SBJS_DOS = main_dos.o 
HEAD = entity/Entity.h basic/BasicDef.h dosplay/dosplay.h
HEAD_UI = paint/paint.h 
LIBS = -L./entity/AIs -lAIs
LIBS_UI = -L. -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
LIBS_EGE32 = -L./libs -lgraphics
LIBS_EGE64 = -L./libs -lgraphics64

winfull64 : $(SBJS) $(SBJS_UI)
	g++ -o $(TARG_WIN_FULL) $(SBJS) $(SBJS_UI) $(LIBS) $(LIBS_EGE64) $(LIBS_UI)

winfull32 : $(SBJS) $(SBJS_UI)
	g++ -o $(TARG_WIN_FULL) $(SBJS) $(SBJS_UI) $(LIBS) $(LIBS_EGE32) $(LIBS_UI)

lindos : $(SBJS) $(SBJS_DOS)
	g++ -o $(TARG_LIN_DOS) $(SBJS) $(SBJS_DOS) $(LIBS)

windos : $(SBJS) $(SBJS_DOS)
	g++ -o $(TARG_WIN_DOS) $(SBJS) $(SBJS_DOS) $(LIBS)

EntityControl.o : entity/EntityControl.cpp entity/AIs/initAIs.h entity/Entity.h entity/EntityControl.h basic/BasicDef.h
	g++ -c entity/EntityControl.cpp $(CXXFLAGS)

dosplay.o : dosplay/dosplay.cpp dosplay/dosplay.h entity/Entity.h basic/BasicDef.h entity/EntityControl.h
	g++ -c dosplay/dosplay.cpp $(CXXFLAGS)

paint.o : paint/paint.cpp entity/AIs/declaration.h entity/EntityControl.h paint/board.h paint/button_start.h paint/button_show.h paint/button_hide.h paint/button_undo.h paint/list_player1.h paint/list_player2.h paint/control.h
	g++ -c paint/paint.cpp $(CXXFLAGS)

main_dos.o : main_dos.cpp $(HEAD)
	g++ -c main_dos.cpp $(CXXFLAGS)

main.o : main.cpp $(HEAD)
	g++ -c main.cpp $(CXXFLAGS)

clean :
	-rm $(SBJS) $(SBJS_DOS) $(SBJS_UI) $(TARG_LIN_DOS) $(TARG_WIN_DOS) $(TARG_WIN_FULL)

cleantmp :
	-rm $(SBJS) $(SBJS_DOS) $(SBJS_UI)
