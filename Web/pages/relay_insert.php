<?php
require ('../conf/mysqlconn.php');

//$pot = $_GET['pot'];
$state = $_GET['state'];


$query = "INSERT INTO RelayTable(state, time4) values('$state', now());";

if(isset($state)){
	mysqli_query($conn, $query);
	echo $query;
	header("location: relay_final.php");
}else{
	echo $query."<br>sub-fail";
}
?>
