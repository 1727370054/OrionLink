SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC) ../register_client/register_client.o 

TARGET=config_client
CPPFLAGS= -I../platform -I../register_client
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