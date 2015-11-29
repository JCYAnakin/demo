<!doctype html>
<head>
  <title>Delete Card</title>
  <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;font-family:"Colonna MT";}
div#menu {background-color:#B0E0E6;height:425px;width:864px;float:left;font-family:"Courier New"}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;}
h2 {margin-bottom:0;font-size:18px;text-align: center}
ul {margin:0;}
li {list-style:none;text-align: center}
</style>

<style> 
html{width:100%;height:100%;} 
body{background:#fff;font-size:18px;font-family:"Arial", "Tahoma", "微软雅黑", "雅黑";
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
    padding:2px 100px 2px 100px;
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
<h1><center>Delete Card!</center></h1>
</div>

<div id="menu">
<h2><center>  
<form action = "card_del.php" method = "post">
<table border="0">
<tr>
  <td>Card ID:</td>
  <td><input type="text" name="id"></td>
</tr>
</table>
<input type = "submit" name="sub" class="btn" value="DELETE CARD!"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'">
</form>
<br>
</center></h2>
<ul>
<li><a href = 'index.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Home</a></li>
</ul>
</div>

<div id="footer">Powered By Ji Chenyang</div>
</div> 
</body> 
</html>

<?php
 	include("connect.php");	

 	if(!empty($_POST['sub'])){
 		$id = $_POST['id'];
 		 $sql_s = "SELECT * FROM card WHERE id = '$id'";
		 $sql = "DELETE FROM card WHERE id = '$id'";
// if the insert is null
			$check = mysql_query($sql_s);
			$rs_s = mysql_fetch_array($check);
			if(!$rs_s){
				echo "<script>alert('this id doesn\'t exist!');location.href = 'card_del.php'</script>";
			}
			else{
					mysql_query($sql);
					echo "<script>alert('Delete Card Success!');location.href = 'cards.php'</script>";  
				}
		}

?>
