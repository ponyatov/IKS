log.log: ./exe.exe iks.iks
	./exe.exe < iks.iks > log.log && tail log.log
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
./exe.exe: $(C) $(H)
	$(CXX) -std=gnu++11 -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
