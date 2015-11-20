<!doctype html>
<head>
  <title>HomePage</title>
  <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;	}
div#menu {background-color:#B0E0E6;height:500px;width:150px;float:left;}
div#content {background-color:#EEEEEE;height:500px;width:350px;float:left;}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;}
h2 {margin-bottom:0;font-size:18px;}
ul {margin:0;}
li {list-style:none;}
</style>
</head>


	

<body>  
<div id="container">

<div id="header">
<h1><center>Welcome To The Library System!</center></h1>
</div>

<div id="menu">
<h2><center>Menu</center></h2>
<ul>
<br>
<li><a href = 'add.php'> Add Books!</a></li>
<br>
<li>Search!</li>
<br>
<li>Borrow!</li>
<br>
<li>Return!</li>
<br>
<li>Manage Cards!</li>
</ul>
</div>

<div id="content">Content goes here</div>
<div id="footer">Powered By Ji Chenyang</div>
</div>



<?php
include("connect.php");

$sql = "SELECT * from test";   //order by id desc limit 10
$query = mysql_query($sql);        //只能执行一次
while($rs = mysql_fetch_array($query)){
?>
<MARQUEE scrollAmount=2>roll!!!</MARQUEE>
<h2>header: <a href="view.php?edit=<?php echo $rs['id'] ?>"> <?php echo $rs['name']?> 
|<a href="edit.php?edit=<?php echo $rs['id'] ?>">edit</a>|<a href = "del.php?del=<?php echo $rs['id'] ?>">delete</a>|</h2>
<li>2015</li>     <!--<ph echo $rs['dates']?>-->
<p>time!!!</p>      <!--<ph echo ichov_substr($rs['things'], 0, 5, "gbk")...?>-->
<hr>
<?php
}
?>
</body>
</html>


