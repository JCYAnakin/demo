<!doctype html>
<head>
  <title>ADD Books</title>
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
<h1><center>Add Books!</center></h1>
</div>

<div id="menu">
<h2><center>  
<form action = "add.php" method = "post">
<table border="0">
<tr>
  <td>Book ID:</td>
  <td><input type="text" name="id"></td>
</tr>
<tr>
  <td>Category:</td>
  <td><input type="text" name="category"></td>
</tr>
<tr>
  <td>Title:</td>
  <td><input type="text" name="title"></td>
</tr>
<tr>
  <td>Press:</td>
  <td><input type="text" name="press"></td>
</tr>
<tr>
  <td>Press time:</td>
  <td><input type="text" name="time"></td>
</tr>
<tr>
  <td>Author:</td>
  <td><input type="text" name="author"></td>
</tr>
<tr>
  <td>Price:</td>
  <td><input type="text" name="price"></td>
</tr>
<tr>
  <td>Quantity:</td>
  <td><input type="text" name="quantity"></td>
</tr>
</table>
<input type = "submit" name="sub" class="btn" value="ADD BOOKS!"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'">
</form>

<br>
</center></h2>
<ul>
<li><a href = 'index.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Home</a></li>
</ul>
</div>

<div id="footer">Powered By Ji Chenyang<br></div>
</div> 
</body> 
</html>

<?php
 	include("connect.php");	

 	if(!empty($_POST['sub'])){
 		$id = $_POST['id'];
 		$category = $_POST['category'];
 		$title = $_POST['title'];
 		$press = $_POST['press'];
 		$time = $_POST['time'];
 		$author = $_POST['author'];
 		$price = $_POST['price'];
 		$quantity = $_POST['quantity'];
 		//now(),get time
 		 $sql_s = "SELECT id , category, name, press, time, author, price FROM books WHERE id = '$id'";
		 $sql = "INSERT INTO books VALUES('$id', '$category', '$title','$press','$time', '$author', '$price','$quantity','$quantity')";
		 //$sql_d = "DELETE FROM books where id = '$title'";
		 $sql_u = "UPDATE books SET total = total + $quantity, number = number + $quantity where id ='$id'";
// if the insert is null
		 if(!$id){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the ID cannot be null!');location.href = 'add.php'</script>"; 
		 }
		 else if(!$category){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the CATEGORY cannot be null!');location.href = 'add.php'</script>"; 
		 }
		  else if(!$title){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the TITLE cannot be null!');location.href = 'add.php'</script>"; 
		 }
		  else if(!$press){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the PRESS cannot be null!');location.href = 'add.php'</script>"; 
		 }

		 else if(!$time){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the TIME cannot be null!');location.href = 'add.php'</script>"; 
		 }
		  else if(!$author){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the AUTHOR cannot be null!');location.href = 'add.php'</script>"; 
		 }
		  else if(!$price){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the PRICE cannot be null!');location.href = 'add.php'</script>"; 
		 }
		  else if(!$quantity){
		 //	mysql_query($sql_d);
		 	echo "<script>alert('the QUANTITY cannot be null!');location.href = 'add.php'</script>"; 
		 }
		 //
	 	else{
			$check = mysql_query($sql_s);
			$rs = mysql_fetch_array($check);
//if the id is exist.. 
			if($rs['id'] == $id){
				if($rs['category']!=$category||$rs['name']!=$title||$rs['press']!=$press||$rs['time']!=$time||$rs['author']!=$author||$rs['price']!=$price){
					echo "<script>alert('this book id has exist, choose another one!');location.href = 'add.php'</script>";  
				}
				else{
					mysql_query($sql_u);
					echo "<script>alert('add to old book success!');location.href = 'add.php'</script>";  
				}
			}
			else{
				mysql_query($sql);
				echo "<script>alert('add new book success!');location.href = 'add.php'</script>";  
			}
			//echo "<script>alert('insert success!');location.href = 'index.php'</script>"; 
		}
 	}

?>
