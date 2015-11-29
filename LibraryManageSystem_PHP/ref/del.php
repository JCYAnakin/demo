<?php
 	include("connect.php");

 		if(!empty($_GET['del'])){
 			$d = $_GET['del'];
 		//now(),get time
		 $sql = "DELETE FROM test where id = '$d'";
		//echo $sql;
		mysql_query($sql);
		echo "<script>alert('delete success!');location.href = 'index.php'</script>"; 
 	}

?>