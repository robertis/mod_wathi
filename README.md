WATHI
============

An apache module for getting insights on every HTTP request

Currently, it works only on Mac OSX ( Lion). It will be ported to Linux.

INSTALLATION
===============


1. Add the following to /etc/apache2/httpd.conf

    <code>
    
    	LoadModule wathi_module libexec/apache2/mod_wathi.so
    
    </code>

2. For the web dashboard and the REST API , also add to httpd.conf

    <code>

    	<Location /wakai>
			SetHandler wathi
    	</Location>

    </code>


3. For setting up database, install sqlite3. 

	a. Create a db file wathi.db in /tmp folder
	
	b. Create a sql file, wathi.sql with contents
	
    <code>

        CREATE TABLE requests ( id INTEGER PRIMARY KEY, method VARCHAR[32], uri VARCHAR[32], response_time REAL);

    </code>

	c. Give read/write permission to the apache user. 
	If you dont set this permission correctly, the apache module will not be able to write anything to the db.
	
	d. Run the command in the sqlite3 shell :
	
    <code>
	
        sqlite3 wathi.db
		
    </code>
	
	e. Run the command in the sqlite3 shell :
	
    <code>
    	
        .read wathi.sql
		
    </code>
	
	f. Add the following to the Apache config file ( httpd.conf)
    	
    <code>

        DBDriver        sqlite3
        DBDParams       "/tmp/wathi.db"
        DBDMin          1
        DBDKeep         1
        DBDMax          1
        DBDPersist      On

    </code>


4. Run 'sudo make' on the top level folder. It will install the module and restart apache.

	In a web browser , go to :
	
    <code>

        http://localhost/wakai/web 

    </code>

	to view the dashboard.
	
	Or, go to : 
	
    <code>

        http://localhost/wakai/rest 

    </code>
    
	to view the insights data in json.






