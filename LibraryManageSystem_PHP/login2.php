<?php
 	include("connect.php");
 	?>
<center>
 <?php
 	echo "Current Time:",date("Y-m-d H:i:s");
 	?>
 </center>
 	<?php
 		if(isset($_POST['sub'])){
 		$id = $_POST['id'];
 		setcookie('admincookie',$id);
 		$password = $_POST['password'];
		$sql = "SELECT * FROM admin WHERE id = '$id'";
		$check = mysql_query($sql);
		$rs = mysql_fetch_array($check);

		if(!$rs['id'])
			echo "<script>alert('admin doesn\'t exit!!');location.href = 'login.php'</script>";
		if($rs['password'] == $password){
			echo "<script>alert('login success!');location.href = 'index.php'</script>";
		}
		else{
			echo "<script>alert('Wrong password');location.href = 'login.php'</script>";
		}
 	}

?>