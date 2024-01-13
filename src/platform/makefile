SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)

TARGET=libplatform.so
CPPFLAGS= -fPIC
LIBS=-levent -lpthread -levent_openssl
INSTALL_PATH=/usr/lib/

$(TARGET):$(OBJS)
	g++ -shared $^ -o $@ $(LIBS)
proto:
	@echo "proto begin"
	protoc -I=./ --cpp_out=./ msg_comm.proto msg_type.proto
	@echo "proto end"
install:$(TARGET) $(OBJS)
	@echo "begin install in "$(INSTALL_PATH)
	@cp *.so $(INSTALL_PATH)
	@echo "install success!"
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
clean:
	rm -rf *.o $(TARGET)


