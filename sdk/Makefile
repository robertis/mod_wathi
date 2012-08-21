LIBTOOL=/usr/share/apr-1/build-1/libtool
LIBTOOL_INCLUDE=/usr/include/apr-1
INSTALL_PATH=/usr/libexec/apache2

OBJECTS=wathi_sdk.lo

SDKLIB=wathi_sdk.la

all: $(SDKLIB)
    	
$(SDKLIB): $(OBJECTS)
	$(LIBTOOL) --silent --mode=link gcc -export-dynamic -rpath $(INSTALL_PATH) -module -avoid-version  $(OBJECTS) -o $(SDKLIB)

%.lo: %.cpp
	$(LIBTOOL) --silent --mode=compile g++ -DDARWIN -DSIGPROCMASK_SETS_THREAD_MASK -I/usr/local/include -I$(APACHE2_INCLUDE) -I$(LIBTOOL_INCLUDE) -c $< -o $@



clean:
	\rm -f *.so *.la *.lo *.slo *.o *~



