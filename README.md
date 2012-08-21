wathi
============

An apache module for getting insights on every HTTP request

Currently, it works only on Mac OSX ( Lion). It will be ported to Linux.

INSTALLATION
===============

1. Run 'sudo make' on the top level folder.

2. Add the following to /etc/apache2/httpd.conf

    LoadModule wathi_module libexec/apache2/mod_wathi.so
