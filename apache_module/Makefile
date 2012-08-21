LIBTOOL=/usr/share/apr-1/build-1/libtool
LIBTOOL_INCLUDE=/usr/include/apr-1
APACHE2_INCLUDE=/usr/include/apache2
INSTALL_PATH=/usr/libexec/apache2
TARGET=mod_wathi
SDK_LIB=../sdk/wathi_sdk.la

all: build

build: $(TARGET).la

$(TARGET).lo: $(TARGET).c
	$(LIBTOOL) --silent --mode=compile gcc -DDARWIN -DSIGPROCMASK_SETS_THREAD_MASK -I/usr/local/include -I$(APACHE2_INCLUDE) -I$(LIBTOOL_INCLUDE) -c -o $(TARGET).lo $(TARGET).c 

$(TARGET).la: $(TARGET).lo 
	$(LIBTOOL) --silent --mode=link gcc -o $(TARGET).la -rpath $(INSTALL_PATH) -module -avoid-version $(TARGET).lo $(SDK_LIB)

clean:
	\rm -f *.so *.la *.lo *.slo *.o *~


