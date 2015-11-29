<?php
 	include("connect.php");

 	if(!empty($_GET['edit'])){
 		$e = $_GET['edit'];
 		//$sql = "SELECT * FROM test WHERE id = '".$_GET['id']."'";
 		 $sql = "SELECT * FROM test WHERE id = '$e'";
 		 $query = mysql_query($sql);
 		 $rs = mysql_fetch_array($query);
	}


 	if(!empty($_POST['sub'])){
 		$title = $_POST['title'];
 		$con = $_POST['con'];
 		$hid = $_POST['hid'];
 		//now(),get time
	    $sql = "UPDATE test set name ='$title', things = '$con' where id ='$hid'";
		//echo $sql;
		mysql_query($sql);
		echo "<script>alert('update success!');location.href = 'index.php'</script>";     // window 
 	}
?>
<form action = "edit.php?edit=<?php echo $rs['id'];?>" method = "post">             

<input type = "hidden" name = "hid" value = "<?php echo $rs['id'] ?>">

title <input type="text" name="title"  value = "<?php echo $rs['name'] ?>"><br>   
content<textarea rows="5" cols ="50" name = "con"><?php echo $rs['things'] ?></textarea><br>  
<input type = "submit" name="sub" value="yes!">
</form>