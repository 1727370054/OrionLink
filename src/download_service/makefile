SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)
INCLUDE_PATH=/usr/include/orion_link 

TARGET=download_service
CPPFLAGS= -I$(INCLUDE_PATH)
LIBS=-levent -lpthread -lplatform -lprotobuf -lssl -ldisk_pb
INSTALL_PATH=/usr/bin/

WATCH=watch_$(TARGET)
START_SHELL=start_$(TARGET)
STOP_SHELL=stop_$(TARGET)

$(TARGET):$(OBJS)
	g++ $^ -o $@ $(LIBS)
$(WATCH):../platform/watchdog.cpp 
	g++ $^ -o $@
install:$(WATCH)
	@echo "make start shell"
	# watch_register_server 3 register_server 20011
	echo "#!/bin/bash" > $(START_SHELL)
	echo "$(WATCH) 3 $(TARGET) \$$1 \$$2 \$$3 \$$4 \$$5" >$(START_SHELL)
	chmod +x $(START_SHELL)
	@echo "make stop shell"
	echo "#!/bin/bash" > $(STOP_SHELL)
	echo "killall $(WATCH)" >> $(STOP_SHELL)
	echo "killall $(TARGET)" >> $(STOP_SHELL)
	chmod +x $(STOP_SHELL)
	@echo "begin install in "$(INSTALL_PATH)
	cp $(TARGET) $(INSTALL_PATH)
	cp $(WATCH) $(INSTALL_PATH)
	cp $(START_SHELL) $(INSTALL_PATH)
	cp $(STOP_SHELL) $(INSTALL_PATH)
	@echo "install success!"
uninstall:
	rm -rf *.o $(TARGET) $(WATCH) $(START_SHELL) $(STOP_SHELL)
	rm -rf $(INSTALL_PATH)$(TARGET)
	rm -rf $(INSTALL_PATH)$(WATCH)
	rm -rf $(INSTALL_PATH)$(START_SHELL)
	rm -rf $(INSTALL_PATH)$(STOP_SHELL)
clean:
	rm -rf *.o $(TARGET) $(WATCH) $(START_SHELL) $(STOP_SHELL)