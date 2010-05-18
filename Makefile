CXX	= g++
RM	= rm -f

CFLAGS	= 

LDFLAGS	= 

INCS	= -I.. \
	      -I../out/Release/obj/gen/proto_out

TARGET	= mozc-config

OBJS	= main.o

MOZC_DICT	= mozc-dict

MOZC_DICT_OBJS	= mozc_dict_main.o

EXTOBJS	= ../out/Release/obj.target/session_protocol/gen/proto_out/session/config.pb.o \
          ../out/Release/obj.target/session/libconfig_handler.a \
		  ../out/Release/obj.target/dictionary/libdictionary.a \
		  ../out/Release/obj.target/dictionary/libuser_pos_data.a \
          ../out/Release/obj.target/base/*.a

LIBS	= -lpthread -lprotobuf

all:	$(TARGET) $(MOZC_DICT) ja.mo

$(TARGET):	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(OBJS) $(EXTOBJS)

$(MOZC_DICT):	$(MOZC_DICT_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(MOZC_DICT_OBJS) $(EXTOBJS)

clean:
	$(RM) $(TARGET) $(OBJS) $(MOZC_DICT) $(MOZC_DICT_OBJS)
	$(RM) -r ja.mo ja/

.cc.o:
	$(CXX) $(CFLAGS) $(INCS) -c $<

ja.mo:	ja.po
	msgfmt -o ja.mo ja.po
	mkdir -p ja/LC_MESSAGES
	ln -s ../../ja.mo ja/LC_MESSAGES/ibus-mozc.mo

