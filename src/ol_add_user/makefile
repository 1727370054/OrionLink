TARGET=ol_add_user
SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC) ) 
INCLUDE_PATH=/usr/include/orion_link 
CPPFLAGS= -I$(INCLUDE_PATH)
LIBS=-levent -lpthread -lplatform -lprotobuf -lauth
INSTALL_PATH=../../bin/
$(TARGET):$(OBJS)  
	g++  $+ -o $@ $(LIBS)
install:
	@echo "make start shell"
	cp $(TARGET) $(INSTALL_PATH)
uninstall:
	rm -rf *.o  $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o  $(TARGET) 