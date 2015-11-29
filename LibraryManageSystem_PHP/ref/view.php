<?php
 	include("connect.php");

 	if(!empty($_GET['edit'])){
 		$e = $_GET['edit'];
 		//$sql = "SELECT * FROM test WHERE id = '".$_GET['id']."'";
 		 $sql = "SELECT * FROM test WHERE id = '$e'";
 		 $query = mysql_query($sql);
 		 $rs = mysql_fetch_array($query);
	}

?>
<h1><?php echo $rs['name']?></h1>
<h3> dianjiliang: </h3>
<hr>
<p>
<?php echo $rs['things']?>
</p>