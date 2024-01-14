SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)

TARGET=register_client
CPPFLAGS= -I../platform
LIBS=-levent -lpthread -lplatform -lprotobuf -lssl 
INSTALL_PATH=/usr/bin/

$(TARGET):$(OBJS)
	g++ $^ -o $@ $(LIBS)
install:
	cp $(TARGET) $(INSTALL_PATH)
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o $(TARGET)