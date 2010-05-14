CXX	= g++
RM	= rm -f
CFLAGS	= 
LDFLAGS	= 
INCS	= -I.. \
	  -I../out/Release/obj/gen/proto_out \
	  -I../protobuf/files/src
TARGET	= mozc-config
OBJS	= main.o
EXTOBJS	= ../out/Release/obj.target/session_protocol/gen/proto_out/session/config.pb.o \
          ../out/Release/obj.target/protobuf/libprotobuf.a \
          ../out/Release/obj.target/session/libconfig_handler.a \
          ../out/Release/obj.target/base/*.a
LIBS	= -lpthread

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(OBJS) $(EXTOBJS)

clean:
	$(RM) $(TARGET) $(OBJS)

.cc.o:
	$(CXX) $(CFLAGS) $(INCS) -c $<

