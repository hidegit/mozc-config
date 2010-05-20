DESTDIR =
prefix = /usr/local
bindir = $(prefix)/bin
libexecdir = $(prefix)/libexec
datadir = $(prefix)/share

CXX	= g++
RM	= rm -f
INSTALL = /usr/bin/install

MOZC_SRC = ..

CFLAGS	= 

LDFLAGS	=

INCS	= -I$(MOZC_SRC) \
	      -I$(MOZC_SRC)/out/Release/obj/gen/proto_out

MOZC_CONF	= mozc-config

MOZC_CONF_OBJS	= mozc_config_main.o

MOZC_DICT	= mozc-dict

MOZC_DICT_OBJS	= mozc_dict_main.o

EXTOBJS	= $(MOZC_SRC)/out/Release/obj.target/session_protocol/gen/proto_out/session/config.pb.o \
          $(MOZC_SRC)/out/Release/obj.target/session/libconfig_handler.a \
		  $(MOZC_SRC)/out/Release/obj.target/dictionary/libdictionary.a \
		  $(MOZC_SRC)/out/Release/obj.target/dictionary/libuser_pos_data.a \
          $(MOZC_SRC)/out/Release/obj.target/base/*.a

LIBS	= -lpthread -lprotobuf

IBUS_SETUP_MOZC = ibus-setup-mozc

MOS = ja.mo

all:	$(MOZC_CONF) $(MOZC_DICT) $(MOS)

$(MOZC_CONF):	$(MOZC_CONF_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(MOZC_CONF_OBJS) $(EXTOBJS)

$(MOZC_DICT):	$(MOZC_DICT_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBS) $(MOZC_DICT_OBJS) $(EXTOBJS)

$(IBUS_SETUP_MOZC) :	$(IBUS_SETUP_MOZC).in
	sed -e 's|@LOCALE_DIR@|$(DESTDIR)/$(datadir)/locale|' \
		-e 's|@IBUS_MOZC_DIR@|$(DESTDIR)/$(datadir)/ibus-mozc/setup|' \
		-e 's|@BIN_DIR@|$(DESTDIR)/$(bindir)|' $@.in > $@
	chmod +x $@

install: all $(IBUS_SETUP_MOZC)
	$(INSTALL) -d $(DESTDIR)/$(bindir)
	$(INSTALL) -d $(DESTDIR)/$(libexecdir)
	$(INSTALL) -d $(DESTDIR)/$(datadir)/locale/ja/LC_MESSAGES
	$(INSTALL) -d $(DESTDIR)/$(datadir)/ibus-mozc/setup
	$(INSTALL) -m755 $(MOZC_CONF) $(MOZC_DICT) $(DESTDIR)/$(bindir)
	$(INSTALL) -m755 $(IBUS_SETUP_MOZC) $(DESTDIR)/$(libexecdir)
	$(INSTALL) -m644 ja.mo $(DESTDIR)/$(datadir)/locale/ja/LC_MESSAGES/ibus-mozc.mo
	$(INSTALL) -m644 setup.glade $(DESTDIR)/$(datadir)/ibus-mozc/setup
 
clean:
	$(RM) $(MOZC_CONF) $(MOZC_CONF_OBJS) $(MOZC_DICT) $(MOZC_DICT_OBJS) $(IBUS_SETUP_MOZC) $(MOS)

.SUFFIXES: .cc .o .po .mo

.cc.o:
	$(CXX) $(CFLAGS) $(INCS) -c $<

.po.mo:
	msgfmt -o $*.mo $*.po

