<?php
header('Content-Type: text/html; charset=utf-8');

$host = "localhost";
$user = "smart";
$pw = "smartgarden!";
$name = "capstone";

$conn = mysqli_connect($host, $user, $pw, $name) or die("fail-1");

mysqli_select_db($conn, $name);

if(!$conn){
	die("fail-2");
}
?>
