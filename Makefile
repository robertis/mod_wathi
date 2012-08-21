APXS=apxs
APACHECTL=apachectl

LIBTOOL=/usr/share/apr-1/build-1/libtool
INSTALL_PATH=/usr/libexec/apache2
TARGET=mod_wathi
BUILD_SDK=sdk_objects
MAKE=make
INSIGHTLIB=apache_module/mod_wathi.la
APC_MOD=mod_wathi.lo
CLEAN_SDK=clean_sdk
CLEAN_APC=clean_apc

all: stop clean install start



$(BUILD_SDK): 
	cd sdk; $(MAKE)

$(CLEAN_SDK): 
	cd sdk; $(MAKE) clean

$(APC_MOD): 
	cd apache_module; $(MAKE)

$(CLEAN_APC): 
	cd apache_module; $(MAKE) clean

install: $(BUILD_SDK) $(APC_MOD)
	$(APXS) -i $(INSIGHTLIB)
	$(LIBTOOL) --finish $(INSTALL_PATH)

clean: $(CLEAN_SDK) $(CLEAN_APC)
	\rm -f *.so *.la *.lo *.slo *.o *~

uninstall:
	$(LIBTOOL) --mode=uninstall /bin/rm $(INSTALL_PATH)/$(TARGET).*

reload: install restart

start:
	$(APACHECTL) start
restart:
	$(APACHECTL) restart
stop:
	$(APACHECTL) stop

