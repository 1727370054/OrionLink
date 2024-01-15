SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC) )
TARGET=liboldb.so
CPPFLAGS= -fPIC  -I/usr/include/mysql
LIBS=-lpthread 
# apt-get install libmysqlclient-dev
INSTALL_PATH=/usr/lib/
exist = $(shell if [ ! -d $(INCLUDE_PATH) ]; then mkdir $(INCLUDE_PATH); fi;)

$(TARGET):$(OBJS)
	g++ -shared $+ -o $@ $(LIBS)
install:
	cp $(TARGET) $(INSTALL_PATH)
	@echo $(exist) "check include ..."
	cp *.h $(INCLUDE_PATH)
	@echo "install liboldb.so success!"
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o $(TARGET)
