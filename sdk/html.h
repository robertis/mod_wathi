#include <string>

std::string html = "\
		    <link rel='stylesheet' href='http://yuilibrary.com/combo/css?main-min.css'> \
		    <script src='http://yui.yahooapis.com/3.6.0/build/yui/yui-min.js'></script> \
		    <div id='wathi'></div> \
		    <script> \
		    YUI().use('datatable', 'io-base', 'json-parse', function (Y) \
		    { \
			var url = 'http://localhost/wakai/rest'; \
			function renderTheTable(req_data){ \
			    var table = new Y.DataTable({ \
				columns: [ 'id', 'method', 'uri', 'time_stamp', 'response_time' ], \
				data : req_data, \
				summary: 'Apache requests insights', \
				caption: 'Data from last few days. The response time is in milliseconds' \
			    }); \
			    table.render('#wathi'); \
			} \
			function complete(id, o, args) { \
			    var id = id; \
			    try { \
				parsedResponse = Y.JSON.parse(o.responseText); \
				var res = parsedResponse.result; \
				renderTheTable(res); \
			    } \
			    catch (e) { \
				Y.log('exception while calling REST'); return; \
			    } \
			}; \
			Y.on('io:complete', complete, Y); \
			var request = Y.io(url); \
		    }); \
		    </script>";

std::string json = "\ 
{\"data\": \
    { \
	\"name\": \"Bob\",  \
	\"location\": \"San Jose\" \
    }   \
}  \
";
