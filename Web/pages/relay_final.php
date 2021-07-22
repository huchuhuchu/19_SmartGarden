<?php
require("../conf/mysqlconn.php");
require("../conf/phperror.php");
//header("Refresh:3");

//paging 설정
$query = "SELECT * FROM RelayTable ORDER BY idx4 DESC LIMIT 1;";
$result1 = mysqli_query($conn, $query);

while($row = mysqli_fetch_array($result1)){
	echo "relay=".$row['state'];
}
