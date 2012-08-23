#include <string>

std::string html = " \
<html> \
    <head> \
	<script> function testFunction() \
	    { \
		alert(\"Tesing js!\"); \
	    } \
	</script>\ 
    </head> \
    <body> \
	<input type=\"button\" onclick=\"testFunction()\" value=\"Show alert box\" /> \
    </body> \
</html> \
";

std::string json = "\ 
{\"data\": \
    { \
	\"name\": \"Bob\",  \
	\"location\": \"San Jose\" \
    }   \
}  \
";
