<head>
  <title>Search Books</title>
    <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;}
div#menu {background-color:#B0E0E6;height:425px;width:864px;float:left;}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;font-family: Colonna MT}
h2 {margin-bottom:0;font-size:18px;text-align: center}
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
<h1>Search results:</h1>
<br>
<br>
<?php
 	include("connect.php");	

 	if(!empty($_POST['sub'])){
 		$id = $_POST['id'];
 		$category = $_POST['category'];
 		$title = $_POST['title'];
 		$press = $_POST['press'];
 		$time = $_POST['time'];
 		$timehi = $_POST['timehi'];
 		$author = $_POST['author'];
 		$price = $_POST['price'];
 		$pricehi = $_POST['pricehi'];
 		$order = $_POST['order'];
 		//now(),get time
// if the query is null
		if(!$id){
		 	$id = '%'; 
		 }
		if(!$category){
			$category = '%'; 
		 }
		if(!$title){
		 	$title = '%'; 
		 }
		if(!$press){
			$press = '%'; 
		 }
		if(!$time){
			//$time = '%';
		 	$time = -1; 
		 }
		if(!$author){
		 	$author = '%'; 
		 }
		if(!$price){
			//$price = '%';
		 	$price = -1; 
		 }	
		if(!$timehi){
 			$timehi = 99999;
 		}
 		if(!$pricehi){
 			$pricehi = 99999;
 		}
		 if(!$order){
		 	$order = 'name';
		 }	
//		
		//$sql = "SELECT * FROM books WHERE id like '$id' and category like '$category'and name like '$title'and press like '$press'and time between '$time' and '$timehi' and author like '$author'and price between '$price' and '$pricehi' ORDER by $order asc";
		$sql = "SELECT * FROM books WHERE id like '%$id%' and category like '%$category%'and name like '%$title%'and press like '%$press%' and time between '$time' and '$timehi' and author like '%$author%'and price between '$price' and '$pricehi'ORDER by $order asc";
		$query = mysql_query($sql);
		$i = 0;
		while($rs = mysql_fetch_array($query)){
			if($i == 50)
				break; 
			$i = $i + 1;

?>
<table border="0"  class="hovertable" >
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Book ID:</td>
  <td><?php echo $rs['id']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Category:</td>
  <td><?php echo $rs['category']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Title:</td>
  <td><?php echo $rs['name']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Press:</td>
  <td><?php echo $rs['press']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Press time:</td>
  <td><?php echo $rs['time']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Author:</td>
  <td><?php echo $rs['author']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Price:</td>
  <td><?php echo $rs['price']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Total:</td>
  <td><?php echo $rs['total']?></td>
</tr>
<tr onmouseover="this.style.backgroundColor='#ffff66';" onmouseout="this.style.backgroundColor='#d4e3e5';">
  <td>Available:</td>
  <td><?php echo $rs['number']?></td>
</tr>
</table>
<hr>
<?php
	}
	if($i == 0){
		echo "<script>alert('No Such Books!!!');location.href = 'search.php'</script>";
	}
}
?>
<br>
<br>
<li><a href = 'search.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Searching!</a></li>
 <br>
 <br>
<li><a href = 'index.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Back Home!  </a></li>
 <br>
 <br>
 <br>
 <br>