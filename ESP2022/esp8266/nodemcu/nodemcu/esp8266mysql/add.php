<?php
date_default_timezone_set('Asia/Bangkok');
$temp = $_GET['temp'];
$hum = $_GET['hum'];

$servername = "db";
$username = "root";
$password = "MYSQL_ROOT_PASSWORD";
$dbname = "tutor";

// Create connection
$conn = new mysqli($servername, $username,$password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$valtemp = $_GET['temp'];
$valhum = $_GET['hum'];
$sql = "INSERT INTO esp8266(temp,HUM) VALUES ($valtemp, $valhum);";

if ($conn->query($sql) === TRUE) {
    echo "save OK";
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
