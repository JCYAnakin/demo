<!doctype html>
<head>
  <title>HomePage</title>
  <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;}
div#menu {background-color:#B0E0E6;height:425px;width:864px;float:left;}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;}
h2 {margin-bottom:0;font-size:40px;text-align: center}
ul {margin:0;}
li {list-style:none;text-align: center}
</style>

<style> 
html{width:100%;height:100%;} 
body{background:#fff;font-size:18px;font-family:"Colonna MT", "Tahoma", "微软雅黑", "雅黑";
line-height:18px;padding:0px;margin:0px;text-align:center} 
div{padding:18px} 
img{border:0px;vertical-align:middle;padding:0;margin:0} 
input, button{font-family:"Arial", "Tahoma", "微软雅黑", "雅黑";border:0;
vertical-align:middle;margin:8px;line-height:18px;font-size:18px} 
.btn{width:140px;height:36px;line-height:18px;font-size:18px;
background:url("bg.jpg") no-repeat left top;color:#FFF;padding-bottom:4px} 
a{      /* 统一设置所以样式 */
     font-family:HAKUYOGuiFanZi3500;
     font-size:30px;
     text-align:center;
     margin:3px;
}
a:link,a:visited{  /* 超链接正常状态、被访问过的样式 */
    color: #F0F0F0;
    padding:4px 150px 4px 150px;
    background-color:#00AEAE;
    text-decoration:none;
 
    border-top:1px solid #EEEEEE; /* 边框实现阴影效果 */
    border-left:1px solid #EEEEEE;
    border-bottom:1px solid #717171;
    border-right:1px solid #717171;
}
a:hover{       /* 鼠标指针经过时的超链接 */
    color:#821818;     /* 改变文字颜色 */
    padding:5px 160px 3px 160 px;  /* 改变文字位置 */
    background-color:#e2c4c9;  /* 改变背景色 */
    border-top:1px solid #717171; /* 边框变换，实现“按下去”的效果 */
    border-left:1px solid #717171;
    border-bottom:1px solid #EEEEEE;
    border-right:1px solid #EEEEEE;
}
</style> 
</head>
<body>  
<div id="container">

<div id="header">
<h1><center>Welcome To The Library System!</center></h1>
</div>
<div id="menu">
<h2><center>Menu
<ul>
<br>
  <li  align="center"><a href = 'add.php'class = "a"> +Books! </a></li>
  <br>
  <br>
  <li  align="center"><a href = 'add2.php'class = "a"> +Books2 </a></li>
  <br>
  <br>
  <li align = "center"><a href = 'search.php'class = "a" >Search!</a></li>
<br>
<br>
 <li  align="center"><a href = 'borrowpre.php'class = "a"> Borrow! </a></li>
<br>
<br>
 <li  align="center"><a href = 'returnpre.php'class = "a"> Return! </a></li>
<br>
<br>
 <li  align="center"><a href = 'cards.php'class = "a"> +-Cards </a></li>
</ul>
</center></h2>
</div>

<div id="footer">Powered By Ji Chenyang</div>
</div>
 
<MARQUEE scrollAmount=2>Wish You Happy Every Day!!!!! </MARQUEE>  
<center>
<?php
	date_default_timezone_set('Etc/GMT-8'); 
	echo date("Y-m-d H:i:s");
	?>
</center>
</body> 
</html>


