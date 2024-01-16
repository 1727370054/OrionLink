SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)

INCLUDE_PATH=/usr/include/orion_link
TARGET=libconfig_client.so 
CPPFLAGS= -fPIC -I$(INCLUDE_PATH)
LIBS=-levent -lpthread -lplatform -lprotobuf -lssl -lregister_client 
INSTALL_PATH=/usr/lib/

.PHONY:all exist
all:$(TARGET) exist  
exist:
	@if [ ! -d $(INCLUDE_PATH) ]; then \
		mkdir -p $(INCLUDE_PATH); \
	fi

$(TARGET):$(OBJS)
	g++ -shared $^ -o $@ $(LIBS)
install:
	cp $(TARGET) $(INSTALL_PATH)
	cp *.h $(INCLUDE_PATH)
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o $(TARGET)