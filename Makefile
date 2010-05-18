CXX	= g++
RM	= rm -f

CFLAGS	= 

LDFLAGS	= 

INCS	= -I.. \
	      -I../out/Release/obj/gen/proto_out

TARGET	= mozc-config

OBJS	= main.o

EXTOBJS	= ../out/Release/obj.target/session_protocol/gen/proto_out/session/config.pb.o \
          ../out/Release/obj.target/session/libconfig_handler.a \
		  ../out/Release/obj.target/dictionary/libdictionary.a \
		  ../out/Release/obj.target/dictionary/libuser_pos_data.a \
          ../out/Release/obj.target/base/*.a

LIBS	= -lpthread -lprotobuf

all:	$(TARGET) ja.mo

$(TARGET):	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(OBJS) $(EXTOBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
	$(RM) -r ja.mo ja/

.cc.o:
	$(CXX) $(CFLAGS) $(INCS) -c $<

ja.mo:	ja.po
	msgfmt -o ja.mo ja.po
	mkdir -p ja/LC_MESSAGES
	ln -s ../../ja.mo ja/LC_MESSAGES/ibus-mozc.mo

mozc-dict:	mozc_dict_main.o
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) mozc_dict_main.o $(EXTOBJS)
