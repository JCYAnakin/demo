<style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;}
div#menu {background-color:#B0E0E6;height:500px;width:864px;float:left;}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;}
h2 {margin-bottom:0;font-size:18px;text-align: center}
ul {margin:0;}
li {list-style:none;text-align: center}
</style>

<style> 
html{width:100%;height:100%;} 
body{background:#66B3FF;font-size:18px;font-family:"Colonna MT", "Tahoma", "微软雅黑", "雅黑";
line-height:18px;padding:0px;margin:0px;text-align:center} 
div{padding:18px} 
img{border:0px;vertical-align:middle;padding:0;margin:0} 
input, button{font-family:"Arial", "Tahoma", "微软雅黑", "雅黑";border:0;
vertical-align:middle;margin:8px;line-height:18px;font-size:18px} 
.btn{width:140px;height:36px;line-height:18px;font-size:18px;
background:url("bg.jpg") no-repeat left top;color:#FFF;padding-bottom:4px} 
.a { width:140px;height:36px;line-height:18px;font-size:18px;
background:url("bg.jpg") no-repeat left top;color:#FFF;padding-bottom:4pxtext-decoration:none}
</style> 
<head>
<title>login page</title>
</head>
<body>
<?php
	date_default_timezone_set('Etc/GMT-8'); 
	echo date("Y-m-d H:i:s");
?>
<form action = "login2.php" method = "post">
<br>
<center>Input Admin ID:<input type="text" name="id"></center><br>
<center>Input Password:<input type="text" name="password"></center><br>
<center><input type = "submit" name="sub" value="Log in!"></center>
</form>
</body>