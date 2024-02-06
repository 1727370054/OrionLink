SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC) )
TARGET=liboldb.so
CPPFLAGS= -fPIC  -I/usr/include/mysql
LIBS=-lpthread -lmysqlclient  
# apt-get install libmysqlclient-dev
INSTALL_PATH=/usr/lib/
INCLUDE_PATH=/usr/include/orion_link 

.PHONY:all exist
all:$(TARGET) exist  
exist:
	@if [ ! -d $(INCLUDE_PATH) ]; then \
		mkdir -p $(INCLUDE_PATH); \
	fi

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
