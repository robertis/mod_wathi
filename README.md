WATHI
============

An apache module for getting insights on every HTTP request

Currently, it works only on Mac OSX ( Lion). Porting to Linux is easy.

INSTALLATION
===============


1. Add the following to /etc/apache2/httpd.conf

    
        LoadModule wathi_module libexec/apache2/mod_wathi.so
    
    
2. For the web dashboard and the REST API , also add to httpd.conf

    
    	<Location /wakai>
			SetHandler wathi
    	</Location>

    

3. For setting up database, install sqlite3. 

	a. Create a db file wathi.db in /tmp folder
	
	b. Create a sql file, wathi.sql with contents
	
    
        CREATE TABLE requests ( id INTEGER PRIMARY KEY, method VARCHAR[10], uri VARCHAR[256], time_stamp VARCHAR[52], response_time REAL);

    
	c. Give read/write permission to the apache user. 
	If you dont set this permission correctly, the apache module will not be able to write anything to the db.
	
	d. Run the command in the sqlite3 shell :
	
    	
        sqlite3 wathi.db
		
    	
	e. Run the command in the sqlite3 shell :
	
    	
        .read wathi.sql
		
    	
	f. Add the following to the Apache config file ( httpd.conf)
    	
    
        DBDriver        sqlite3
        DBDParams       "/tmp/wathi.db"
        DBDMin          1
        DBDKeep         1
        DBDMax          1
        DBDPersist      On

    

4. Run 'sudo make' on the top level folder. It will install the module and restart apache.

	In a web browser , go to :
	
    
        http://localhost/wakai/web 

    
	to view the dashboard.
	
	Or, go to : 
	
    
        http://localhost/wakai/rest 

    
	to view the insights data in json.






