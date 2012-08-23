wathi
============

An apache module for getting insights on every HTTP request

Currently, it works only on Mac OSX ( Lion). It will be ported to Linux.

INSTALLATION
===============


1. Add the following to /etc/apache2/httpd.conf

    LoadModule wathi_module libexec/apache2/mod_wathi.so

2. For the web dashboard and the REST API , also add to httpd.conf
    <Location /wakai>
	SetHandler wathi
    </Location>

2. Run 'sudo make' on the top level folder. It will install the module and restart apache.
	In a web browser , go to :
	    http://localhost/wakai/web 
	to view the dashboard.
