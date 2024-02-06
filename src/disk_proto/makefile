SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)

INCLUDE_PATH=/usr/include/orion_link
TARGET=libdisk_pb.so 
CPPFLAGS= -fPIC -I$(INCLUDE_PATH)
LIBS=-levent -lpthread -lplatform -lprotobuf -lssl -lregister_client 
INSTALL_PATH=/usr/lib/

.PHONY:all exist
all:$(TARGET) exist proto   
exist:
	@if [ ! -d $(INCLUDE_PATH) ]; then \
		mkdir -p $(INCLUDE_PATH); \
	fi

$(TARGET):$(OBJS)
	g++ -shared $^ -o $@ $(LIBS)
proto:
	@echo "proto begin"
	protoc -I=./ --cpp_out=./ disk_client_gui.proto
	@echo "proto end"
install:
	cp $(TARGET) $(INSTALL_PATH)
	cp *.h $(INCLUDE_PATH)
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o $(TARGET)