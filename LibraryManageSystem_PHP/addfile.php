<?php
 	include("connect.php");
 	?>
<center>
 <?php
 	echo "Current Time:",date("Y-m-d H:i:s");
 	?>
 </center>
 	<?php
 	if($_FILES['myfile']['name'] != ''){
　　if($_FILES['myfile']['error'] > 0)
　　　　echo "11" . $_FILES['myfile']['error'];
　　} 
	else{
　　　　move_uploaded_file($_FILES['myfile']['tmp_name'] , "uploads/" . $FILES['myfile']['name']);
　　　　echo "<script>alert(上传成功！);</script>";
　　}
} 
else{
　　echo "<script>alert(请上传文件！);</script>";
}
?>