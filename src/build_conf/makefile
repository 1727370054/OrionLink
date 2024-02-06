SRC_CPP=$(wildcard *.cpp)
SRC_CC=$(wildcard *.cc)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRC_CPP))
OBJS_CC=$(patsubst %.cc,%.o,$(SRC_CC))
OBJS=$(OBJS_CPP) $(OBJS_CC)
MYSQL_CONFIG_PATH=/etc/ol_mysql_init.conf
TARGET=build_mysql_conf
INSTALL_PATH=../../bin/

$(TARGET):$(OBJS)
	g++  $+ -o $@ $(LIBS)
install:
	cp $(TARGET) $(INSTALL_PATH)
uninstall:
	rm -rf *.o $(TARGET)
	rm -rf $(INSTALL_PATH)$(TARGET)
	rm -rf $(MYSQL_CONFIG_PATH)
clean:
	rm -rf *.o $(TARGET)
	rm -rf $(MYSQL_CONFIG_PATH)