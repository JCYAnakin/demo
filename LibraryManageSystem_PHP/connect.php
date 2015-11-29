<?php
error_reporting(E_ALL ^ E_DEPRECATED);//mute the alarm
date_default_timezone_set('Etc/GMT-8'); 
 @mysql_connect("localhost","root","123456")or die("fail to connect"); //connect to the database
 @mysql_select_db("project") or die("fail to connect the db");                    //select db    
  //mysql_set_chartset('gbk');
 mysql_query("set names 'gbk'");
//
//$sql = mysql_query("INSERT INTO test VALUES ('succ','success')");

                                        //mysql_query("sql statement");
										//mysql_fetch_array( )//index and name
										//           _object
										//mysql_num_row() how many
?>



