<!doctype html>
<head>
  <title>Search Books</title>
    <style type="text/css">
div#container{width:900px; height: auto;
   position: relative;
   left: 15%; }
div#header {background-color:#5F9EA0;font-family:"Colonna MT";}
div#menu {background-color:#B0E0E6;height:435px;width:864px;float:left;font-family:"Courier New"}
div#footer {background-color:#99bbbb;clear:both;text-align:center;}
h1 {margin-bottom:0;}
h2 {margin-bottom:0;font-size:18px;text-align: center}
ul {margin:0;}
li {list-style:none;text-align: center}
p {margin-bottom:0;font-size: 10px;font-family:"Arial";}
</style>

<style> 
html{width:100%;height:100%;} 
body{background:#fff;font-size:18px;font-family:"Colonna MT", "Tahoma", "微软雅黑", "雅黑";
line-height:18px;padding:0px;margin:0px;text-align:center} 
div{padding:18px} 
img{border:0px;vertical-align:middle;padding:0;margin:0} 
input, button{font-family:"Arial", "Tahoma", "微软雅黑", "雅黑";border:0;
vertical-align:middle;margin:8px;line-height:18px;font-size:18px} 
.btn{width:140px;height:26px;line-height:18px;font-size:18px;
background:url("bg.jpg") no-repeat left top;color:#FFF;padding-bottom:4px} 
a{      /* 统一设置所以样式 */
     font-family:HAKUYOGuiFanZi3500;
     font-size:30px;
     text-align:center;
     margin:3px;
}
a:link,a:visited{  /* 超链接正常状态、被访问过的样式 */
    color: #F0F0F0;
    padding:0px 100px 0px 100px;
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
<h1><center>Search For Books!</center></h1>
</div>

<div id="menu">
<h2><center>  
<form action = "searchres.php" method = "post">
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
    <td>-</td>
  <td><input type="text" name="timehi"></td>
</tr>
<tr>
  <td>Author:</td>
  <td><input type="text" name="author"></td>
</tr>
<tr>
  <td>Price:</td>
  <td><input type="text" name="price"></td>
  <td>-</td>
  <td><input type="text" name="pricehi"></td>
</tr>
<tr>
  <td>Order by?</td>
  <td><input type="text" name="order"></td>
</tr>
</table>
<p>*NOTE: The input of "order" can be chosen from "id, category, name, press, time, author, price".</p>
<input type = "submit" name="sub" class = "btn" value="Search"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'">
</form>
</center></h2>
<ul>
<br>
<li><a href = 'index.php' class = "a"onmouseover="this.style.backgroundPosition='left -36px'"
 onmouseout="this.style.backgroundPosition='left top'"> Return Home!</a></li>
</ul>

</div>	
<div id="footer">Powered By Ji Chenyang</div>
</div> 	
</body>
</html>
