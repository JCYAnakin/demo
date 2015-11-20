<head>
  <title>Return Books</title>
    <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;}
div#menu {background-color:#B0E0E6;height:425px;width:864px;float:left;}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;font-family: Colonna MT}
h2 {margin-bottom:0;font-size:18px;text-align: center}
p {margin-bottom:0;font-size:22px;font-family: Candara}
ul {margin:0;}
li {list-style:none;text-align: center}
table {
margin:0 auto;
text-align: left;
}
table.hovertable {
	font-family: Candara,arial,sans-serif;
	font-size:30px;
	color:#333333;
	border-width: 1px;
	border-color: #999999;
	border-collapse: collapse;
}
table.hovertable th {
	background-color:#c3dde0;
	border-width: 1px;
	padding: 8px;
	border-style: solid;
	border-color: #a9c6c9;
}
table.hovertable tr {
	background-color:#d4e3e5;
}
table.hovertable td {
	border-width: 1px;
	padding: 8px;
	border-style: solid;
	border-color: #a9c6c9;
}
</style>
</style>

<style> 
html{width:100%;height:100%;} 
body{background:#B0E0E6;font-size:18px;font-family:"Arial", "Tahoma", "微软雅黑", "雅黑";
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
<br>	
<h1>Books Return</h1>
<br>
<br>
<p>Books Borrowed:</p>
<br>
<?php
 	include("connect.php");	

 	if(!empty($_POST['sub'])){
 		$id = $_POST['id'];
 		setcookie('rcardcookie',$id);
		$sqlpre = "SELECT * FROM card WHERE id = '$id'";	
		$sql = "SELECT * FROM card JOIN record WHERE record.card_id = '$id' and card.id = '$id'";
		$querypre = mysql_query($sqlpre);
		$rspre = mysql_fetch_array($querypre);
		$query = mysql_query($sql);
		if(!$rspre)
			echo "<script>alert('card doesn\'t exit!!');location.href = 'borrowpre.php'</script>";
		else
?>
<table border="0"  class="hovertable" >
<th>BookID</th>
<th>Category</th>
<th>Title</th>
<th>Press</th>
<th>PublishTime</th>
<th>Author</th>
<th>Price</th>
<th>BorrowTime</th>
<th>ReturnTime</th>
<?php
		while($rs = mysql_fetch_array($query)){
?>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td><?php 
  	$gain = $rs['book_id'];
  	$sql_n = "SELECT * FROM books WHERE id = $gain";
  	$query_n = mysql_query($sql_n);
  	$rs_n = mysql_fetch_array($query_n);
  	echo $rs['book_id'];
  ?></td>
  <td><?php
  	  	echo $rs_n['category'];	  	
  ?>
  </td>
   <td><?php
  	  	echo $rs_n['name'];	  	
  ?>
  </td>
   <td><?php
  	  	echo $rs_n['press'];	  	
  ?>
  </td>
     <td><?php
  	  	echo $rs_n['time'];	  	
  ?>
  </td>
     <td><?php
  	  	echo $rs_n['author'];	  	
  ?>
  </td>
     <td><?php
  	  	echo $rs_n['price'];	  	
  ?>
  </td>
     <td><?php
  	  	echo $rs['borrow_time'];	  	
  ?>
  </td>
     <td><?php
  	  	echo $rs['return_time'];	  	
  ?>
  </td>
</tr>
<?php
	}
}
?>
</table>
<br>
<p>Enter The BookID:</p>
<form action = "return.php" method = "post">
<input type="text" name="return">
<input type = "submit" name="sub2" class="btn" value="Return Books!"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'">
 </form>
 <?php
	if(!empty($_POST['sub2'])){
    $card = $_COOKIE['rcardcookie'];
 		$return = $_POST['return'];
 		$sql_b = "SELECT * FROM record WHERE book_id = '$return' and card_id = '$card'";
 		$query_b = mysql_query($sql_b);
		$rs_b = mysql_fetch_array($query_b);

		if(!$rs_b){
			echo "<script>alert('You didn\'t borrow this book!!');location.href = 'returnpre.php'</script>";
		}
		else{
			$sql_success = "UPDATE books SET number = number + 1 where id ='$return'";
			mysql_query($sql_success);
			$sql_successre = "DELETE FROM record where book_id = '$return' and card_id = '$card'";
			mysql_query($sql_successre);
			echo "<script>alert('Return Successfully!!');location.href = 'borrowpre.php'</script>";
		}
	}
 ?>
<br>
<br>
<li><a href = 'borrowpre.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Another Card!!!!</a></li>
 <br>
 <br>
<li><a href = 'index.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Back Home!  </a></li>
 <br>
